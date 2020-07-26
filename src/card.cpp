#include "card.h"
#include "dtypes.h"
#include <iostream>

Card::Card() {
    suit = ksuit_default;
    value = kvalue_default;
}

Card::Card(Suit _suit, Value _value) {
    suit = _suit;
    value = _value;
}

std::ostream& operator<<(std::ostream& strm, Card &card) {
    return strm << "Card [suit = " << card.suit << ", value = " << card.value << "]";
}