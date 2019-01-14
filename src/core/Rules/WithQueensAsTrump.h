#include <core/helper.h>
#include "DifferentTrumpRule.h"

#ifndef DOPPELKOPF_WITHQUEENSASTRUMP_H
#define DOPPELKOPF_WITHQUEENSASTRUMP_H

class WithQueensAsTrump : public DifferentTrumpRule {
public:
    WithQueensAsTrump() {
        m_trumpCards = std::vector<Card>{
                Card(Suit::DIAMONDS, CardValue::QUEEN),
                Card(Suit::HEARTS, CardValue::QUEEN),
                Card(Suit::SPADES, CardValue::QUEEN),
                Card(Suit::CLUBS, CardValue::QUEEN),
                };
    }
};

#endif
