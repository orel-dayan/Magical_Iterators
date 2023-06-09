
#include "MagicalContainer.hpp"

namespace ariel {


    bool MagicalContainer::isPrime(int &num) {
        if (num < 2) {
            return false;
        }
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }

    void MagicalContainer::addElement(int element) {
        long elementAt = findElementIndex(element); // find if element already exists
        if (elementAt != -1) {
            return;
        }

        int *value = new int(element); // create new element to add to the container
        addSortedElements(value); // add the element to the sorted vector

        if (isPrime(element) == true) { // if the element is prime, add it to the prime vector
            addPrime(value); // add the element to the prime vector

        }
        m_size++; // increase the size of the container
    }

    void MagicalContainer::removeElement(int num) {

        auto elementAt = static_cast<unsigned long>(findElementIndex(num));
        if (elementAt == -1) {
            throw std::runtime_error("Error - Cant remove element that doesnt exist");
        }
        removePrime(m_elements.at(elementAt));
        removeSortedElements(m_elements.at(elementAt)); // remove the element from the sorted vector
        m_size--; // decrease the size of the container

    }

    long MagicalContainer::findElementIndex(int num) {
        long numberIdx = 0;
        for (int *element: m_elements) { // find the index of the element in the sorted vector
            if (*element == num) {
                break;
            }
            numberIdx++; // increase the index
        }

        auto location = m_elements.begin() + numberIdx;
        if (location != m_elements.end()) {
            return std::distance(m_elements.begin(), location);
        }

        return -1; // if the element is not found, return -1
    }


    void MagicalContainer::addSortedElements(int *num) {
        long numberidx = 0;
        for (int *element: m_elements) {
            if (*element > *num) {
                break;
            }
            numberidx++;
        }

        auto location = m_elements.begin() + numberidx;
        m_elements.insert(location, num);
    }

    void MagicalContainer::addPrime(int *num) {
        m_primes.push_back(num); // add the element to the prime vector
    }


    void MagicalContainer::removeSortedElements(const int *num) {
        for (auto it = m_elements.begin(); it != m_elements.end(); ++it) {
            if (*it == num) {
                delete *it;
                m_elements.erase(it); // remove the element from the sorted vector
                break; // stop the loop
            }
        }
    }

    void MagicalContainer::removePrime(const int *num) {
        for (auto it = m_primes.begin(); it != m_primes.end(); ++it) {
            if (*it == num) { // if the element is found in the prime vector
                m_primes.erase(it);
                break;
            }
        }
    }


    int MagicalContainer::size() const {
        return m_size;
    }

    MagicalContainer::~MagicalContainer() {
        for (unsigned long i = 0; i < m_size; i++) {
            delete m_elements.at(i);
        }
    }


}
