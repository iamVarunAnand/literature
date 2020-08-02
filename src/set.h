#ifndef LITERATURE_SET_H
#define LITERATURE_SET_H

#include "dtypes.h"
#include "card.h"
#include <iostream>
#include <vector>

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