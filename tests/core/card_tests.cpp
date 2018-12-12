#include <gtest/gtest.h>
#include <core/card.h>

TEST(card_test, test_true){
    Card card(Suit::DIAMONDS, CardValue::NINE);
    ASSERT_EQ(card.value(), CardValue::NINE);
}

