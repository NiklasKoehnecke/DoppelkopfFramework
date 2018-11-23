#ifndef DOPPELKOPF_GAME_H
#define DOPPELKOPF_GAME_H

#include <random>
#include "Player.h"

class Game {
public:
    Game(std::vector<Player> &players) : m_players(players) {
        initializeCards();
    }

    void start();

private:
    void initializeCards();

    std::vector<std::vector<Card>> createPlayerCards(std::vector<Card> cards, std::default_random_engine &rng);

    int playRound(int startingPlayer);


    std::vector<Player> m_players;
    std::vector<Card> m_allCards;
};


#endif //DOPPELKOPF_GAME_H
