#include "MagicalContainer.hpp"

namespace ariel {


    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return MagicalContainer::SideCrossIterator(m_container);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        return m_container.m_elements.empty()
               ? MagicalContainer::SideCrossIterator(m_container)
               : MagicalContainer::SideCrossIterator{m_container, &m_container.m_elements[m_container.m_size - 1] + 1};
    }


    int &MagicalContainer::SideCrossIterator::operator*() {
        if (m_container.m_size == 0) {
            throw std::runtime_error("Error: Out of range ");
        }
        if (*this == this->end()) {
            throw std::runtime_error("Error:Out of range ");
        }

        if (m_current == nullptr) {
            m_current = &m_container.m_elements[0];
        }

        return **m_current; // dereference operator
    }


    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        if (*this == this->end()) { // if we are at the end of the container
            throw std::runtime_error("Error - Out of range");
        }

        updateCurrentAndNext();
        return *this;
    }

    void MagicalContainer::SideCrossIterator::updateCurrentAndNext() {
        auto nextElement = m_next;
        if (m_current == &m_container.m_elements[m_container.m_size / 2]) {
            m_current = &m_container.m_elements[m_container.m_size - 1] + 1;
        } else {
            m_current = m_changed ? &m_container.m_elements[nextElement] : &m_container.m_elements[m_container.m_size -
                                                                                                   nextElement - 1];
            m_changed = !m_changed;
        }

        if (m_changed) {
            m_next++;
        }
    }


    MagicalContainer::SideCrossIterator &
    MagicalContainer::SideCrossIterator::operator=(MagicalContainer::SideCrossIterator &other) {

        if (typeid(*this) != typeid(other)) {
            throw std::runtime_error("Error - Cant assign iterators of different types");
        }

        if (&this->getContainer() != &other.getContainer()) {
            throw std::runtime_error("Error - Container is different");
        }

        m_current = other.m_current;
        m_changed = other.m_changed;
        m_next = other.m_next;

        return *this;
    }


}
