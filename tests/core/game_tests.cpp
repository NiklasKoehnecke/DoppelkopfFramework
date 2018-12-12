#include <gtest/gtest.h>
#include <core/game.h>

TEST(game_test, example_test){
    std::vector<Player> players;
    Game g = Game(players);
    ASSERT_EQ(true, true);
}

