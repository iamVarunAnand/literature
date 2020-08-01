#include "dealer.h"
#include "player.h"
#include "messages.h"
#include "constants.h"
#include "set.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>

class GameManager {
    private: Dealer dealer;
    private: std::vector<Player> players;

    public: GameManager(int num_players = kNumPlayers) {
        dealer = Dealer();
        for(int i = 0; i < num_players; ++i) {
            players.push_back(Player(i));
        }
    }

    public: void PlayGame() {
        dealer.DealCards(players);
        int turn = 0;
        int sets_declared = 0;
        
        while(sets_declared < kNumTotalSets) {
            AskForCardMessage afcm = players[turn].GetNextMove();
            ReleaseCardMessage rcm = players[afcm.player_id].ReleaseCard(afcm.card);
            
            if(rcm.release) {
                DeclareSetMessage dsm = players[turn].ReceiveCard(rcm.card);

                // check if the player wishes to declare a set
                if(dsm.declare) {
                    std::cout << "[INFO] player " << turn << " is declaring " << dsm.set << std::endl;
                    players[turn].DeclareSet(dsm.set);
                    players[turn].points += (1 + dsm.set.type);
                    sets_declared += 1;
                }
            }
            else
                turn = (turn + 1) % players.size();
        }

        for(int i = 0; i < players.size(); ++i) {
            std::cout << "[INFO] player " << i << " got " << players[i].points << " points" << std::endl;
        }
    }
};

int main() {
    srand(time(nullptr));

    GameManager gm(kNumPlayers);
    gm.PlayGame();

    return 0;
}