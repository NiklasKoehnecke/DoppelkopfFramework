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
        std::vector<int> playerPoints(4);

        m_playerCards = createPlayerCards(m_allCards);
        for (size_t i = 0; i < NUMPLAYERS; i++) {
            m_players.at(i).setCards(m_playerCards.at(i));
        }

        std::vector<bool> teams(4);
        std::vector<std::vector<Card>> wonCards(4);

        //TODO await extra rules like solo

        std::vector<int> roundPoints(4);
        //play a round
        int startingPlayer = 0;
        for (size_t i = 0; i < NUMTURNS; i++) {
            m_cardsLastRound = std::vector<Card>();
            std::cout << "New Round!\n";
            size_t winner = playRound(startingPlayer);
            auto result = calculateLastRoundPoints(winner, startingPlayer);
            roundPoints.at(winner)+=result.first;
            playerPoints.at(winner)+=result.second;
            startingPlayer = winner;
        }
        //TODO Calculate points of players
    }
}

std::pair<int,int> calculateLastRoundPoints(size_t winner, size_t startingPlayer) {
    //TODO calculate amount of points and stuff like foxes and CJ's
    int rawPoints;
    for (size_t i = 0; i < NUMPLAYERS; i++) {
        size_t playerID = (i + startingPlayer) % NUMPLAYERS;

    }

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

//sets m_cardsLastRound
size_t Game::playRound(size_t startingPlayer) {
    size_t winner = startingPlayer;
    Card winningCard(Suit::DIAMONDS, CardValue::NINE); //dummy card
    std::vector<Card> playedCards(4);

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
        playedCards.at(playerID) = playedCard;

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
    std::random_device rd;
    std::mt19937 g(rd());
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
