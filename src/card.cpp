//
// Created by Niklas_Laptop on 23.11.2018.
//

#include "card.h"

std::string suitName(Suit s) {
    switch (s) {
        case DIAMONDS:
            return "D";
        case HEARTS:
            return "H";
        case SPADES:
            return "S";
        case CLUBS:
            return "C";
    }
}

std::string valueName(CardValue v) {
    switch (v) {
        case NINE:
            return "9";
        case JACK:
            return "J";
        case QUEEN:
            return "Q";
        case KING:
            return "K";
        case TEN:
            return "1";
        case ASS:
            return "A";
    }
}

std::ostream &operator<<(std::ostream &os, const Card &card) {
    os << suitName(card.m_suit) << valueName(card.m_value);
    return os;
}

