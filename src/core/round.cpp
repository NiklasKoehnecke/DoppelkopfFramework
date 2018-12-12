#include "round.h"

Round::Round(const std::vector<Card> &m_playedCards, size_t m_winner, size_t startPosition) : m_playedCards(
        m_playedCards), m_winner(m_winner), startPosition(startPosition) {}
