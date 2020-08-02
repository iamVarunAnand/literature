#include "player.h"
#include "constants.h"
#include "set.h"
#include "card.h"
#include "algorithm"
#include <utility>

void Player::Brain::UpdateSetCounts(Set set, bool increment) {
    if(set_counts.find(set) == set_counts.end()) {
        set_counts[set] = 1;
    }
    else {    
        if(increment)
            set_counts[set] += 1;
        else {
            set_counts[set] -= 1;
            if(set_counts[set] == 0)
                ForgetSetCounts(set);
        }
    }
}

void Player::Brain::ForgetSetCounts(Set set) {
    set_counts.erase(set);
}

bool Player::Brain::IsDeclare(Set set) {
    if(set_counts[set] == kNumCardsPerSet)
        return true;
    else
        return false;
}

std::vector<Set> Player::Brain::FindPlayableSets() {
    std::vector<Set> playable;
    for(std::pair<Set, int> sc : set_counts)
        playable.push_back(sc.first);
    
    return playable;
}

std::vector<Card> Player::Brain::FindRequiredCards(std::vector<Card> player_cards) {
    std::vector<Set> playable_sets = FindPlayableSets();
    std::vector<Card> required_cards;
    for(Set set : playable_sets) {
        // find the cards part of the current set
        std::vector<Card> set_cards = Set::GetCardsInSet(set);

        // remove from this set the cards that the player already has
        for(auto it = set_cards.begin(); it != set_cards.end(); ++it) {
            if(std::find(player_cards.begin(), player_cards.end(), *it) != player_cards.end()) {
                set_cards.erase(it);
                it -= 1;
            }
        }

        // add all the remaining cards to the set of required cards
        for(Card c : set_cards)
            required_cards.push_back(c);       
    }

    return required_cards;
}

Card Player::Brain::GetNextMove(std::vector<Card> cards) {
    if(cards.size() == 0)
        return Card();
    else {
        std::vector<Card> required_cards = FindRequiredCards(cards);
        return required_cards[0];
    }
}