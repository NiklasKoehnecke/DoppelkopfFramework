#include "DifferentTrumpRule.h"

#ifndef DOPPELKOPF_WITHJACKSASTRUMP_H
#define DOPPELKOPF_WITHJACKSASTRUMP_H

class WithJacksAsTrump : public DifferentTrumpRule {
public: WithJacksAsTrump() {
        m_trumpCards = std::vector<Card>{
                Card(Suit::DIAMONDS, CardValue::JACK),
                Card(Suit::HEARTS, CardValue::JACK),
                Card(Suit::SPADES, CardValue::JACK),
                Card(Suit::CLUBS, CardValue::JACK),
        };
    }
};

#endif //DOPPELKOPF_WITHOUTTRUMP_H
