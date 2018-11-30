#include "Player.h"

std::ostream &operator<<(std::ostream &os, const Player &player) {
    os << player.m_name;
    return os;
}

Card Player::nextRound() {
    return Card(HEARTS, KING);
}

void Player::cardPlayed(size_t playerID, Card card) {
    //called everytime a card is played, even if its the own
}

void Player::playerWonCards(size_t playerID) {
    //called after a player won cards
}
