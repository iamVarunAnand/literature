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
    if(set_counts[set] == kNumCardsPerSet)
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

// std::vector<Card> Player::Brain::FindRequiredCards(std::vector<Card> player_cards) {
//     std::vector<Set> playable_sets = FindPlayableSets();
//     std::vector<Card> required_cards;
//     for(Set set : playable_sets) {
//         // find the cards part of the current set
//         std::vector<Card> set_cards = Set::GetCardsInSet(set);

//         // remove from this set the cards that the player already has
//         for(auto it = set_cards.begin(); it != set_cards.end(); ++it) {
//             if(std::find(player_cards.begin(), player_cards.end(), *it) != player_cards.end()) {
//                 set_cards.erase(it);
//                 it -= 1;
//             }
//         }

//         // add all the remaining cards to the set of required cards
//         for(Card c : set_cards)
//             required_cards.push_back(c);       
//     }

//     return required_cards;
// }

Card Player::Brain::GetNextMove(std::vector<Card> cards) {
    if(cards.size() == 0)
        return Card();
    else {
        Set set = FindSetToPlay();
        return req_cards[set][0];
    }
}