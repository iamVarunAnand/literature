#include <include/dtypes.hpp>
#include <include/set.hpp>
#include <include/card.hpp>
#include <include/renderer.hpp>
#include <iostream>
#include <vector>

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

std::vector<Card> Set::GetCardsInSet(Set set) {
    std::vector<Card> cards;

    if(set.type) {
        for(Value v = kNine; v <= kAce; v = (Value)(v + 1))
            cards.push_back(Card(set.suit, v));
    }
    else {
        for(Value v = kTwo; v <= kSeven; v = (Value)(v + 1))
            cards.push_back(Card(set.suit, v));
    }

    return cards;
}

bool Set::operator==(const Set &b) const {
    return (suit == b.suit && type == b.type);
}

std::ostream& operator<<(std::ostream &strm, Set &s) {
    return strm << "Set [Suit = " << Renderer::kSuitToString.at(s.suit) << ", type = " << s.type << "]";
}

std::size_t SetHash::operator()(const Set &x) const {
    return std::hash<std::size_t>()(x.suit ^ (x.type << 31));
}