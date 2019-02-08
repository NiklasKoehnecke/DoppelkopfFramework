#ifndef DOPPELKOPF_EXAMPLEBOT_H
#define DOPPELKOPF_EXAMPLEBOT_H

#include "../core/player.h"

class ExampleBot: public Player {
public:
    ExampleBot(std::string name = "noName"): Player(name) {}


    Card nextRound() override;
};


#endif //DOPPELKOPF_EXAMPLEBOT_H
