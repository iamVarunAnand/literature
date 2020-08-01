#ifndef LITERATURE_MESSAGES_H
#define LITERATURE_MESSAGES_H

#include "card.h"
#include "set.h"
#include <iostream>

struct Message {
    // purely for ease of implementation purposes
};

struct AskForCardMessage : public Message {
    Card card;
    int player_id;

    AskForCardMessage();
    AskForCardMessage(Card _card, int _player_id);
    friend std::ostream& operator<<(std::ostream &strm, AskForCardMessage &msg);
};

struct ReleaseCardMessage : public Message {
    bool release;
    Card card;

    ReleaseCardMessage();
    ReleaseCardMessage(bool _release, Card _card);
    friend std::ostream& operator<<(std::ostream &strm, ReleaseCardMessage &msg);
};

struct DeclareSetMessage : public Message {
    bool declare;
    Set set;

    DeclareSetMessage();
    DeclareSetMessage(bool _declare, Set _set);
    friend std::ostream& operator<<(std::ostream &strm, DeclareSetMessage &msg);
};

#endif