#include "Rule.h"

#ifndef DOPPELKOPF_TWODIAMONDAAREHIGH_H
#define DOPPELKOPF_TWODIAMONDAAREHIGH_H

class TwoDiamondAAreHigh : public Rule {

    virtual int getHighestCardID(int previous, const std::vector<Card> &cards){
        auto it = std::find(cards.begin(), cards.end(), Card(Suit::DIAMONDS, CardValue::ASS));
        if(it != cards.end()){
           return (int) std::distance(cards.begin(), it);
        } else {
            return previous;
        }
    };
};

#endif
