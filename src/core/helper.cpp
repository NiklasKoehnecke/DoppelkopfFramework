#include <random>
#include <chrono>
#include "helper.h"

int randomInt(int low, int high) {
    auto s1 = static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::seed_seq seed{s1};
    std::mt19937 mt(seed);
    std::uniform_int_distribution<int> dist(low, high);
    return dist(mt);
}