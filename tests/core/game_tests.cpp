#include <gtest/gtest.h>
#include "../../src/core/card.cpp"

TEST(card_test, test_true){
	Card card(Suit::DIAMONDS, CardValue::NINE);
	ASSERT_EQ(card.value(), CardValue::NINE);
}

