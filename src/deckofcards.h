#ifndef LITERATURE_DECKOFCARDS_H_
#define LITERATURE_DECKOFCARDS_H_

#include "card.h"
#include <vector>

class DeckOfCards {
    protected: int kNumSuits;
    protected: int kNumCardsPerSuit;
    protected: int kNumTotalCards;
    protected: std::vector<Card> deck;

    public: DeckOfCards();
};

#endif