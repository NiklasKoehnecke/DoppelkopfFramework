#ifndef DOPPELKOPF_GAME_H
#define DOPPELKOPF_GAME_H

#include <random>
#include "Player.h"
#include "Ruleset.h"

class Game {
public:
    explicit Game(std::vector<Player> &players) : m_players(players) {
        initializeCards();
        m_playerPoints = std::vector<int>(4);
    }

    bool checkValidCard(size_t PlayerID, Card firstCard, Card newCard);

    std::vector<Card> getValidCards(size_t playerID, Card &c);

    void start();

private:
    void initializeCards();

    std::vector<std::vector<Card>> createPlayerCards(std::vector<Card> cards);

    size_t playRound(size_t startingPlayer);
    std::pair<int,int> calculateLastRoundPoints(size_t winner, size_t startingPlayer);

    std::vector<Player> m_players;
    std::vector<Card> m_allCards;
    std::vector<std::vector<Card>> m_playerCards;
    std::vector<Card> m_cardsLastRound;
    std::vector<int> m_playerPoints;
    Ruleset m_rules;
};


#endif //DOPPELKOPF_GAME_H
