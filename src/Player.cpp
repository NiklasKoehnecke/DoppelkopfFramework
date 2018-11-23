//
// Created by Niklas_Laptop on 23.11.2018.
//

#include "Player.h"

Card Player::nextRound() {
    Card c = m_cards.back();
    m_cards.pop_back();
    return c;
}

std::ostream &operator<<(std::ostream &os, const Player &player) {
    os << "m_name: " << player.m_name;
    return os;
}
