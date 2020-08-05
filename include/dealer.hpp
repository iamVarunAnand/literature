#ifndef LITERATURE_INCLUDE_DEALER_HPP_
#define LITERATURE_INCLUDE_DEALER_HPP_

#include <include/player.hpp>
#include <include/card.hpp>
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