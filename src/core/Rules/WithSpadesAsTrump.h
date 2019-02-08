#include "DifferentTrumpRule.h"

#ifndef DOPPELKOPF_WITHSPADESASTRUMP_H
#define DOPPELKOPF_WITHSPADESASTRUMP_H

class WithSpadesAsTrump : public DifferentTrumpRule {
public:
    WithSpadesAsTrump() {
        m_trumpCards = std::vector<Card>{
                Card(Suit::SPADES, CardValue::NINE),
                Card(Suit::SPADES, CardValue::TEN),
                Card(Suit::SPADES, CardValue::KING),
                Card(Suit::SPADES, CardValue::ASS),
                Card(Suit::SPADES, CardValue::JACK),
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

#endif //DOPPELKOPF_WITHOUTTRUMP_H
