#include "player.h"
#include "card.h"
#include "messages.h"
#include "dtypes.h"
#include "constants.h"
#include "set.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>

Player::Player() {
    id = -1;

    num_cards = 0;
    points = 0;
}

Player::Player(int _id) {
    id = _id;

    num_cards = 0;
    points = 0;
}

std::ostream& operator<<(std::ostream &strm, Player &p) {
    return strm << "Player [id = " << p.id << "]";
}

void Player::SetCards(std::vector<Card> _cards) {
    // calculate the total number of cards
    num_cards = _cards.size();
    for(int i = 0; i < num_cards; ++i)
    {
        // pick up the card
        cards.push_back(_cards[i]);

        // update set count
        Set current_set(_cards[i].suit, Set::DetermineSetType(_cards[i].value));
        if(set_counts.find(current_set) != set_counts.end())
            set_counts[current_set] += 1;
        else
            set_counts[current_set] = 1;
    }
}

void Player::ShowCards() {
    for(Card c : cards)
        std::cout << c << std::endl;
}

AskForCardMessage Player::GetNextMove() {
    // if this is the Computer, then the computer would have to decide its move first
    // if this is the User, then the move must be taken as input from the user

    // once the move has been decided, an appropriate message needs to be generated and returned

    // LIKELY: method needs to be defined separately by both child classes.

    // for now, return a random message
    Suit s = (Suit)(rand() % kNumSuits);
    Value v = (Value)(rand() % kNumCardsPerSuit);
    int pid = rand() % kNumPlayers;

    return AskForCardMessage(Card(s, v), pid);
}

ReleaseCardMessage Player::ReleaseCard(Card card) {
    bool release = false;

    auto it = std::find(cards.begin(), cards.end(), card);
    if(it != cards.end()) {
        // drop the card
        cards.erase(it);

        // update the set count
        Set current_set(card.suit, Set::DetermineSetType(card.value));
        set_counts[current_set] -= 1;

        // decrement the card count
        num_cards -= 1;

        release = true;
    }

    return ReleaseCardMessage(release, card);
}

DeclareSetMessage Player::ReceiveCard(Card card) {
    bool declare = false;
    
    // pick up the card
    cards.push_back(card);

    // update set count
    Set current_set(card.suit, Set::DetermineSetType(card.value));
    set_counts[current_set] += 1;

    // check if the set is to be declared
    if(set_counts[current_set] == kNumCardsPerSet)
        declare = true;

    // increment card count
    num_cards += 1;

    return DeclareSetMessage(declare, current_set);
}

void Player::DeclareSet(Set set) {
    // remove cards that belong to the particular set
    for(int i = 0; i < num_cards; ++i) {
        Set current_set(cards[i].suit, Set::DetermineSetType(cards[i].value));

        if(current_set == set) {
            cards.erase(cards.begin() + i);
            i -= 1;
            num_cards -= 1;
        }
    }

    // remove set from set counts
    set_counts.erase(set);
}