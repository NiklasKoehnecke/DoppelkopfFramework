//
// Created by Niklas_Laptop on 23.11.2018.
//

#ifndef DOPPELKOPF_CARD_H
#define DOPPELKOPF_CARD_H

#include <ostream>

enum Suit{
    DIAMONDS,
    HEARTS,
    SPADES,
    CLUBS,

};

enum CardValue{
    NINE,
    JACK,
    QUEEN,
    KING,
    TEN,
    ASS
};

class Card {
public:
    friend std::ostream &operator<<(std::ostream &os, const Card &card);
    Card(Suit suit, CardValue value) : m_suit(suit), m_value(value) {}

private:
    Suit m_suit;
    CardValue m_value;

};


#endif //DOPPELKOPF_CARD_H
