#ifndef LITERATURE_PLAYER_H
#define LITERATURE_PLAYER_H

#include "card.h"
#include "message.h"
#include "set.h"
#include <iostream>
#include <vector>
#include <unordered_map>

class Player {
    private: int id;
    private: std::vector<Card> cards;
    public: std::unordered_map<Set, int, SetHash> set_counts;
    public: int num_cards;

    public: Player();
    public: Player(int);
    public: void SetCards(std::vector<Card>);
    public: Message GetNextMove();
    public: bool ReleaseCard(Card);
    public: void ReceiveCard(Card);
    public: void ShowCards();
    public: friend std::ostream& operator<<(std::ostream&, Player&);
};

#endif