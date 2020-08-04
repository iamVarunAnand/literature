#include "player.h"
#include "constants.h"
#include "set.h"
#include "card.h"
#include "algorithm"
#include <utility>
#include <unordered_set>

Player::Brain::Brain() {
    declare = false;
}

void Player::Brain::ForgetRequiredCards(Set set) {
    req_cards.erase(set);
}

void Player::Brain::AddToRequiredCards(Set set, Card card) {
    // add the card to the list of required cards
    req_cards[set].push_back(card);

    // check if the set state can be forgotten
    if(req_cards[set].size() == kNumCardsPerSet)
        ForgetRequiredCards(set);
}

void Player::Brain::DeleteFromRequiredCards(Set set, Card card) {
    // find the card and delete it
    auto it = std::find(req_cards[set].begin(), req_cards[set].end(), card);
    if(it != req_cards[set].end())
        req_cards[set].erase(it);

    // check if the set state can be forgotten (which means the set can be declared)
    if(req_cards[set].size() == 0) {
        ForgetRequiredCards(set);
        declare = true;
    }
}

void Player::Brain::UpdateRequiredCards(Card card, bool received) {
    // compute the current set
    Set set = Set(card.suit, Set::DetermineSetType(card.value));

    // check if the card has been received
    if(received) {
        // check if this is the first time a card belonging to this set is received
        if(req_cards.find(set) == req_cards.end()) {
            // grab all the cards that belong to the current set
            std::vector<Card> set_cards = Set::GetCardsInSet(set);

            // add all the set cards (except the received card) to the list of required cards
            for(Card c : set_cards)
                if(!(c == card))
                    AddToRequiredCards(set, c);
        }
        // else remove the received card from the list of required cards
        else {
            DeleteFromRequiredCards(set, card);
        }
    }
    // else the card has been released
    else {
        // add the released card to the list of required cards
        AddToRequiredCards(set, card);
    }
}

void Player::Brain::AddPlayerToCard(Card card, int pid) {
    memory[card].push_back(pid);
}

void Player::Brain::DeletePlayerFromCard(Card card, int pid) {
    auto it = std::find(memory[card].begin(), memory[card].end(), pid);
    if(it != memory[card].end())
        memory[card].erase(it);
}

void Player::Brain::ConfirmPlayerForCard(Card card, int pid) {
    std::vector<int> temp; temp.push_back(pid);
    memory[card] = temp;
}

void Player::Brain::ForgetCard(Card card) {
    memory.erase(card);
}

void Player::Brain::InitializeMemory(int pid, std::vector<Card> cards) {
    // initialize a hash set to keep track of the sets seen
    std::unordered_set<Set, SetHash> sets_seen;

    // loop through the cards and update the memory
    for(Card card : cards) {
        // calculate the set of the current card
        Set set = Set(card.suit, Set::DetermineSetType(card.value));

        // check to see if the current set has already been seen
        if(sets_seen.find(set) != sets_seen.end())
            ForgetCard(card);
        // else add all players (except this) to the cards in this set (except current card)
        else {
            // get the list of cards that belong to this set
            std::vector<Card> set_cards = Set::GetCardsInSet(set);

            for(Card c : set_cards) {
                if(!(c == card)) {
                    for(int i = 0; i < kNumPlayers; ++i)
                        if(i != pid)
                            memory[c].push_back(i);
                }
            }
        }

        // add the set to the seen sets
        sets_seen.insert(set);
    }
}

void Player::Brain::UpdateMemory(Card card, int pid, bool received) {
    // calculate the set corresponding to the card
    Set set = Set(card.suit, Set::DetermineSetType(card.value));

    // check to see if the card was received
    if(received) {
        ForgetCard(card);        
    }
    // else the card has been released
    else {
        // check to see if the cards corresponding to the current set can be forgotten
        if(req_cards.find(set) == req_cards.end()) {
            // grab the cards corresponding to the current set
            std::vector<Card> set_cards = Set::GetCardsInSet(set);

            // loop through the cards and erase them from memory
            for(Card card : set_cards) {
                if(memory.find(card) != memory.end())
                    memory.erase(card);
            }
        }
        // else confirm the receiving player to have the released card
        else
            ConfirmPlayerForCard(card, pid);
    }
}

bool Player::Brain::IsCardRequired(Card card) {
    if(memory.find(card) != memory.end())
        return true;
    else
        return false;
}

Set Player::Brain::FindSetToPlay() {
    int min_count = INT16_MAX;
    Set set_to_play;
    
    for(std::pair<Set, std::vector<Card>> rc : req_cards)
        if(rc.second.size() < min_count) {
            min_count = rc.second.size();
            set_to_play = rc.first;
        }
    
    return set_to_play;
}

AskForCardMessage Player::Brain::CheckForCertainty() {
    Card card;
    int pid = -1;

    for(auto it = memory.begin(); it != memory.end() && pid == -1; ++it) {
        if((*it).second.size() == 1) {
            card = (*it).first;
            pid = (*it).second[0];
        }
    }

    return AskForCardMessage(card, pid);
}

AskForCardMessage Player::Brain::GetNextMove(std::vector<Card> cards) {
    if(cards.size() == 0)
        return AskForCardMessage(Card(), rand() % kNumPlayers);
    else {
        AskForCardMessage afcm = CheckForCertainty();

        if(afcm.player_id != -1)
            return afcm;
        else {
            Set set = FindSetToPlay();
            
            Card card = req_cards[set][0];
            int pid = memory[card][0];

            return AskForCardMessage(card, pid);
        }
    }
}