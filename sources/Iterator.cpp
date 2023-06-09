#include "MagicalContainer.hpp"

namespace ariel {

    void Iterator::checkType(const Iterator &other) const {
        if (typeid(*this) != typeid(other)) {
            throw std::runtime_error("Error -Cant compare or assign iterators of different types");
        }
    }

    bool Iterator::operator==(const Iterator &other) const {
        checkType(other);
        return this->m_current == other.m_current;
    }

    bool Iterator::operator!=(const Iterator &other) const {
        checkType(other);
        return !(*this == other);
    }

    bool Iterator::operator<(const Iterator &other) const {
        checkType(other);
        return this->m_current < other.m_current;
    }

    bool Iterator::operator>(const Iterator &other) const {
        checkType(other);
        return this->m_current > other.m_current;
    }

    Iterator &Iterator::operator=(const Iterator &other) {
        checkType(other);

        if (&this->getContainer() != &other.getContainer()) {
            throw std::runtime_error("Error -Container is different");
        }

        m_current = other.m_current;

        return *this;
    }

    MagicalContainer &Iterator::getContainer() const {
        return m_container;
    }

    int **Iterator::getCurrent() const {
        return m_current;
    }

}
