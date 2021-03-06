#ifndef LITERATURE_INCLUDE_PLAYER_HPP_
#define LITERATURE_INCLUDE_PLAYER_HPP_

#include <include/card.hpp>
#include <include/messages.hpp>
#include <include/set.hpp>
#include <include/brain.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>

class Player {

    private: int id;
    private: std::vector<Card> cards;
    private: Brain brain;

    public: int num_cards;
    public: int points;
    public: bool isplaying;

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