#ifndef LITERATURE_PLAYER_H
#define LITERATURE_PLAYER_H

#include "card.h"
#include "messages.h"
#include "set.h"
#include <iostream>
#include <vector>
#include <unordered_map>

class Player {
    private: int id;
    private: std::vector<Card> cards;
    public: std::unordered_map<Set, int, SetHash> set_counts;

    public: int num_cards;
    public: int points;

    public: Player();
    public: Player(int);

    public: void SetCards(std::vector<Card>);
    public: AskForCardMessage GetNextMove();
    public: ReleaseCardMessage ReleaseCard(Card);
    public: DeclareSetMessage ReceiveCard(Card);
    public: void DeclareSet(Set);
    public: void ShowCards();
    public: friend std::ostream& operator<<(std::ostream&, Player&);
};

#endif