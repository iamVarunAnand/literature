#include "deckofcards.h"
#include "dtypes.h"
#include <vector>

DeckOfCards::DeckOfCards() {
    kNumSuits = 4;
    kNumCardsPerSuit = 13;
    kNumTotalCards = kNumSuits * kNumCardsPerSuit;

    for(int i = 0; i < kNumSuits; ++i) {
        for(int j = 0; j < kNumCardsPerSuit; ++j) {
            Suit s = (Suit)i;
            Value v = (Value)j;

            Card c(s, v);
            deck.push_back(c);
        }
    }
}