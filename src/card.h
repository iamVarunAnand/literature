#ifndef LITERATURE_CARD_H_
#define LITERATURE_CARD_H_

#include "dtypes.h"
#include <iostream>

class Card {
    private: Suit suit;
    private: Value value;

    public: Card();
    public: Card(Suit _suit, Value _value);
    public: friend std::ostream& operator<<(std::ostream &strm, Card &card);
};

#endif