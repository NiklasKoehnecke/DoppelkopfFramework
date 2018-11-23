#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

#include "Game.h"

const int NUMTURNS = 12;
const int NUMROUNDS = 8;
const int NUMPLAYERS = 4;

void Game::start() {
    //TODO initialize rules
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine{seed};

    for (int round = 0; round < NUMROUNDS; round++) {

        //set player cards
        std::vector<std::vector<Card>> playerCards = createPlayerCards(m_allCards, rng);
        for(int i=0;i<NUMPLAYERS;i++){
            m_players.at(i).setCards(playerCards.at(i));
        }

        //TODO await extra rules
        int startingPlayer = 0;
        for (int i = 0; i < NUMTURNS; i++) {
            startingPlayer = playRound(startingPlayer);
        }
    }
}

int Game::playRound(int startingPlayer) {
    int winner = 0;
    Player winningPlayer = m_players.at(0);
    for (int player = 0; player < NUMPLAYERS; player++) {
        Player * p = &m_players.at((player + startingPlayer) % NUMPLAYERS);
        Card playedCard = p->nextRound();
        std::cout << *p << " played: <" << playedCard << "> ";
    }
    std::cout << std::endl;
    return winner;
}

std::vector<std::vector<Card>> Game::createPlayerCards(std::vector<Card> cards, std::default_random_engine &rng) {
    std::vector<std::vector<Card>> playerCards;
    std::shuffle(std::begin(m_allCards), std::end(m_allCards), rng);
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