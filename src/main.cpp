#include "dealer.h"
#include "player.h"
#include "message.h"
#include <iostream>
#include <vector>
#include <cstdlib>

class GameManager {
    private: Dealer dealer;
    private: std::vector<Player> players;

    public: GameManager(int num_players = 4) {
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

        while(!IsGameOver()) {
            Message msg = players[turn].GetNextMove();
            std::cout << msg << std::endl;
            bool has_card = players[msg.player_id].ReleaseCard(msg.card);
            std::cout << has_card << std::endl;
            
            if(has_card) 
                players[turn].ReceiveCard(msg.card);
            else
                turn = (turn + 1) % players.size();
        }

        for(Player p : players)
            std::cout << p.num_cards << ' ';
        
        std::cout << std::endl;

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

    GameManager gm(4);
    gm.PlayGame();

    return 0;
}