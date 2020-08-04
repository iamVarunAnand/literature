#include "dealer.h"
#include "player.h"
#include "messages.h"
#include "constants.h"
#include "set.h"
#include "renderer.h"
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
            AskForCardMessage afcm = players[turn].PlayNextMove();
            ReleaseCardMessage rcm = players[afcm.player_id].ReleaseCardTo(afcm.card, turn);

            std::cout << "[AFCM] player " << turn << " asked player " << afcm.player_id << " for card " << afcm.card << ".\n";
            std::cout << "[RCM] player " << afcm.player_id << " replied " << rcm.release << std::endl << std::endl;

            // broadcast turn info to all players
            for(Player p : players)
                p.ReceiveTurnInfo(turn, afcm.player_id, afcm.card, rcm.release);
            
            if(rcm.release) {
                DeclareSetMessage dsm = players[turn].ReceiveCardFrom(rcm.card, afcm.player_id);

                // check if the player wishes to declare a set
                if(dsm.declare) {
                    std::cout << "[DSM] player " << turn << " is declaring " << dsm.set << std::endl;

                    players[turn].DeclareSet(dsm.set);
                    players[turn].points += (1 + dsm.set.type);
                    sets_declared += 1;
                }
            }
            else
                turn = afcm.player_id;
        }

        std::cout << std::endl << "Final results: " << std::endl;
        for(int i = 0; i < players.size(); ++i) {
            std::cout << "\tplayer " << i << " got " << players[i].points << " points" << std::endl;
        }
    }
};

int main() {
    srand(time(nullptr));

    GameManager gm(kNumPlayers);

    clock_t start = clock();
    gm.PlayGame();
    clock_t end = clock();

    std::cout << "[INFO] game took " << (double)(end - start) / (double)CLOCKS_PER_SEC << " seconds" << std::endl;

    return 0;
}