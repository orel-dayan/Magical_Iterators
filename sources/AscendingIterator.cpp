#include "MagicalContainer.hpp"

namespace ariel {

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return MagicalContainer::AscendingIterator{m_container};
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        return m_container.m_elements.empty()
               ? MagicalContainer::AscendingIterator(m_container)
               : MagicalContainer::AscendingIterator{m_container, &m_container.m_elements[m_container.m_size]};
    }

    int &MagicalContainer::AscendingIterator::operator*() {
        if (m_container.m_size == 0) {
            throw std::out_of_range("Error - Out of range");
        }
        if (*this == this->end()) {
            throw std::out_of_range("Error - Out of range");
        }

        if (m_current == nullptr && !m_container.m_elements.empty()) {
            m_current = &m_container.m_elements[0]; // i  used [] becaue acording to readme its not matter if  valid
        }

        return **m_current;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
        if (*this == this->end() || m_container.m_elements.empty()) {
            throw std::runtime_error("Error - Out of range");
        }
        if (m_current == nullptr) {
            m_current = &m_container.m_elements[0];
        }
        m_current++;
        return *this;
    }


}
