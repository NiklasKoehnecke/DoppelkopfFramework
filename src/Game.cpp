#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

#include "Game.h"
#include "helper.h"

const int NUMTURNS = 12;
const int NUMROUNDS = 8;
const int NUMPLAYERS = 4;


void Game::start() {
    m_rules = Ruleset();
    //TODO initialize rules
    for (int round = 0; round < NUMROUNDS; round++) {
        //set player cards
        std::vector<int> playerPoints(NUMPLAYERS);
        m_playerCards = createPlayerCards(m_allCards);
        for (size_t i = 0; i < NUMPLAYERS; i++) {
            m_players.at(i).setCards(m_playerCards.at(i));
        }

        m_teams = std::vector<bool>(NUMPLAYERS);
        setRegularTeams();
        //TODO set teams with soli and wedding, adjust everything to work with those conditions
        //TODO await extra rules like solo

        std::vector<int> roundPoints(NUMPLAYERS);
        //play a round
        int startingPlayer = 0;
        for (size_t i = 0; i < NUMTURNS; i++) {
            //m_cardsLastRound = std::vector<Card>();
            std::cout << "New Round!\n";
            size_t winner = playRound(startingPlayer);
            auto result = calculateLastRoundPoints(winner, startingPlayer, i - 1 == NUMTURNS);
            roundPoints.at(winner) += result.first;
            playerPoints.at(winner) += result.second;
            startingPlayer = winner;
        }
        printVector(playerPoints);
        playerPoints = awardGamePoints(roundPoints, playerPoints);
        printVector(playerPoints);
        //TODO Calculate points of players
    }
}

void Game::setRegularTeams() {
    //regular rules:
    for (size_t i = 0; i < NUMPLAYERS; i++) {
        if (contains(m_playerCards.at(i), Card(Suit::CLUBS, CardValue::QUEEN)))
            m_teams.at(i) = true;
    }
}

size_t Game::getTeamMember(size_t playerID) {
    for (size_t i = 0; i < m_teams.size(); i++) {
        if (i != playerID && m_teams.at(playerID) == m_teams.at(i))
            return i;
    }
    return 5;
}

bool Game::teamMembers(size_t player1, size_t player2) {
    return player1 == player2 || getTeamMember(player1) == player2;
}

std::pair<int, int> Game::calculateLastRoundPoints(size_t winner, size_t startingPlayer, bool lastRound) {
    //TODO calculate amount of points and stuff like foxes and CJ's
    int rawCardPoints = 0;
    int gamePoints = 0;
    for (size_t i = 0; i < NUMPLAYERS; i++) {
        size_t playerID = (i + startingPlayer) % NUMPLAYERS;
        Card &playedCard = m_cardsLastRound.at(playerID);
        rawCardPoints += m_rules.getValue(playedCard);

        //TODO fix this for when teams are not yet determined
        //Catch fox
        if (playedCard.value() == CardValue::ASS && playedCard.suit() == Suit::DIAMONDS) {
            if (!teamMembers(playerID, winner))
                ++gamePoints;
        }
        //Catch CJ and win with it
        if (lastRound) {
            Card cj = Card(Suit::CLUBS, CardValue::JACK);
            if (m_cardsLastRound.at(winner) == cj)
                ++gamePoints;
            for (int j = 0; j < NUMPLAYERS; j++) {
                if (!teamMembers(j, winner)) {
                    ++gamePoints;
                }
            }
        }

    }
    return std::pair<int, int>(rawCardPoints, gamePoints);

}


bool Game::checkValidCard(size_t playerID, Card firstCard, Card newCard) {
    auto cards = m_playerCards.at(playerID);
    //Card available?
    if (!contains(cards, newCard)) return false;
    //served ?
    if (m_rules.isSameType(firstCard, newCard)) return true;
        //no need to serve?
    else if (m_rules.containsType(cards, firstCard)) return false;
    return true;
}

std::vector<Card> Game::getValidCards(size_t playerID, Card &c) {
    std::vector<Card> validCards = std::vector<Card>();
    for (Card card : m_playerCards.at(playerID)) {
        if (checkValidCard(playerID, c, card))
            validCards.push_back(card);
    }
    return validCards;
}

std::vector<int> Game::awardGamePoints(std::vector<int> &roundPoints, std::vector<int> playerPoints) {
    //TODO refactor
    std::vector<int> winPoints = playerPoints;
    int team0CardPoints = 0, team1CardPoints = 0, team0winPoints = 0, team1winPoints = 0;
    for (size_t i = 0; i < NUMPLAYERS; i++) {
        if (m_teams.at(i)) {
            team1CardPoints += roundPoints.at(i);
            team1winPoints += playerPoints.at(i);
        } else {
            team0CardPoints += roundPoints.at(i);
            team0winPoints += playerPoints.at(i);
        }
    }
    printVector(m_teams);
    std::cout << team0CardPoints << " " << team1CardPoints << "\n";
    if (team0CardPoints > team1CardPoints) {
        team0winPoints += 2;
        if (team1CardPoints < 90) ++team0winPoints;
        if (team1CardPoints < 60) ++team0winPoints;
        if (team1CardPoints < 30) ++team0winPoints;
        if (team1CardPoints == 0) ++team0winPoints;
        team0winPoints -= team1winPoints;
        team1winPoints = 0;
        team1winPoints -= team0winPoints;
    } else {
        ++team1winPoints;
        if (team0CardPoints < 90) ++team1winPoints;
        if (team0CardPoints < 60) ++team1winPoints;
        if (team0CardPoints < 30) ++team1winPoints;
        if (team0CardPoints == 0) ++team1winPoints;
        team1winPoints -= team0winPoints;
        team0winPoints = 0;
        team0winPoints -= team1winPoints;
    }

    for (size_t i = 0; i < NUMPLAYERS; i++) {
        if (m_teams.at(i)) {
            playerPoints.at(i) = team1winPoints;
        } else {
            playerPoints.at(i) = team0winPoints;
        }
    }
    return playerPoints;
}

