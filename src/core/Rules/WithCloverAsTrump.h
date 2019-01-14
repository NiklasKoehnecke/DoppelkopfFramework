#include "DifferentTrumpRule.h"

#ifndef DOPPELKOPF_WITHCLOVERASTRUMP_H
#define DOPPELKOPF_WITHCLOVERASTRUMP_H

class WithCloverAsTrump : public DifferentTrumpRule {
public:
    WithCloverAsTrump() {
        m_trumpCards = std::vector<Card>{
                Card(Suit::CLUBS, CardValue::NINE),
                Card(Suit::CLUBS, CardValue::TEN),
                Card(Suit::CLUBS, CardValue::KING),
                Card(Suit::CLUBS, CardValue::ASS),
                Card(Suit::CLUBS, CardValue::JACK),
                Card(Suit::HEARTS, CardValue::JACK),
                Card(Suit::SPADES, CardValue::JACK),
                Card(Suit::CLUBS, CardValue::JACK),
                Card(Suit::DIAMONDS, CardValue::QUEEN),
                Card(Suit::HEARTS, CardValue::QUEEN),
                Card(Suit::SPADES, CardValue::QUEEN),
                Card(Suit::CLUBS, CardValue::QUEEN),
                Card(Suit::HEARTS, CardValue::TEN)};
    }
};

#endif
