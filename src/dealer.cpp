#include "dealer.h"
#include "dtypes.h"
#include "constants.h"
#include "card.h"
#include <cstdlib>
#include <iostream>

Dealer::Dealer() {
    for(int i = 0; i < kNumSuits; ++i) {
        for(int j = 0; j < kNumCardsPerSuit; ++j) {
            Suit s = (Suit)i;
            Value v = (Value)j;

            Card c(s, v);
            deck.push_back(c);
        }
    }
}

void Dealer::ShuffleDeck() {
    for(int i = kNumTotalCards - 1; i > 0; --i) {
        int j = rand() % (i + 1);

        Card temp = deck[j];
        deck[j] = deck[i];
        deck[i] = temp;
    }
}

std::vector<int> Dealer::CalcNumCardsPerPlayer(int num_players) {
    int num_initial_cards = kNumTotalCards / num_players;
    int num_extra_cards = kNumTotalCards % num_players;

    std::vector<int> kNumCardsPerPlayer;
    for(int i = 0; i < num_players; ++i)
        kNumCardsPerPlayer.push_back(num_initial_cards);

    for(int i = 0; i < num_extra_cards; ++i)
        kNumCardsPerPlayer[i] += 1;
    
    return kNumCardsPerPlayer;
}

void Dealer::DealCards(std::vector<Player> &players) {
    // calculate the number of cards for each player
    int num_players = players.size();
    std::vector<int> kNumCardsPerPlayer = CalcNumCardsPerPlayer(num_players);

    // shuffle the deck
    ShuffleDeck();

    // distribute the cards
    int deck_index = 0;
    for(int i = 0; i < num_players; ++i) {
        std::vector<Card> player_cards;
        for(int j = 0; j < kNumCardsPerPlayer[i]; ++j) {
            player_cards.push_back(deck[deck_index]);
            deck_index += 1;
        }
        players[i].SetCards(player_cards);
    }
}

void Dealer::ShowRandomCard() {    
    int index = rand() % kNumTotalCards;
    std::cout << "Generated index: " << index << " - ";
    std::cout << deck[index] << std::endl;
}