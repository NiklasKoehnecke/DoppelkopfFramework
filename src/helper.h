#ifndef DOPPELKOPF_HELPER_H
#define DOPPELKOPF_HELPER_H

#include <vector>
#include <algorithm>
#include <iostream>

int randomInt(int low, int high);

template<typename T>
bool contains(std::vector<T> vec, T item) {
    return std::find(vec.begin(), vec.end(), item) != vec.end();
}

template<typename T>
void printVector(std::vector<T> vector) {
    for (T item : vector)
        std::cout << item << " ";
    std::cout << std::endl;
}

#endif //DOPPELKOPF_HELPER_H
