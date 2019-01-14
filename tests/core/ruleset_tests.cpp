#include <gtest/gtest.h>
#include <core/ruleset.h>
#include <core/card.h>


TEST(ruleset_test, ForSameCardsFirstIsHigher){
    Ruleset ruleset;
    std::vector<Card> round = {
           Card(Suit::DIAMONDS, CardValue::NINE),
           Card(Suit::DIAMONDS, CardValue::NINE),
           Card(Suit::DIAMONDS, CardValue::ASS),
           Card(Suit::DIAMONDS, CardValue::ASS),
    };
    ruleset.setEnabled("WithDiamondsAsTrump");
    ASSERT_EQ(ruleset.getHighestCardID(round), 2);
}

TEST(ruleset_test, NonTrumpCannotBeatFirstCard){
    Ruleset ruleset;
    std::vector<Card> round = {
            Card(Suit::HEARTS, CardValue::NINE),
            Card(Suit::SPADES, CardValue::NINE),
            Card(Suit::CLUBS, CardValue::ASS),
            Card(Suit::CLUBS, CardValue::ASS),
    };
    ruleset.setEnabled("WithDiamondsAsTrump");
    ASSERT_EQ(ruleset.getHighestCardID(round), 0);
}


TEST(ruleset_test, SecondH10BeatsFirstIfActive){
    Ruleset ruleset;
    std::vector<Card> round = {
            Card(Suit::HEARTS, CardValue::TEN),
            Card(Suit::SPADES, CardValue::NINE),
            Card(Suit::HEARTS, CardValue::TEN),
            Card(Suit::CLUBS, CardValue::ASS),
    };
    ruleset.setEnabled("WithDiamondsAsTrump");
    ASSERT_EQ(ruleset.getHighestCardID(round), 0);
    ruleset.setEnabled("SecondH10BeatsFirstH10");
    ASSERT_EQ(ruleset.getHighestCardID(round), 2);
    ruleset.setDisabled("SecondH10BeatsFirstH10");
    ASSERT_EQ(ruleset.getHighestCardID(round), 0);
}

TEST(ruleset_test, TwoDiamondAAreHighIfActivated){
    Ruleset ruleset;
    std::vector<Card> round = {
            Card(Suit::HEARTS, CardValue::TEN),
            Card(Suit::SPADES, CardValue::QUEEN),
            Card(Suit::DIAMONDS, CardValue::ASS),
            Card(Suit::DIAMONDS, CardValue::ASS),
    };
    ruleset.setEnabled("WithDiamondsAsTrump");
    ASSERT_EQ(ruleset.getHighestCardID(round), 0);
    ruleset.setEnabled("TwoDiamondAAreHigh");
    ASSERT_EQ(ruleset.getHighestCardID(round), 2);
    ruleset.setDisabled("TwoDiamondAAreHigh");
    ASSERT_EQ(ruleset.getHighestCardID(round), 0);
}

TEST(ruleset_test, WithQueensAsTrump){
    Ruleset ruleset;
    std::vector<Card> round = {
            Card(Suit::HEARTS, CardValue::QUEEN),
            Card(Suit::SPADES, CardValue::QUEEN),
            Card(Suit::HEARTS, CardValue::TEN),
            Card(Suit::SPADES, CardValue::JACK),
    };
    ruleset.setEnabled("WithDiamondsAsTrump");
    ASSERT_EQ(ruleset.getHighestCardID(round), 2);
    ruleset.clearRules();

    ruleset.setEnabled("WithQueensAsTrump");
    ASSERT_EQ(ruleset.getHighestCardID(round), 1);
    ruleset.clearRules();
}

TEST(ruleset_test, WithJacksAsTrump){
    Ruleset ruleset;
    std::vector<Card> round = {
            Card(Suit::HEARTS, CardValue::QUEEN),
            Card(Suit::SPADES, CardValue::QUEEN),
            Card(Suit::HEARTS, CardValue::JACK),
            Card(Suit::SPADES, CardValue::JACK),
    };
    ruleset.setEnabled("WithDiamondsAsTrump");
    ASSERT_EQ(ruleset.getHighestCardID(round), 1);
    ruleset.clearRules();
    ruleset.setEnabled("WithJacksAsTrump");
    ASSERT_EQ(ruleset.getHighestCardID(round), 3);
    ruleset.clearRules();
    ruleset.setEnabled("WithDiamondsAsTrump");
    ASSERT_EQ(ruleset.getHighestCardID(round), 1);
    ruleset.clearRules();
}

TEST(ruleset_test, WithoutTrump){
    Ruleset ruleset;
    std::vector<Card> round = {
            Card(Suit::HEARTS, CardValue::QUEEN),
            Card(Suit::SPADES, CardValue::QUEEN),
            Card(Suit::HEARTS, CardValue::KING),
            Card(Suit::SPADES, CardValue::JACK),
    };
    ruleset.setEnabled("WithDiamondsAsTrump");
    ASSERT_EQ(ruleset.getHighestCardID(round), 1);
    ruleset.clearRules();

    ruleset.setEnabled("WithoutTrump");
    ASSERT_EQ(ruleset.getHighestCardID(round), 2);
}

TEST(ruleset_test, DifferentTrumpValues){
    Ruleset ruleset;
    ruleset.setEnabled("WithDiamondsAsTrump");
    ASSERT_TRUE(ruleset.isTrump(Card(Suit::DIAMONDS, CardValue::TEN)));
    ruleset.setDisabled("WithDiamondsAsTrump");

    ruleset.setEnabled("WithSpadesAsTrump");
    ASSERT_TRUE(ruleset.isTrump(Card(Suit::SPADES, CardValue::TEN)));
    ruleset.setDisabled("WithSpadesAsTrump");

    ruleset.setEnabled("WithCloverAsTrump");
    ASSERT_TRUE(ruleset.isTrump(Card(Suit::CLUBS, CardValue::TEN)));
    ruleset.setDisabled("WithCloverAsTrump");

    ruleset.setEnabled("WithHeartAsTrump");
    ASSERT_TRUE(ruleset.isTrump(Card(Suit::HEARTS, CardValue::TEN)));
    ruleset.setDisabled("WithHeartAsTrump");

}
