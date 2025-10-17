#ifndef LITERATURE_INCLUDE_BRAIN_HPP_
#define LITERATURE_INCLUDE_BRAIN_HPP_

#include <unordered_map>
#include <vector>

#include "../include/card.hpp"
#include "../include/messages.hpp"
#include "../include/set.hpp"

class Brain {
   private:
    std::unordered_map<Set, std::vector<Card>, SetHash> req_cards;
    std::unordered_map<Card, std::vector<int>, CardHash> memory;

    void AddToRequiredCards(Set, Card);
    void DeleteFromRequiredCards(Set, Card);
    void ForgetRequiredCards(Set);
    void AddPlayerToCard(Card, int);
    void DeletePlayerFromCard(Card, int);
    void ConfirmPlayerForCard(Card, int);
    void ForgetCard(Card);
    bool IsCardRequired(Card);

    bool IsDeclare(Set);

   public:
    bool declare;

    Brain();

    void UpdateRequiredCards(Card, bool);
    void InitializeMemory(int, std::vector<Card>);
    void UpdateMemory(Card, int, bool);
    void UpdateMemory(int, int, Card, bool);
    void UpdateMemory(int);
    void ShowMemory();

    Set FindSetToPlay();
    AskForCardMessage CheckForCertainty();
    AskForCardMessage GetNextMove(std::vector<Card>);
};

#endif