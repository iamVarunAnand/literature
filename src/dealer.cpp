#include "dealer.h"
#include "card.h"
#include <cstdlib>
#include <iostream>

Dealer::Dealer() {
    
}

void Dealer::ShuffleDeck() {
    srand(time(nullptr));

    for(int i = kNumTotalCards - 1; i > 0; --i) {
        int j = rand() % (i + 1);

        Card temp = deck[j];
        deck[j] = deck[i];
        deck[i] = temp;
    }
}

void Dealer::ShowRandomCard() {
    srand(time(nullptr));
    
    int index = rand() % kNumTotalCards;
    std::cout << "Generated index: " << index << " - ";
    std::cout << deck[index] << std::endl;
}