#ifndef LITERATURE_PLAYER_H
#define LITERATURE_PLAYER_H

#include "card.h"
#include "message.h"
#include <vector>

class Player {
    private: int id;
    private: std::vector<Card> cards;

    public: Player();
    public: Player(int _id);
    public: Message GetNextMove();
};

#endif