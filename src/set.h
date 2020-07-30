#ifndef LITERATURE_SET_H
#define LITERATURE_SET_H

#include "dtypes.h"
#include <iostream>

struct Set {
    Suit suit;
    bool type;

    Set();
    Set(Suit, int);
    static bool DetermineSetType(Value);
    bool operator==(const Set&) const;
    friend std::ostream& operator<<(std::ostream&, Set&);

};

struct SetHash {
    std::size_t operator()(const Set&) const;
};

#endif