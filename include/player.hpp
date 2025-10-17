#ifndef LITERATURE_INCLUDE_PLAYER_HPP_
#define LITERATURE_INCLUDE_PLAYER_HPP_

#include <iostream>
#include <vector>

#include "../include/brain.hpp"
#include "../include/card.hpp"
#include "../include/messages.hpp"
#include "../include/set.hpp"

class Player {
   private:
    int id;
    std::vector<Card> cards;
    Brain brain;

   public:
    int num_cards;
    int points;
    bool isplaying;

    Player();
    Player(int);

    void SetCards(std::vector<Card>);
    void DeclareSet(Set);
    void ReceiveTurnInfo(int, int, Card, bool);
    void ReceivePlayerHasLeftGameUpdate(int);
    void ShowCards();
    void ShowMemory();

    AskForCardMessage PlayNextMove();
    ReleaseCardMessage ReleaseCardTo(Card, int);
    DeclareSetMessage ReceiveCardFrom(Card, int);

    friend std::ostream& operator<<(std::ostream&, Player&);
};

#endif