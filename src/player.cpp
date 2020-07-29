#include "player.h"
#include "card.h"
#include "message.h"
#include <iostream>

Player::Player() {
    id = -1;
}

Player::Player(int _id) {
    id = _id;
}

std::ostream& operator<<(std::ostream &strm, Player p) {
    return strm << "Player [id = " << p.id << "]";
}

Message Player::GetNextMove() {
    // if this is the Computer, then the computer would have to decide its move first
    // if this is the User, then the move must be taken as input from the user

    // once the move has been decided, an appropriate message needs to be generated and returned

    // LIKELY: method needs to be defined separately by both child classes.

    return Message(Card(), 0);
}

bool Player::CheckForCard(Card c) {
    return false;
} 