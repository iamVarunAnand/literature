#include "player.h"
#include "card.h"
#include "message.h"
#include "dtypes.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

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
    num_cards = _cards.size();
    for(int i = 0; i < num_cards; ++i)
        cards.push_back(_cards[i]);
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
    Value v = (Value)(rand() % 13);
    int pid = rand() % 4;

    return Message(Card(s, v), pid);
}

// bool Player::CheckForCard(Card card) {
//     auto it = std::find(cards.begin(), cards.end(), card);
    
//     if(it != cards.end())
//         return true;
//     else
//         return false;
// }

bool Player::ReleaseCard(Card card) {
    auto it = std::find(cards.begin(), cards.end(), card);
    if(it != cards.end()) {
        cards.erase(it);
        num_cards -= 1;

        return true;
    }
    else
        return false;
}

void Player::ReceiveCard(Card card) {
    cards.push_back(card);
    num_cards += 1;
}