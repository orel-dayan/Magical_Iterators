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
            throw std::runtime_error("Error - Out of range");
        }

        if (m_current == nullptr) {
            m_current = &m_container.m_primes.at(0);
        }

        return **m_current;
    }


    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        if (*this == this->end()) {
            throw std::runtime_error("Error - Out of range");
        }
        if (m_current == nullptr && !m_container.m_primes.empty()) {
            m_current = &m_container.m_primes.at(0);
        }
        m_current++;
        return *this;
    }


}
