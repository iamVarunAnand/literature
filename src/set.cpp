#include "dtypes.h"
#include "set.h"
#include <iostream>

Set::Set() {
    suit = kSuitDefault;
    type = -1;
}

Set::Set(Suit _suit, int _type) {
    suit = _suit;
    type = _type;
}

int Set::DetermineSetType(Value value) {
    if(value > kSeven)
        return 1;
    else
        return 0;
}

bool Set::operator==(const Set &b) const {
    return (suit == b.suit && type == b.type);
}

std::ostream& operator<<(std::ostream &strm, Set &s) {
    return strm << "Set [Suit = " << s.suit << ", type = " << s.type << "]";
}

std::size_t SetHash::operator()(const Set &x) const {
    return std::hash<std::size_t>()(x.suit ^ (x.type << 31));
}