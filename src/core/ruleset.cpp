#include "ruleset.h"


Ruleset::Ruleset(){
    m_nameToRule.push_back(std::make_pair("WithDiamondsAsTrump", new WithDiamondsAsTrump()));
    m_nameToRule.push_back(std::make_pair("WithoutTrump" ,  new WithoutTrump()));
    m_nameToRule.push_back(std::make_pair("WithSpadesAsTrump",new  WithSpadesAsTrump()));
    m_nameToRule.push_back(std::make_pair("WithCloverAsTrump",new WithCloverAsTrump()));
    m_nameToRule.push_back(std::make_pair("WithHeartAsTrump",new WithHeartAsTrump()));
    m_nameToRule.push_back(std::make_pair("WithJacksAsTrump",new WithJacksAsTrump()));
    m_nameToRule.push_back(std::make_pair("WithQueensAsTrump",new WithQueensAsTrump()));
    m_nameToRule.push_back(std::make_pair("SecondH10BeatsFirstH10",new SecondH10BeatsFirst()));
    m_nameToRule.push_back(std::make_pair("TwoDiamondAAreHigh",new TwoDiamondAAreHigh()));
}


bool Ruleset::isTrump(const Card &card) {
    bool previous = false;
    for(auto rule : m_ruleInstances){
        previous = rule->isTrump(previous, card);
    }
    return previous;
}

bool Ruleset::containsTrump(const std::vector<Card> &cards) {
    for (Card c : cards)
        if (isTrump(c)) return true;
    return false;
}

bool Ruleset::containsType(const std::vector<Card> &cards, const Card &card) {
    if (isTrump(card))
        return containsTrump(cards);
    for (Card c: cards)
        if (!isTrump(c) && c.suit() == card.suit())
            return true;
    return false;
}

bool Ruleset::isSameType(const Card &c1, const Card &c2) {
    if (isTrump(c1) && isTrump(c2)) return true;
    else {
        if (isTrump(c1) || isTrump(c2)) return false;
        return c1.suit() == c2.suit();
    }
}

// cards has to be sorted after the order the cards where played in
int Ruleset::getHighestCardID(const std::vector<Card> &cards) {
    int previous = 0;
    for(auto rule : m_ruleInstances){
        previous = rule->getHighestCardID(previous, cards);
    }
    return previous;
}

int Ruleset::getValue(const Card &c) {
    switch(c.value()){
        case CardValue::NINE:
            return 0;
        case CardValue::TEN:
            return 10;
        case CardValue::JACK:
            return 2;
        case CardValue::QUEEN:
            return 3;
        case CardValue::KING:
            return 4;
        case CardValue::ASS:
            return 11;
    }
    return 0;
}

void Ruleset::rebuildRuleInstances(){
    m_ruleInstances.clear();
    for(const auto pair : m_nameToRule){
        if(isEnabled(pair.first)){
            m_ruleInstances.push_back(pair.second);
        }
    }
}

void Ruleset::setEnabled(std::string rule) {
    bool found = false;
    for(const auto pair : m_nameToRule){
        if(pair.first == rule){
            found = true;
        }
    }
    if(!found){
        throw std::invalid_argument("Rule is not implemented");
    }
    m_enabledRules.insert(rule);
    rebuildRuleInstances();
}

bool Ruleset::isEnabled(std::string rule) {
    return m_enabledRules.find(rule) != m_enabledRules.end();
}

void Ruleset::setDisabled(std::string rule) {
    m_enabledRules.erase(rule);
    rebuildRuleInstances();
}

void Ruleset::clearRules() {
    m_enabledRules.clear();
    rebuildRuleInstances();
}




