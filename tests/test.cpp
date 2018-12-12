#include <gtest/gtest.h>

// TODO figure out why the cpp files need to be included and not only the header
// This is the include for all tests
#include <core/game.cpp>
#include <core/ruleset.cpp>
#include <core/player.cpp>
#include <core/round.cpp>
#include <core/helper.cpp>
#include <core/card.cpp>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
