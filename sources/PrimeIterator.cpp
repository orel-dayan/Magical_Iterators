#include "MagicalContainer.hpp"

namespace ariel {

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return MagicalContainer::PrimeIterator{m_container};
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        return m_container.m_elements.empty()
               ? MagicalContainer::PrimeIterator(m_container)
               : MagicalContainer::PrimeIterator{m_container, &m_container.m_primes[m_container.m_primes.size()]};
    }

    int &MagicalContainer::PrimeIterator::operator*() {
        if (*this == this->end() || m_container.m_primes.empty()) {
            throw std::runtime_error("Error - Out of range ");
        }

        if (m_current == nullptr) { // if current is null then we need to set it to the first element
            m_current = &m_container.m_primes[0]; // i  used [] becaue acording to readme its not matter if  valid

        }

        return **m_current; // dereference operator
    }


    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        if (*this == this->end()) {
            throw std::runtime_error("Error - Out of range ");
        }
        if (m_current == nullptr && !m_container.m_primes.empty()) {
            m_current = &m_container.m_primes[0]; // i  used [] becaue acording to readme its not matter if  valid
        }
        m_current++;
        return *this;
    }


}
