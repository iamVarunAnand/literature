#ifndef LITERATURE_CARD_H_
#define LITERATURE_CARD_H_

#include "dtypes.h"
#include <iostream>

struct Card {
    Suit suit;
    Value value;

    Card();
    Card(Suit _suit, Value _value);
    friend std::ostream& operator<<(std::ostream &strm, Card &card);
    bool operator==(const Card &b);
};

#endif