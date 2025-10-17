#include "../include/messages.hpp"

#include <iostream>

#include "../include/card.hpp"
#include "../include/set.hpp"

AskForCardMessage::AskForCardMessage() {
    card = Card();
    player_id = -1;
}

AskForCardMessage::AskForCardMessage(Card _card, int _player_id) {
    card = _card;
    player_id = _player_id;
}

ReleaseCardMessage::ReleaseCardMessage() {
    release = false;
    card = Card();
}

ReleaseCardMessage::ReleaseCardMessage(bool _release, Card _card) {
    release = _release;
    card = _card;
}

DeclareSetMessage::DeclareSetMessage() {
    declare = false;
    set = Set();
}

DeclareSetMessage::DeclareSetMessage(bool _declare, Set _set) {
    declare = _declare;
    set = _set;
}

std::ostream &operator<<(std::ostream &strm, AskForCardMessage &msg) {
    return strm << "AskForCardMessage [" << msg.card << ", player_id = " << msg.player_id << "]";
}

std::ostream &operator<<(std::ostream &strm, ReleaseCardMessage &msg) {
    return strm << "ReleaseCardMessage [release = " << msg.release << ", " << msg.card << "]";
}

std::ostream &operator<<(std::ostream &strm, DeclareSetMessage &msg) {
    return strm << "DeclareSetMessage [declare = " << msg.declare << ", " << msg.set << "]";
}