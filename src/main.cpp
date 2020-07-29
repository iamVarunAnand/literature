#include "dealer.h"
#include "player.h"
#include "message.h"
#include <iostream>
#include <vector>

class GameManager {
    private: Dealer dealer;
    private: std::vector<Player> players;

    public: GameManager(int num_players = 4) {
        dealer = Dealer();
        for(int i = 0; i < num_players; ++i) {
            players.push_back(Player(i));
        }
    }

    public: void PlayGame() {
        dealer.DealCards(players);

        Message msg = players[0].GetNextMove();
        std::cout << msg << std::endl;
        bool has_card = players[msg.player_id].ReleaseCard(msg.card);
        std::cout << has_card << std::endl;
        
        if(has_card)
        {
            players[0].ReceiveCard(msg.card);
            std::cout << players[0].num_cards << " " << players[msg.player_id].num_cards << std::endl;
        }

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
    GameManager gm(4);
    gm.PlayGame();

    return 0;
}