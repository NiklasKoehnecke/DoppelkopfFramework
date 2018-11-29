#include <random>
#include "helper.h"

int randomInt(int low, int high) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(low, high);
    return dist(mt);
}