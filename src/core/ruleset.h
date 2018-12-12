#ifndef DOPPELKOPF_RULESET_H
#define DOPPELKOPF_RULESET_H

#include <vector>
#include "card.h"

class Ruleset {
public:
    Ruleset();

    bool isTrump(Card card);

    bool containsTrump(std::vector<Card> cards);

    bool containsType(std::vector<Card> cards, Card c);

    bool isHigher(const Card &highCard, const Card &newCard);

    int getValue(const Card &c);

    bool isSameType(const Card &c1, const Card &c2);

protected:
    //Trump cards need to be organized according to the value of the cards to make comparison easier
    std::vector<Card> m_trumpCards;
};


#endif //DOPPELKOPF_RULESET_H
