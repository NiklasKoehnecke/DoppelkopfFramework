#include <iostream>
#include <random>
#include <chrono>

#include "game.h"
#include "helper.h"

const int NUMTURNS = 12;
const int NUMROUNDS = 8;
const int NUMPLAYERS = 4;


std::vector<int> Game::start() {
    //enable standart rules
    m_rules = Ruleset();
    m_rules.setEnabled("WithDiamondsAsTrump");

    //TODO initialize rules

    std::vector<int> totalPlayerPoints(NUMPLAYERS);
    for (int round = 0; round < NUMROUNDS; round++) {
        std::cout << "New Round!\n";
        //set player cards
        m_playerCards = createPlayerCards(m_allCards);
        for (size_t i = 0; i < NUMPLAYERS; i++) {
            m_players.at(i).setCards(m_playerCards.at(i));
        }

        m_teams = std::vector<bool>(NUMPLAYERS);
        setRegularTeams();

        //TODO set teams with soli and wedding, adjust everything to work with those conditions
        //TODO add flag for when teams are not yet set
        //TODO await extra rules like solo
        std::vector<Round> rounds;

        //play a round
        size_t startingPlayer = 0;
        for (size_t i = 0; i < NUMTURNS; i++) {
            Round r = playRound(startingPlayer);
            rounds.push_back(r);
            size_t winner = r.getWinner();
            startingPlayer = winner;
        }
        auto playerPoints = awardGamePoints(rounds);
        printVector(playerPoints);
        for (size_t id = 0; id < NUMPLAYERS; id++) {
            totalPlayerPoints.at(id) += playerPoints.at(id);
        }
    }
    std::cout << "end result" << std::endl;
    printVector(totalPlayerPoints);
    return totalPlayerPoints;
}

void Game::setRegularTeams() {
    //regular rules:
    for (size_t i = 0; i < NUMPLAYERS; i++) {
        if (contains(m_playerCards.at(i), Card(Suit::CLUBS, CardValue::QUEEN)))
            m_teams.at(i) = true;
    }
}

std::vector<size_t> Game::getTeamMember(size_t playerID) {
    std::vector<size_t> members;
    for (size_t i = 0; i < m_teams.size(); i++) {
        if (i != playerID && m_teams.at(playerID) == m_teams.at(i))
            members.push_back(i);
    }
    return members;
}

//This will not work correctly if there is a wedding and teams are not yet determined
//TODO add flag
bool Game::teamMembers(size_t player1, size_t player2) {
    return player1 == player2 || contains(getTeamMember(player1), player2);
}

std::pair<int, int> Game::calculateLastRoundPoints(Round r, bool lastRound) {
    size_t startingPlayer = r.getStartPosition();
    size_t winner = r.getWinner();

    int rawCardPoints = 0;
    int gamePoints = 0;
    for (size_t i = 0; i < NUMPLAYERS; i++) {
        size_t playerID = (i + startingPlayer) % NUMPLAYERS;
        Card playedCard = r.playedCards().at(playerID);
        rawCardPoints += m_rules.getValue(playedCard);

        //Catch fox
        if (playedCard.value() == CardValue::ASS && playedCard.suit() == Suit::DIAMONDS) {
            if (!teamMembers(playerID, winner))
                ++gamePoints;
        }
        //Catch CJ and win with it
        if (lastRound) {
            Card cj = Card(Suit::CLUBS, CardValue::JACK);
            if (r.playedCards().at(winner) == cj) //win with it
                ++gamePoints;
            for (size_t j = 0; j < NUMPLAYERS; j++) { //catch it
                if (!teamMembers(j, winner)) {
                    if (r.playedCards().at(j) == cj)
                        ++gamePoints;
                }
            }
        }

    }
    return std::pair<int, int>(rawCardPoints, gamePoints);

}

bool Game::hasCard(size_t playerID, Card card){
   auto playerHand = m_playerCards.at(playerID);
   return contains(playerHand, card);
}

bool Game::checkValidCard(size_t playerID, Card firstCard, Card newCard) {
    auto cards = m_playerCards.at(playerID);
    //Card available?
    if (!hasCard(playerID, newCard)) return false;
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

std::vector<int> Game::awardGamePoints(std::vector<Round> &rounds) {
    std::vector<int> playerPoints(4);
    std::vector<int> roundPoints(4);

    for (size_t turn = 0; turn < rounds.size(); turn++) {
        size_t winner;
        winner = rounds.at(turn).getWinner();
        auto result = calculateLastRoundPoints(rounds.at(turn), turn == NUMROUNDS - 1);
        roundPoints.at(winner) += result.first;
        playerPoints.at(winner) += result.second;
    }
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
    //TODO: Adjust with team size != 2 (determine how to do 1 wins vs 3 and how 0.X points are handled)
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

Round Game::playRound(size_t startingPlayer) {
    std::vector<Card> playedCards; //this will be overridden

    for (size_t player = 0; player < NUMPLAYERS; player++) {
        size_t playerID = (player + startingPlayer) % NUMPLAYERS;
        Player *p = &m_players.at(playerID);
        auto currentPlayerCards = &m_playerCards.at(playerID);

        Card playedCard = p->nextRound();

        // TODO: We might want some kind of error message if bots fail to make fine moves
        if(player == 0 && !hasCard(playerID, playedCard)) {
            // If he is the first one to move, and he doesn't chooses a card he has, play his first card
            playedCard = m_playerCards[playerID][0];
        }
        if(player != 0 && !checkValidCard(playerID, playedCards[0], playedCard)){
            //if an invalid card was played, choose a random card to play
            auto validCards = getValidCards(playerID, playedCards[0]);
            auto idx = size_t(randomInt(0, validCards.size() - 1));
            playedCard = validCards.at(idx);
        }

        //actually play the card
        currentPlayerCards->erase(std::find(currentPlayerCards->begin(), currentPlayerCards->end(), playedCard));
        playedCards.push_back(playedCard);

        //Notify all players that a card was played
        for(Player p : m_players){
            p.cardPlayed(playerID,playedCard);
        }
        std::cout << *p << " played: <" << playedCard << "> ";
    }
    int winningCardPosition = m_rules.getHighestCardID(playedCards);
    int winningCardPlayerID = (winningCardPosition + startingPlayer) % NUMPLAYERS;
    std::cout << "winner: " << m_players.at(winningCardPlayerID) << std::endl;
    for(Player p : m_players){
        p.playerWonCards(winningCardPlayerID);
    }
    return Round(playedCards, winningCardPlayerID, startingPlayer);
}

std::vector<std::vector<Card>> Game::createPlayerCards(std::vector<Card> cards) {
    std::vector<std::vector<Card>> playerCards;
    auto s1 = static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::seed_seq seed{s1};
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


