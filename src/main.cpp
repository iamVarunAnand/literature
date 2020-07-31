#include "dealer.h"
#include "player.h"
#include "message.h"
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

    public: bool IsGameOver() {
        int zero_count = 0;
        for(int i = 0; i < players.size(); ++i)
            if(players[i].num_cards == 0)
                zero_count += 1;
        
        if(zero_count == players.size() - 1)
            return true;
        else
            return false;
    }

    public: void PlayGame() {
        dealer.DealCards(players);
        int turn = 0;
        
        int loop_limit = 0;
        while(!IsGameOver() && loop_limit < 1000) {
            Message msg = players[turn].GetNextMove();
            // std::cout << msg << std::endl;
            bool has_card = players[msg.player_id].ReleaseCard(msg.card);
            // std::cout << has_card << std::endl;
            
            if(has_card) {
                players[turn].ReceiveCard(msg.card);

                // check if the player wishes to declare a set
                if(players[turn].to_declare) {
                    // players[turn].ShowCards();
                    // std::cout << "[INFO] num cards before declaring = " << players[turn].num_cards << std::endl;
                    Set s = players[turn].DeclareSet();
                    std::cout << "Player " << turn << " declared set " << s << std::endl;
                    // std::cout << std::endl << s << std::endl << std::endl;
                    // std::cout << "[INFO] num cards after declaring = " << players[turn].num_cards << std::endl;
                    // players[turn].ShowCards();
                    // break;
                }

            }
            else
                turn = (turn + 1) % players.size();
            
            loop_limit += 1;
        }

        for(Player p : players)
            std::cout << p.num_cards << " ";

        // for(int i = 0; i < 4; ++i) {
        //     Message m = players[i].GetNextMove();
        //     bool has_card = players[m.player_id].CheckForCard(m.card);

        //     std::cout << has_card << std::endl;
        // }
    }

    public: friend std::ostream& operator<<(std::ostream &strm, GameManager &gm) {
        for(Player p : gm.players)
            strm << p << '\n';
        
        return strm;
    }
};

int main() {
    srand(time(nullptr));

    GameManager gm(kNumPlayers);
    gm.PlayGame();

    return 0;
}