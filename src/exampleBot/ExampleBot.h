#ifndef DOPPELKOPF_EXAMPLEBOT_H
#define DOPPELKOPF_EXAMPLEBOT_H

#include "../core/Player.h"

class ExampleBot: public Player {
public:
    ExampleBot(): Player("ExampleBot"){};

    Card nextRound() override;
};


#endif //DOPPELKOPF_EXAMPLEBOT_H