//sets m_cardsLastRound
size_t Game::playRound(size_t startingPlayer) {
    size_t winner = startingPlayer;
    Card winningCard(Suit::DIAMONDS, CardValue::NINE); //dummy card
    std::vector<Card> playedCards{winningCard, winningCard, winningCard, winningCard}; //this will be overridden

    for (size_t player = 0; player < NUMPLAYERS; player++) {
        size_t playerID = (player + startingPlayer) % NUMPLAYERS;
        Player *p = &m_players.at(playerID);
        auto currentPlayerCards = &m_playerCards.at(playerID);
        Card playedCard = p->nextRound();

        if (player == 0)
            winningCard = playedCard;
        //if an invalid card was played, choose a random card to play
        if (!checkValidCard(playerID, winningCard, playedCard)) {
            auto validCards = getValidCards(playerID, winningCard);
            auto idx = size_t(randomInt(0, validCards.size() - 1));
            playedCard = validCards.at(idx);

            if (player == 0)
                winningCard = playedCard;
        }
        currentPlayerCards->erase(std::find(currentPlayerCards->begin(), currentPlayerCards->end(), playedCard));
        playedCards.at(playerID) = playedCard; //use at to preserve player <-> card identity

        if (m_rules.isHigher(playedCard, winningCard)) {
            winningCard = playedCard;
            winner = playerID;
        }
        std::cout << *p << " played: <" << playedCard << "> ";
    }
    std::cout << "winner: " << m_players.at(winner) << std::endl;
    m_cardsLastRound = playedCards;

    return winner;
}

std::vector<std::vector<Card>> Game::createPlayerCards(std::vector<Card> cards) {
    std::vector<std::vector<Card>> playerCards;
    //TODO, actually generate random arrays, not the same every programm execution(which shuffle apparently does)
    auto s1 = static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::seed_seq seed{ static_cast<long unsigned int>(s1) };
    std::mt19937 g(seed);
    std::shuffle(cards.begin(), cards.end(), g);
    for (int i = 0; i < NUMPLAYERS; i++) {
        auto set = std::vector<Card>(cards.begin() + i * NUMTURNS, cards.begin() + (i + 1) * NUMTURNS);
        playerCards.push_back(set);
    }
    return playerCards;
}

void Game::initializeCards() {
    m_allCards = std::vector<Card>{
            Card(Suit::DIAMONDS, CardValue::NINE),
            Card(Suit::DIAMONDS, CardValue::JACK),
            Card(Suit::DIAMONDS, CardValue::QUEEN),
            Card(Suit::DIAMONDS, CardValue::KING),
            Card(Suit::DIAMONDS, CardValue::TEN),
            Card(Suit::DIAMONDS, CardValue::ASS),
            Card(Suit::HEARTS, CardValue::NINE),
            Card(Suit::HEARTS, CardValue::JACK),
            Card(Suit::HEARTS, CardValue::QUEEN),
            Card(Suit::HEARTS, CardValue::KING),
            Card(Suit::HEARTS, CardValue::TEN),
            Card(Suit::HEARTS, CardValue::ASS),
            Card(Suit::SPADES, CardValue::NINE),
            Card(Suit::SPADES, CardValue::JACK),
            Card(Suit::SPADES, CardValue::QUEEN),
            Card(Suit::SPADES, CardValue::KING),
            Card(Suit::SPADES, CardValue::TEN),
            Card(Suit::SPADES, CardValue::ASS),
            Card(Suit::CLUBS, CardValue::NINE),
            Card(Suit::CLUBS, CardValue::JACK),
            Card(Suit::CLUBS, CardValue::QUEEN),
            Card(Suit::CLUBS, CardValue::KING),
            Card(Suit::CLUBS, CardValue::TEN),
            Card(Suit::CLUBS, CardValue::ASS),
            Card(Suit::DIAMONDS, CardValue::NINE),
            Card(Suit::DIAMONDS, CardValue::JACK),
            Card(Suit::DIAMONDS, CardValue::QUEEN),
            Card(Suit::DIAMONDS, CardValue::KING),
            Card(Suit::DIAMONDS, CardValue::TEN),
            Card(Suit::DIAMONDS, CardValue::ASS),
            Card(Suit::HEARTS, CardValue::NINE),
            Card(Suit::HEARTS, CardValue::JACK),
            Card(Suit::HEARTS, CardValue::QUEEN),
            Card(Suit::HEARTS, CardValue::KING),
            Card(Suit::HEARTS, CardValue::TEN),
            Card(Suit::HEARTS, CardValue::ASS),
            Card(Suit::SPADES, CardValue::NINE),
            Card(Suit::SPADES, CardValue::JACK),
            Card(Suit::SPADES, CardValue::QUEEN),
            Card(Suit::SPADES, CardValue::KING),
            Card(Suit::SPADES, CardValue::TEN),
            Card(Suit::SPADES, CardValue::ASS),
            Card(Suit::CLUBS, CardValue::NINE),
            Card(Suit::CLUBS, CardValue::JACK),
            Card(Suit::CLUBS, CardValue::QUEEN),
            Card(Suit::CLUBS, CardValue::KING),
            Card(Suit::CLUBS, CardValue::TEN),
            Card(Suit::CLUBS, CardValue::ASS),
    };
}


