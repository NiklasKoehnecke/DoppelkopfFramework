#include <iostream>
#include <fstream>
#include "core/Game.h"
#include "exampleBot/ExampleBot.h"

int main() {
    std::string filename = "../player.csv";
    std::fstream file("../player.csv", file.trunc | file.in | file.out);

    if (!file.is_open()) {
        std::cout << "failed to open " << filename << '\n';
    } else {
        file << "name1, name2";
    }
    std::vector<Player> players;
    ExampleBot();
    players.push_back(ExampleBot("#1"));
    players.push_back(Player("#2"));
    players.push_back(Player("#3"));
    players.push_back(Player("#4"));
    Game g = Game(players);
    g.start();
    return 0;
}
