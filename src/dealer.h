#ifndef LITERATURE_DEALER_H_
#define LITERATURE_DEALER_H_

#include "player.h"
#include "card.h"
#include <vector>

class Dealer {
    private: std::vector<Card> deck;

    public: Dealer();
    private: std::vector<int> CalcNumCardsPerPlayer(int num_players);
    private: void ShuffleDeck();
    public: void DealCards(std::vector<Player> &players);
    public: void ShowRandomCard();
};

#endif