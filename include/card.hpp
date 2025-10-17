#ifndef LITERATURE_INCLUDE_CARD_HPP_
#define LITERATURE_INCLUDE_CARD_HPP_

#include <iostream>

#include "../include/dtypes.hpp"

struct Card {
    Suit suit;
    Value value;

    Card();
    Card(Suit _suit, Value _value);
    bool operator==(const Card &b) const;
    friend std::ostream &operator<<(std::ostream &strm, Card &card);
};

struct CardHash {
    std::size_t operator()(const Card &) const;
};

#endif