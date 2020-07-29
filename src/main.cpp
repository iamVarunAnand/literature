#include "dealer.h"
#include "player.h"
#include "message.h"
#include <iostream>
#include <vector>

class GameManager {
    private: std::vector<Player> players;

    public: GameManager(int num_players = 4) {
        for(int i = 0; i < num_players; ++i) {
            players.push_back(Player(0));
        }
    }

    public: void PlayGame() {
        for(int i = 0; i < 4; ++i) {
            Message m = players[i].GetNextMove();
            bool has_card = players[m.player_id].CheckForCard(m.card);

            std::cout << has_card << std::endl;
        }
    }

    public: friend std::ostream& operator<<(std::ostream &strm, GameManager gm) {
        for(Player p : gm.players)
            strm << p << '\n';
        
        return strm;
    }
};

int main() {
    GameManager gm(4);

    std::cout << gm << std::endl;
    gm.PlayGame();

    return 0;
}