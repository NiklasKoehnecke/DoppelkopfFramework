#ifndef DOPPELKOPF_RULE_H
#define DOPPELKOPF_RULE_H

// This is an empty rule. To add special rules, derive from this class
// Rules will be executed chained after one another, with each rule having the
// possibility to overwrite the previous ones. So the execution order is important,
// and will be handled in ruleset.

#include <vector>
#include "../card.h"
#include "../helper.h"


class Rule{
public:
    virtual bool isTrump(bool previous, const Card &card){
       return previous;
    }

    virtual int getHighestCardID(int previous, const std::vector<Card> &cards){
        return previous;
    };
};

#endif //DOPPELKOPF_RULE_H
