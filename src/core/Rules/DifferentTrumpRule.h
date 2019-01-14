#include "Rule.h"

#ifndef DOPPELKOPF_DIFFERENTTRUMPRULE_H
#define DOPPELKOPF_DIFFERENTTRUMPRULE_H

class DifferentTrumpRule : public Rule {
   protected: std::vector<Card> m_trumpCards;
public:
    virtual bool isTrump(bool previous, const Card &card){
        return contains(m_trumpCards, card);
    }

    virtual int getHighestCardID(int previous, const std::vector<Card> &cards){
        Card winningCard = cards[0];
        std::vector<Card> trumpCards;
        for(auto card : cards) {
            if(isTrump(false, card)){
                trumpCards.push_back(card);
            }
        }
        if(!trumpCards.empty()){
            winningCard = trumpCards[0];
            for(auto card : trumpCards){
                if(std::distance(std::find(m_trumpCards.begin(), m_trumpCards.end(), winningCard),
                                 std::find(m_trumpCards.begin(), m_trumpCards.end(), card)) > 0) {
                    winningCard = card;
                }
            }
        } else {
            for(auto card : cards) {
                if(winningCard.suit() == card.suit() && winningCard.value() < card.value()){
                    winningCard = card;
                }
            }
        }
        return (int)std::distance(cards.begin(),std::find(cards.begin(), cards.end(), winningCard));
    };
};

#endif
