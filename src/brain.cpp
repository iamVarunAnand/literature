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
            if(set_counts[set] == 0) {
                ForgetSetCounts(set);
            }
        }
    }
}

void Player::Brain::ForgetSetCounts(Set set) {
    set_counts.erase(set);
}

bool Player::Brain::IsDeclare(Set set) {
    if(req_cards[set].size() == 0)
        return true;
    else
        return false;
}

void Player::Brain::UpdateRequiredCards(Card card, bool received) {
    Set set = Set(card.suit, Set::DetermineSetType(card.value));

    if(received) {
        // seeing the set for the first time
        if(req_cards.find(set) == req_cards.end()) {
            // push back all the cards except the received card
            std::vector<Card> set_cards = Set::GetCardsInSet(set);
            for(Card c : set_cards)
                if(!(c == card))
                    req_cards[set].push_back(c);
        }
        else {
            // find the current card and remove it
            auto it = std::find(req_cards[set].begin(), req_cards[set].end(), card);
            req_cards[set].erase(it);

            // check if the current set can be removed
            if(req_cards[set].size() == 0)
                ForgetRequiredCards(set);
        }
    }
    else {
        // check if the current set can be removed
        if(req_cards[set].size() == kNumCardsPerSet - 1) {
            req_cards.erase(set);
        }
        else {
            // add the card to the list of required cards
            req_cards[set].push_back(card);
        }
    }
}

void::Player::Brain::ForgetRequiredCards(Set set) {
    req_cards.erase(set);
}

Set Player::Brain::FindSetToPlay() {
    int max_count = INT16_MIN;
    Set set;

    for(std::pair<Set, int> sc : set_counts)
        if(sc.second > max_count) {
            max_count = sc.second;
            set = sc.first;
        }
    
    return set;
}

Card Player::Brain::GetNextMove(std::vector<Card> cards) {
    if(cards.size() == 0)
        return Card();
    else {
        Set set = FindSetToPlay();
        return req_cards[set][0];
    }
}