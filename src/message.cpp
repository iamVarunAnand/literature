#include "card.h"
#include "message.h"
#include <iostream>

Message::Message() {
    card = Card();
    player_id = -1;
}

Message::Message(Card _card, int _player_id) {
    card = _card;
    player_id = _player_id;
}

std::ostream& operator<<(std::ostream &strm, Message msg) {
    return strm << "Message [" << msg.card << ", player_id = " << msg.player_id << "]";
}