#include <core/helper.h>
#include "DifferentTrumpRule.h"

#ifndef DOPPELKOPF_WITHHEARTASTRUMP_H
#define DOPPELKOPF_WITHHEARTASTRUMP_H

class WithHeartAsTrump : public DifferentTrumpRule {
public:
    WithHeartAsTrump() {
        m_trumpCards = std::vector<Card>{
                Card(Suit::HEARTS, CardValue::NINE),
                Card(Suit::HEARTS, CardValue::KING),
                Card(Suit::HEARTS, CardValue::ASS),
                Card(Suit::DIAMONDS, CardValue::JACK),
                Card(Suit::SPADES, CardValue::JACK),
                Card(Suit::CLUBS, CardValue::JACK),
                Card(Suit::DIAMONDS, CardValue::QUEEN),
                Card(Suit::HEARTS, CardValue::QUEEN),
                Card(Suit::SPADES, CardValue::QUEEN),
                Card(Suit::CLUBS, CardValue::QUEEN),
                Card(Suit::HEARTS, CardValue::TEN)};
    }
};

#endif //DOPPELKOPF_WITHOUTTRUMP_H
