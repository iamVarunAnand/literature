#include "dealer.h"
#include "player.h"
#include "message.h"
#include <iostream>

int main() {
    Dealer d;
    Player p(0);

    Message msg = p.GetNextMove();

    std::cout << msg;

    return 0;
}