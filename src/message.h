#ifndef LITERATURE_MESSAGE_H
#define LITERATURE_MESSAGE_H

#include "card.h"
#include <iostream>

struct Message {
    Card card;
    int player_id;

    Message();
    Message(Card _card, int _player_id);
    friend std::ostream& operator<<(std::ostream &strm, Message msg);
};

#endif