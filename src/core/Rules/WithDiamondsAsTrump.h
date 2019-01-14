#include <core/helper.h>
#include "DifferentTrumpRule.h"

#ifndef DOPPELKOPF_WITHDIAMONDSASTRUMP_H
#define DOPPELKOPF_WITHDIAMONDSASTRUMP_H

class WithDiamondsAsTrump : public DifferentTrumpRule {

public:
    WithDiamondsAsTrump() {
        m_trumpCards = std::vector<Card>{
                Card(Suit::DIAMONDS, CardValue::NINE),
                Card(Suit::DIAMONDS, CardValue::TEN),
                Card(Suit::DIAMONDS, CardValue::KING),
                Card(Suit::DIAMONDS, CardValue::ASS),
                Card(Suit::DIAMONDS, CardValue::JACK),
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
