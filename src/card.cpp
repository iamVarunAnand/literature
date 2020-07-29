#include "card.h"
#include "dtypes.h"
#include <iostream>

Card::Card() {
    suit = kSuitDefault;
    value = kValueDefault;
}

Card::Card(Suit _suit, Value _value) {
    suit = _suit;
    value = _value;
}

bool Card::operator==(const Card &b) {
    return (suit == b.suit && value == b.value);
}

std::ostream& operator<<(std::ostream& strm, Card &card) {
    return strm << "Card [suit = " << card.suit << ", value = " << card.value << "]";
}