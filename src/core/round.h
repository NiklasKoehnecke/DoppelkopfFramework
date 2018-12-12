#ifndef DOPPELKOPF_ROUND_H
#define DOPPELKOPF_ROUND_H


#include <vector>
#include "card.h"

class Round {
public:
    Round(const std::vector<Card> &m_playedCards, size_t m_winner, size_t startPosition);

    const std::vector<Card> &playedCards() const {
        return m_playedCards;
    }

    size_t getWinner() const {
        return m_winner;
    }

    size_t getStartPosition() const {
        return startPosition;
    }

private:
    std::vector<Card> m_playedCards;
    size_t m_winner;
    size_t startPosition;
};


#endif //DOPPELKOPF_ROUND_H
