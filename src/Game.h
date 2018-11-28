#ifndef DOPPELKOPF_GAME_H
#define DOPPELKOPF_GAME_H

#include <random>
#include "Player.h"
#include "Ruleset.h"
#include "Round.h"

class Game {
public:
    explicit Game(std::vector<Player> &players) : m_players(players) {
        initializeCards();
        m_playerPoints = std::vector<int>(4);
    }

    bool checkValidCard(size_t PlayerID, Card firstCard, Card newCard);

    std::vector<Card> getValidCards(size_t playerID, Card &c);

    std::vector<int> start();

private:
    void initializeCards();

    std::vector<std::vector<Card>> createPlayerCards(std::vector<Card> cards);

    void setRegularTeams();

    size_t getTeamMember(size_t playerID);

    bool teamMembers(size_t player1, size_t player2);

    Round playRound(size_t startingPlayer);

    std::pair<int, int> calculateLastRoundPoints(Round r, bool lastRound);

    std::vector<int> awardGamePoints(std::vector<Round> &rounds);

    std::vector<Player> m_players;
    std::vector<Card> m_allCards;
    std::vector<std::vector<Card>> m_playerCards;
    std::vector<int> m_playerPoints;
    std::vector<bool> m_teams; // 0  is contra, 1 is re
    Ruleset m_rules;
};


#endif //DOPPELKOPF_GAME_H
