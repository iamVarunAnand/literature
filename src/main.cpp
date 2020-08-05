#include "dealer.h"
#include "player.h"
#include "messages.h"
#include "constants.h"
#include "set.h"
#include "renderer.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>

class GameManager {
    private: Dealer dealer;
    private: std::vector<Player> players;

    private: void CanPlayerBeRemoved(int pid) {
        if(players[pid].num_cards == 0) {
            // remove the player from the game
            players[pid].isplaying = false;

            std::cout << "[RPFGM] player " << pid << " has left the game" << std::endl;
            
            // inform the other players who are still playing
            for(int i = 0; i < kNumPlayers; ++i) {
                if(i != pid && players[i].isplaying == true) 
                    players[i].ReceivePlayerHasLeftGameUpdate(pid);
            }
        }
    }

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
            std::cout << "[RCM] player " << afcm.player_id << " replied " << rcm.release << std::endl;

            for(int i = 0; i < kNumPlayers; ++i)
                players[i].ReceiveTurnInfo(afcm.player_id, turn, afcm.card, rcm.release);

            if(rcm.release) {
                DeclareSetMessage dsm = players[turn].ReceiveCardFrom(rcm.card, afcm.player_id);

                // check if the player who gave the card can be removed from the game
                CanPlayerBeRemoved(afcm.player_id);

                // check if the player wishes to declare a set
                if(dsm.declare) {
                    std::cout << "[DSM] player " << turn << " is declaring " << dsm.set << std::endl;

                    players[turn].DeclareSet(dsm.set);
                    players[turn].points += (1 + dsm.set.type);
                    sets_declared += 1;

                    // check if the player who declared the set can be removed from the game
                    CanPlayerBeRemoved(turn);
                }
            }

            // update the turn
            // if player received the card, declared the set and left the game
            if(rcm.release && players[turn].isplaying == false) {
                // check if the game has come to an end
                if(sets_declared == kNumTotalSets)
                    turn = -1;

                // turn goes to next player who is still playing
                else {
                    turn = (turn + 1) % kNumPlayers;
                    while(players[turn].isplaying == false)
                        turn = (turn + 1) % kNumPlayers;
                }
            }
            else if (!rcm.release)
                turn = afcm.player_id;
            
            std::cout << "turn goes to player " << turn << std::endl << std::endl;
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