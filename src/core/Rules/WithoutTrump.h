#include "Rule.h"
#include "WithDiamondsAsTrump.h"

#ifndef DOPPELKOPF_WITHOUTTRUMP_H
#define DOPPELKOPF_WITHOUTTRUMP_H

class WithoutTrump : public WithDiamondsAsTrump {
    bool isTrump(bool previous, const Card &card) override{
        return false;
    }
};

#endif //DOPPELKOPF_WITHOUTTRUMP_H
