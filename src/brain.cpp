#include "player.h"
#include "constants.h"
#include "set.h"
#include "card.h"
#include "algorithm"
#include <utility>

Player::Brain::Brain() {
    declare = false;
}

void Player::Brain::ForgetRequiredCards(Set set) {
    req_cards.erase(set);
}

void Player::Brain::AddToRequiredCards(Set set, Card card) {
    // add the card to the list of required cards
    req_cards[set].push_back(card);

    // check if the set state can be forgotten
    if(req_cards[set].size() == kNumCardsPerSet)
        ForgetRequiredCards(set);
}

void Player::Brain::DeleteFromRequiredCards(Set set, Card card) {
    // find the card and delete it
    auto it = std::find(req_cards[set].begin(), req_cards[set].end(), card);
    req_cards[set].erase(it);

    // check if the set state can be forgotten (which means the set can be declared)
    if(req_cards[set].size() == 0) {
        ForgetRequiredCards(set);
        declare = true;
    }
}

void Player::Brain::UpdateRequiredCards(Card card, bool received) {
    // compute the current set
    Set set = Set(card.suit, Set::DetermineSetType(card.value));

    // check if the card has been received
    if(received) {
        // check if this is the first time a card belonging to this set is received
        if(req_cards.find(set) == req_cards.end()) {
            // grab all the cards that belong to the current set
            std::vector<Card> set_cards = Set::GetCardsInSet(set);

            // add all the set cards (except the received card) to the list of required cards
            for(Card c : set_cards)
                if(!(c == card))
                    AddToRequiredCards(set, c);
        }
        // else remove the received card from the list of required cards
        else {
            DeleteFromRequiredCards(set, card);
        }
    }
    // else the card has been released
    else {
        // add the released card to the list of required cards
        AddToRequiredCards(set, card);
    }
}

Set Player::Brain::FindSetToPlay() {
    int min_count = INT16_MAX;
    Set set_to_play;
    
    for(std::pair<Set, std::vector<Card>> rc : req_cards)
        if(rc.second.size() < min_count) {
            min_count = rc.second.size();
            set_to_play = rc.first;
        }
    
    return set_to_play;
}

Card Player::Brain::GetNextMove(std::vector<Card> cards) {
    if(cards.size() == 0)
        return Card();
    else {
        Set set = FindSetToPlay();
        return req_cards[set][0];
    }
}