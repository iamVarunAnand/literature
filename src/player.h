#ifndef LITERATURE_PLAYER_H
#define LITERATURE_PLAYER_H

#include "card.h"
#include "message.h"
#include <iostream>
#include <vector>

class Player {
    private: int id;
    private: std::vector<Card> cards;

    public: Player();
    public: Player(int _id);
    public: void SetCards(std::vector<Card> _cards);
    public: Message GetNextMove();
    public: bool CheckForCard(Card c);
    public: void ShowCards();
    public: friend std::ostream& operator<<(std::ostream &strm, Player p);
};

#endif