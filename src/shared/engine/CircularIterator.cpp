//
// Created by louismmassin on 1/6/25.
//
#include "CircularIterator.h"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <state/PlayerState.h>

namespace client {
    class Player;
}

namespace engine {
    template <typename T>
    CircularIterator<T>::CircularIterator (std::vector<T>& vec): vec(vec), it(this->vec.begin()){

    }

    template<typename T>
    CircularIterator<T>::CircularIterator(std::vector<T> &vec, typename std::vector<T>::iterator it): vec(vec), it(it) {

    }

    template<typename T>
    CircularIterator<T>::CircularIterator(std::vector<T> &vec, T &element): vec(vec),
    it(std::find_if(vec.begin(), vec.end(), [&element](const T& i) {
        return &i == &element;})){
        if (it == vec.end()) {
            throw std::runtime_error("element not found in vector");
        }
    }

    template<typename T>
    T &CircularIterator<T>::operator*() {
        return *it;
    }

    template<typename T>
    const T &CircularIterator<T>::operator*() const {
        return *it;
    }

    template<typename T>
    T *CircularIterator<T>::operator->() {
        return &(*it);
    }


    template<typename T>
    CircularIterator<T> &CircularIterator<T>::operator++() {
        ++it;
        if (it == vec.end()) {
            it = vec.begin();
        }
        return *this;
    }

    template<typename T>
    bool CircularIterator<T>::operator==(const CircularIterator<T> &otherIterator) {
        return it == otherIterator.it;
    }

    template<typename T>
    bool CircularIterator<T>::operator!=(const CircularIterator<T> &otherIterator) {
        return !(it == otherIterator.it);
    }

    template<typename T>
    void CircularIterator<T>::setElement(const T &element) {
        it = std::find_if(vec.begin(), vec.end(), [&element](const T& i) {
            return &i == &element;
        });
        if (it == vec.end()) {
            throw std::runtime_error("element not found in vector");
        }
    }

    template class CircularIterator<std::unique_ptr<client::Player>>;
    template class CircularIterator<state::PlayerState>;

}
