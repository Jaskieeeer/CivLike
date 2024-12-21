#include "Gold.h"
#include <iostream>

template <typename T>
Gold<T>::Gold(T gold) : gold(gold) {}

template <typename T>
void Gold<T>::displayGold() const {
    std::cout << "Gold: " << gold << std::endl;
}

template <typename T>
void Gold<T>::setGold(T gold) {
    this->gold = gold;
}

template <typename T>
T Gold<T>::getGold() const {
    return gold;
}

template class Gold<int>;
template class Gold<double>;
template class Gold<std::string>;
