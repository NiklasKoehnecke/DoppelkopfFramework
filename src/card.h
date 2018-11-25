#ifndef DOPPELKOPF_CARD_H
#define DOPPELKOPF_CARD_H

#include <ostream>

enum Suit {
    DIAMONDS,
    HEARTS,
    SPADES,
    CLUBS,

};

enum CardValue {
    NINE,
    JACK,
    QUEEN,
    KING,
    TEN,
    ASS
};

class Card {
public:

    Card(Suit suit, CardValue value) : m_suit(suit), m_value(value) {}

    friend std::ostream &operator<<(std::ostream &os, const Card &card);

    bool operator==(const Card &rhs) const;

    bool operator!=(const Card &rhs) const;

private:
    Suit m_suit;
    CardValue m_value;
public:
    Suit suit() const;

    CardValue value() const;

};


#endif //DOPPELKOPF_CARD_H
