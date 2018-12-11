#include <gtest/gtest.h>

TEST(game_test, test_true) {
    ASSERT_EQ(1, 1);
}

TEST(game_test, test_false) {
    ASSERT_EQ(1, 2);
}
