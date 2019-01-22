#ifndef DOPPELKOPF_PYTHONBOT_H
#define DOPPELKOPF_PYTHONBOT_H

#include "../core/player.h"

class PythonBot: public Player {
public:
    PythonBot();

    Card nextRound() override;

    void cardPlayed(size_t playerID, Card card) override;

    void playerWonCards(size_t playerID) override;

    void setCards(std::vector<Card> cards) override;

    virtual ~PythonBot();
};


#endif //DOPPELKOPF_EXAMPLEBOT_H
