#ifndef LITERATURE_INCLUDE_DEALER_HPP_
#define LITERATURE_INCLUDE_DEALER_HPP_

#include <vector>

#include "../include/card.hpp"
#include "../include/player.hpp"

class Dealer {
   private:
    std::vector<Card> deck;
    std::vector<int> CalcNumCardsPerPlayer(int num_players);
    void ShuffleDeck();

   public:
    Dealer();
    void DealCards(std::vector<Player> &players);
    void ShowRandomCard();
};

#endif