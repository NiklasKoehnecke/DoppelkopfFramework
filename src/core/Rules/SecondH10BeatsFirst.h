#include "Rule.h"

#ifndef DOPPELKOPF_SECONDH10BEATSFIRST_H
#define DOPPELKOPF_SECONDH10BEATSFIRST_H

class SecondH10BeatsFirst : public Rule {

    int getHighestCardID(int previous, const std::vector<Card> &cards) override{
        auto first = std::find(cards.begin(), cards.end(), Card(Suit::HEARTS, CardValue::TEN));
        if(first != cards.end()){
           auto second = std::find(first + 1, cards.end(), Card(Suit::HEARTS, CardValue::TEN));
           if(second != cards.end()) {
               return (int) std::distance(cards.begin(), second);
           }
        }
        return previous;
    };
};

#endif
