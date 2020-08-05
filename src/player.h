#ifndef LITERATURE_PLAYER_H
#define LITERATURE_PLAYER_H

#include "card.h"
#include "messages.h"
#include "set.h"
#include "brain.h"
#include <iostream>
#include <vector>
#include <unordered_map>

class Player {

    private: int id;
    private: std::vector<Card> cards;
    public: Brain brain;

    public: int num_cards;
    public: int points;

    public: Player();
    public: Player(int);

    public: void SetCards(std::vector<Card>);
    public: AskForCardMessage PlayNextMove();
    public: ReleaseCardMessage ReleaseCardTo(Card, int);
    public: DeclareSetMessage ReceiveCardFrom(Card, int);
    public: void DeclareSet(Set);
    public: void ReceiveTurnInfo(int, int, Card, bool);
    public: void ReceivePlayerHasLeftGameUpdate(int);
    public: void ShowCards();
    public: void ShowMemory();
    public: friend std::ostream& operator<<(std::ostream&, Player&);
};

#endif