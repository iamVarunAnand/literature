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
        private: std::unordered_map<Set, int, SetHash> set_counts;
        private: std::unordered_map<Set, std::vector<Card>, SetHash> req_cards;

        public: void UpdateSetCounts(Set, bool);
        public: void UpdateRequiredCards(Card, bool);
        public: void ForgetSetCounts(Set);
        public: void ForgetRequiredCards(Set);
        public: bool IsDeclare(Set);
        public: Set FindSetToPlay();
        public: Card GetNextMove(std::vector<Card>);

        // TODO: encompass all into HandMemory
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
    public: void ShowCards();
    public: friend std::ostream& operator<<(std::ostream&, Player&);
};

#endif