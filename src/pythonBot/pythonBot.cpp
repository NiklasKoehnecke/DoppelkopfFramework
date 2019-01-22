#include "pythonBot.h"
#include <Python.h>

PythonBot::PythonBot() {
    Py_Initialize();
}

PythonBot::~PythonBot() {
    Py_Finalize();
}

Card PythonBot::nextRound() {
    Card c = m_cards.back();
    m_cards.pop_back();
    return c;
}

void PythonBot::setCards(std::vector<Card> cards) {
    Player::setCards(cards);
}

void PythonBot::cardPlayed(size_t playerID, Card card) {
    Player::cardPlayed(playerID, card);
}

void PythonBot::playerWonCards(size_t playerID) {
    Player::playerWonCards(playerID);
}

