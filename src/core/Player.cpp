#include "Player.h"

std::ostream &operator<<(std::ostream &os, const Player &player) {
    os << "m_name: " << player.m_name;
    return os;
}
