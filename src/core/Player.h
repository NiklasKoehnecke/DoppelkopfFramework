#ifndef DOPPELKOPF_PLAYER_H
#define DOPPELKOPF_PLAYER_H

#include <vector>
#include <string>
#include <ostream>
#include "card.h"

class Player {
public:
    Player(std::string name = "noName") : m_name(name) {}

    void setCards(std::vector<Card> cards) { m_cards = std::move(cards); };

    virtual Card nextRound();

    friend std::ostream &operator<<(std::ostream &os, const Player &player);

protected:
    const std::string m_name;
    std::vector<Card> m_cards;
};


#endif //DOPPELKOPF_PLAYER_H
