#include "player.h"
#include "card.h"
#include "messages.h"
#include "dtypes.h"
#include "constants.h"
#include "set.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>

Player::Player() {
    id = -1;

    num_cards = 0;
    points = 0;
}

Player::Player(int _id) {
    id = _id;

    num_cards = 0;
    points = 0;
}

std::ostream& operator<<(std::ostream &strm, Player &p) {
    return strm << "Player [id = " << p.id << "]";
}

void Player::SetCards(std::vector<Card> _cards) {
    // calculate the total number of cards
    num_cards = _cards.size();
    for(int i = 0; i < num_cards; ++i)
    {
        // pick up the card
        cards.push_back(_cards[i]);

        // update required cards
        brain.UpdateRequiredCards(_cards[i], true);
    }

    // initialize the memory
    brain.InitializeMemory(id, cards);
}

void Player::ShowCards() {
    for(Card c : cards)
        std::cout << c << std::endl;
}

AskForCardMessage Player::PlayNextMove() {
    // if this is the Computer, then the computer would have to decide its move first
    // if this is the User, then the move must be taken as input from the user

    // once the move has been decided, an appropriate message needs to be generated and returned

    // LIKELY: method needs to be defined separately by both child classes.

    // for now, return a random message

    return brain.GetNextMove(cards);
}

ReleaseCardMessage Player::ReleaseCardTo(Card card, int pid) {
    bool release = false;

    auto it = std::find(cards.begin(), cards.end(), card);
    if(it != cards.end()) {
        // drop the card
        cards.erase(it);

        // update the required cards
        brain.UpdateRequiredCards(card, false);

        // update memory
        brain.UpdateMemory(card, pid, false);

        // decrement the card count
        num_cards -= 1;

        // update the release flag
        release = true;
    }

    return ReleaseCardMessage(release, card);
}

DeclareSetMessage Player::ReceiveCardFrom(Card card, int pid) {
    bool declare = false;
    
    // pick up the card
    cards.push_back(card);

    // update required cards
    brain.UpdateRequiredCards(card, true);

    // update memory
    brain.UpdateMemory(card, pid, true);

    // increment card count
    num_cards += 1;

    return DeclareSetMessage(brain.declare, Set(card.suit, Set::DetermineSetType(card.value)));
}

void Player::DeclareSet(Set set) {
    // drop cards that belong to the particular set
    for(int i = 0; i < num_cards; ++i) {
        Set current_set(cards[i].suit, Set::DetermineSetType(cards[i].value));

        if(current_set == set) {
            cards.erase(cards.begin() + i);
            i -= 1;
            num_cards -= 1;
        }
    }

    // reset the declare flag
    brain.declare = false;
}

void Player::ReceiveTurnInfo(int from, int to, Card card, bool success) {
    // if the card is a required card, update its status
    if(brain.IsCardRequired(card)) {
        // check to see if the turn was a success
        if(success)
            brain.ConfirmPlayerForCard(card, to);
        else {
            brain.DeletePlayerFromCard(card, to);
            brain.DeletePlayerFromCard(card, from);
        }
    }
}