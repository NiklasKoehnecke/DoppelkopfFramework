#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <chrono>
#include <random>

#include "core/game.h"
#include "exampleBot/exampleBot.h"

template<typename T>
Player *createInstance() { return new T; }

typedef std::map<std::string, Player *(*)()> map_type;

map_type map;

void createPlayerMapping() {
    map.insert(std::make_pair("ExampleBot", &createInstance<ExampleBot>));
}

std::vector<std::pair<std::string, int>> readStats(std::fstream &file) {

    int numPlayers;
    //read all player data
    std::vector<std::pair<std::string, int>> botStats;
    file >> numPlayers;
    std::string player;
    int points;
    for (int i = 0; i < numPlayers; i++) {
        file >> player;
        file >> points;
        botStats.push_back(std::make_pair(player, points));
    }
    return std::move(botStats);

}

void writeStats(std::fstream &file, std::vector<std::pair<std::string, int>> &stats) {
    file.clear();
    file.seekp(0);
    file << stats.size() << "\n";
    for (auto playerStat: stats) {
        file << playerStat.first << " " << playerStat.second << "\n";
    }
    file.flush();
    file.close();
}


int main() {
    std::string filename = "../player.csv";
    std::fstream file("../player.csv");

    if (!file.is_open()) {
        std::cout << "failed to open " << filename << '\n';
    } else {
        createPlayerMapping();

        std::vector<std::pair<std::string, int>> botStats = readStats(file);
        auto s1 = static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::seed_seq seed{s1};
        std::mt19937 mt(seed);
        std::shuffle(botStats.begin(), botStats.end(), mt);

        //draw players to play and start game
        std::vector<Player> players;
        for (int i = 0; i < 4; i++) {
            players.push_back(*(map.at(botStats.at(i).first)()));
        }

        Game g = Game(players);
        auto result = g.start();
        for (int i = 0; i < 4; i++) {
            botStats.at(i).second += result.at(i);
        }
        writeStats(file, botStats);
    }


    return 0;
}
