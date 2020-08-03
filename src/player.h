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
        public:
            std::unordered_map<Set, std::vector<Card>, SetHash> req_cards;
            std::unordered_map<Card, std::vector<int>, CardHash> memory;
            bool declare;

            Brain();
            void AddToRequiredCards(Set, Card);
            void DeleteFromRequiredCards(Set, Card);
            void ForgetRequiredCards(Set);
            void AddPlayerToCard(Card, int);
            void DeletePlayerFromCard(Card, int);
            void ConfirmPlayerForCard(Card, int);
            void ForgetCard(Card);
            bool IsCardRequired(Card);

            void UpdateRequiredCards(Card, bool);
            void InitializeMemory(int, std::vector<Card>);
            void UpdateMemory(Card, int, bool);
            bool IsDeclare(Set);

            Set  FindSetToPlay();
            AskForCardMessage  CheckForCertainty();
            AskForCardMessage GetNextMove(std::vector<Card>);
    };


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
    public: void ShowCards();
    public: friend std::ostream& operator<<(std::ostream&, Player&);
};

#endif