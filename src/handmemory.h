#ifndef LITERATURE_HANDMEMORY_H
#define LITERATURE_HANDMEMORY_H

#include "set.h"
#include "card.h"
#include <unordered_map>
#include <vector>

struct HandMemory {
    std::unordered_map<Set, int, SetHash> set_counts;
    std::unordered_map<Set, std::vector<Card>, SetHash> req_cards;

    void AddToSetCounts(Set);
    void DeleteFromSetCounts(Set);
    void ForgetSetCounts(Set);

    void AddToReqCards(Set, Card);
    void DeleteFromReqCards(Set, Card);
    void ForgetReqCards(Set);
};

#endif