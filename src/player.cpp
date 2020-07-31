#include "player.h"
#include "card.h"
#include "message.h"
#include "dtypes.h"
#include "set.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>

Player::Player() {
    id = -1;
    num_cards = 0;
}

Player::Player(int _id) {
    id = _id;
    num_cards = 0;
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

Message Player::GetNextMove() {
    // if this is the Computer, then the computer would have to decide its move first
    // if this is the User, then the move must be taken as input from the user

    // once the move has been decided, an appropriate message needs to be generated and returned

    // LIKELY: method needs to be defined separately by both child classes.

    // for now, return a random message
    Suit s = (Suit)(rand() % 4);
    Value v = (Value)(rand() % 12);
    int pid = rand() % 4;

    return Message(Card(s, v), pid);
}

bool Player::ReleaseCard(Card card) {
    auto it = std::find(cards.begin(), cards.end(), card);
    if(it != cards.end()) {
        // drop the card
        cards.erase(it);

        // update the set count
        Set current_set(card.suit, Set::DetermineSetType(card.value));
        set_counts[current_set] -= 1;

        // check if set key can be removed
        if(set_counts[current_set] == 0)
            set_counts.erase(current_set);

        // decrement the card count
        num_cards -= 1;

        return true;
    }
    else
        return false;
}

void Player::ReceiveCard(Card card) {
    // pick up the card
    cards.push_back(card);

    // update set count
    Set current_set(card.suit, Set::DetermineSetType(card.value));
    set_counts[current_set] += 1;

    // increment card count
    num_cards += 1;
}