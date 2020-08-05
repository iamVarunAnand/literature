#ifndef LITERATURE_BRAIN_H
#define LITERATURE_BRAIN_H

#include "card.h"
#include "set.h"
#include "messages.h"
#include <unordered_map>
#include <vector>

class Brain {
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
            void UpdateMemory(int, int, Card, bool);
            void UpdateMemory(int);
            bool IsDeclare(Set);

            Set  FindSetToPlay();
            AskForCardMessage  CheckForCertainty();
            AskForCardMessage GetNextMove(std::vector<Card>);
    };

#endif