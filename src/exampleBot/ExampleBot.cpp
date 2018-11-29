#include "ExampleBot.h"

Card ExampleBot::nextRound() {
    Card c = m_cards.back();
    m_cards.pop_back();
    return c;
}
