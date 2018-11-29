#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "core/Game.h"
#include "exampleBot/ExampleBot.h"

template<typename T>
Player* createInstance() { return new T; }

typedef std::map<std::string, Player*(*)()> map_type;

map_type map;
void createPlayerMapping(){
    map.insert(std::make_pair("ExampleBot", &createInstance<ExampleBot>));
}

int main() {
    std::string filename = "../player.csv";
    std::fstream file("../player.csv");

    if (!file.is_open()) {
        std::cout << "failed to open " << filename << '\n';
    } else {
        createPlayerMapping();
        std::string p1, p2 ,p3 ,p4;
        file >> p1 >> p2 >> p3 >> p4;

        std::vector<Player> players;
        players.push_back(*(map.at(p1)()));
        players.push_back(*(map.at(p2)()));
        players.push_back(*(map.at(p3)()));
        players.push_back(*(map.at(p4)()));
        Game g = Game(players);
        g.start();
    }



    return 0;
}
