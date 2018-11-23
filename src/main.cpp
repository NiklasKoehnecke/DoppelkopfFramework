#include <iostream>
#include "Game.h"
int main() {
    std::vector<Player> players;
    players.push_back(Player("#1"));
    players.push_back(Player("#2"));
    players.push_back(Player("#3"));
    players.push_back(Player("#4"));
    Game g = Game(players);
    g.start();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}