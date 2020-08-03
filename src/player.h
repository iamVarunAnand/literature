#ifndef LITERATURE_PLAYER_H
#define LITERATURE_PLAYER_H

#include "card.h"
#include "messages.h"
#include "set.h"
#include <iostream>
#include <vector>
#include <unordered_map>

class Player {

    private: class Brain {
        private: std::unordered_map<Set, std::vector<Card>, SetHash> req_cards;
        // private: std::unordered_map<Card, std::vector<Player>, CardHash> memory;

        public: bool declare;

        public: Brain();

        private: void AddToRequiredCards(Set, Card);
        private: void DeleteFromRequiredCards(Set, Card);
        private: void ForgetRequiredCards(Set);

        public: void UpdateRequiredCards(Card, bool);
        public: bool IsDeclare(Set);
        public: Set  FindSetToPlay();
        public: Card GetNextMove(std::vector<Card>);
    };


    private: int id;
    private: std::vector<Card> cards;
    private: Brain brain;

    public: int num_cards;
    public: int points;

    public: Player();
    public: Player(int);

    public: void SetCards(std::vector<Card>);
    public: AskForCardMessage PlayNextMove();
    public: ReleaseCardMessage ReleaseCard(Card);
    public: DeclareSetMessage ReceiveCard(Card);
    public: void DeclareSet(Set);
    // public: void ReceiveTurnInfo(Player, Player, Card, bool);
    public: void ShowCards();
    public: friend std::ostream& operator<<(std::ostream&, Player&);
};

#endif