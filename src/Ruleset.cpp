#include "Ruleset.h"
#include <algorithm>
#include "helper.h"

Ruleset::Ruleset() {
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

bool Ruleset::isTrump(Card card) {
    return contains(m_trumpCards, card);
}

bool Ruleset::containsTrump(std::vector<Card> cards) {
    for (Card c : cards)
        if (isTrump(c)) return true;
    return false;
}

bool Ruleset::containsType(std::vector<Card> cards, Card card) {
    if (isTrump(card))
        return containsTrump(cards);
    for (Card c: cards)
        if (!isTrump(c) && c.suit() == card.suit())
            return true;
    return false;
}

bool Ruleset::isSameType(Card c1, Card c2) {
    if (isTrump(c1) && isTrump(c2)) return true;
    else {
        if (isTrump(c1) || isTrump(c2)) return false;
        return c1.suit() == c2.suit();
    }
}

bool Ruleset::isHigher(Card secondCard, Card firstCard) {
    //overall value changes in the constructor of another rule set
    //special order rules here
    if (secondCard == firstCard && firstCard == Card(Suit::HEARTS, CardValue::TEN))return true;//both H1
    //regular rules here
    if (isTrump(firstCard)) {
        if (!isTrump(secondCard))
            return false;
        return std::distance(std::find(m_trumpCards.begin(), m_trumpCards.end(), firstCard),
                             std::find(m_trumpCards.begin(), m_trumpCards.end(), secondCard)) > 0;
    } else {
        if (isTrump(secondCard)) return true;
        if (firstCard.suit() != secondCard.suit()) return false;
        //enums are sorted by value
        return firstCard.value() < secondCard.value();
    }
}

int Ruleset::getValue(Card c) {
    switch(c.value()){
        case CardValue::NINE:
            return 0;
        case CardValue::TEN:
            return 10;
        case CardValue::JACK:
            return 2;
        case CardValue::QUEEN:
            return 3;
        case CardValue::KING:
            return 4;
        case CardValue::ASS:
            return 11;
    }
    return 0;
}




