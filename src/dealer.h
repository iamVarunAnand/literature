#ifndef LITERATURE_DEALER_H_
#define LITERATURE_DEALER_H_

#include "deckofcards.h"

class Dealer : private DeckOfCards {
    public: Dealer();
    public: void ShuffleDeck();
    public: void ShowRandomCard();
};

#endif