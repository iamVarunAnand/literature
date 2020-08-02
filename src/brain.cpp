#include "player.h"
#include "constants.h"
#include "set.h"
#include "card.h"
#include <utility>

void Player::Brain::UpdateSetCounts(Set set, bool increment) {
    if(set_counts.find(set) == set_counts.end()) {
        set_counts[set] = 1;
    }
    else {    
        if(increment)
            set_counts[set] += 1;
        else {
            set_counts[set] -= 1;
            if(set_counts[set] == 0)
                ForgetSetCounts(set);
        }
    }
}

void Player::Brain::ForgetSetCounts(Set set) {
    set_counts.erase(set);
}

bool Player::Brain::IsDeclare(Set set) {
    if(set_counts[set] == kNumCardsPerSet)
        return true;
    else
        return false;
}

std::vector<Set> Player::Brain::FindPlayableSets() {
    std::vector<Set> playable;
    for(std::pair<Set, int> sc : set_counts)
        playable.push_back(sc.first);
    
    

    return playable;
}