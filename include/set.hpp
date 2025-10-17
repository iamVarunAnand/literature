#ifndef LITERATURE_INCLUDE_SET_HPP_
#define LITERATURE_INCLUDE_SET_HPP_

#include <iostream>
#include <vector>

#include "../include/card.hpp"
#include "../include/dtypes.hpp"

struct Set {
    Suit suit;
    int type;

    Set();
    Set(Suit, int);
    static int DetermineSetType(Value);
    static std::vector<Card> GetCardsInSet(Set);
    bool operator==(const Set&) const;
    friend std::ostream& operator<<(std::ostream&, Set&);
};

struct SetHash {
    std::size_t operator()(const Set&) const;
};

#endif