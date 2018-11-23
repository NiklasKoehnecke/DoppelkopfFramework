//
// Created by Niklas_Laptop on 23.11.2018.
//

#ifndef DOPPELKOPF_PLAYER_H
#define DOPPELKOPF_PLAYER_H

#include <vector>
#include <string>
#include <ostream>
#include "card.h"

class Player {
public:
    Player(const std::string &m_name = "noName") : m_name(m_name) {}

    void setCards(std::vector<Card> cards) { m_cards = cards; };

    Card nextRound();

protected:
public:
    friend std::ostream &operator<<(std::ostream &os, const Player &player);

protected:
    std::string m_name;
    std::vector<Card> m_cards;
};


#endif //DOPPELKOPF_PLAYER_H
