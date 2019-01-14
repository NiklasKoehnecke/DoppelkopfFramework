#ifndef DOPPELKOPF_RULESET_H
#define DOPPELKOPF_RULESET_H

#include <vector>
#include <set>
#include <string.h>
#include "card.h"
#include "Rules/Rule.h"
#include "Rules/WithoutTrump.h"
#include "Rules/WithDiamondsAsTrump.h"
#include "Rules/WithSpadesAsTrump.h"
#include "Rules/WithHeartAsTrump.h"
#include "Rules/WithCloverAsTrump.h"
#include "Rules/SecondH10BeatsFirst.h"
#include "Rules/TwoDiamondAAreHigh.h"
#include "Rules/WithJacksAsTrump.h"
#include "Rules/WithQueensAsTrump.h"


// This class takes care of which card will be the highest card,
// and what is trump and what not.
class Ruleset {
public:
    Ruleset();

    bool isTrump(const Card &card);

    bool containsTrump(const std::vector<Card> &cards);

    bool containsType(const std::vector<Card> &cards, const Card &c);

    int getHighestCardID(const std::vector<Card> &cards);

    int getValue(const Card &c);

    bool isSameType(const Card &c1, const Card &c2);

    void setEnabled(std::string rule);

    bool isEnabled(std::string rule);

    void setDisabled(std::string rule);

    void clearRules();

private:
    void rebuildRuleInstances();
    // This defines the order in which the rules will be executed
    std::vector<std::pair<std::string, Rule*>> m_nameToRule;
    std::set<std::string> m_enabledRules;
    std::vector<Rule*> m_ruleInstances;
};


#endif //DOPPELKOPF_RULESET_H
