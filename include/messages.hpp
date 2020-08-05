#ifndef LITERATURE_INCLUDE_MESSAGES_HPP_
#define LITERATURE_INCLUDE_MESSAGES_HPP_

#include <include/card.hpp>
#include <include/set.hpp>
#include <iostream>

struct AskForCardMessage {
    Card card;
    int player_id;

    AskForCardMessage();
    AskForCardMessage(Card _card, int _player_id);
    friend std::ostream& operator<<(std::ostream &strm, AskForCardMessage &msg);
};

struct ReleaseCardMessage {
    bool release;
    Card card;

    ReleaseCardMessage();
    ReleaseCardMessage(bool _release, Card _card);
    friend std::ostream& operator<<(std::ostream &strm, ReleaseCardMessage &msg);
};

struct DeclareSetMessage {
    bool declare;
    Set set;

    DeclareSetMessage();
    DeclareSetMessage(bool _declare, Set _set);
    friend std::ostream& operator<<(std::ostream &strm, DeclareSetMessage &msg);
};

#endif