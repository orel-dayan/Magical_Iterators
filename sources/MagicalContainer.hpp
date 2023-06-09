#pragma once

#include <vector>
#include <cmath>
#include <stdexcept>


namespace ariel {

    /**
     * A container class that stores in a sorted manner and provides
     * iterators for accessing elements in ascending order, side-cross order,
     * and prime numbers only.
     */


    class MagicalContainer {
    private:
        std::vector<int *> m_elements; // sorted vector - side cross and ascending iterators
        std::vector<int *> m_primes; // prime vector - prime iterator
        unsigned long m_size; // size of the container


    public:
        // Default constructor - creates an empty container
        MagicalContainer() : m_size(0) {};

        // Copy constructor
        MagicalContainer(const MagicalContainer &other) = default;

        // Move constructor
        MagicalContainer(MagicalContainer &&other)

        noexcept =
        default;

        // Copy assignment operator
        MagicalContainer &operator=(const MagicalContainer &other) {
            if (this != &other) {
                m_elements = other.m_elements;
                m_primes = other.m_primes;
                m_size = other.m_size;
            }
            return *this;
        }

        // Move assignment operator
        MagicalContainer &operator=(MagicalContainer &&other)

        noexcept =
        default;

        // Destructor
        ~MagicalContainer();

        // Checks if a given number is prime
        static bool isPrime(int &num);

        // Adds a given number to the container
        void addElement(int element);

        // Removes a given number from the container
        void removeElement(int element);

        // Returns the size of the container
        int size() const;

        // Forward declaration of iterator classes
        class AscendingIterator;

        class SideCrossIterator;

        class PrimeIterator;

    private:
        // Adds a prime number to the prime vector
        void addPrime(int *number);

        // Adds a sorted number to the sorted vector
        void addSortedElements(int *number);

        // Removes a prime number from the prime vector
        void removePrime(const int *number);

        // Removes a sorted number from the sorted vector
        void removeSortedElements(const int *number);

        // Finds the index of a given number
        long findElementIndex(int number);
    };

    /**
      * Base iterator class for the MagicalContainer.
      */

    class Iterator {
    protected:
        MagicalContainer &m_container; //NOLINT
        int **m_current; //NOLINT

    protected:
        Iterator(MagicalContainer &container, int **current) : m_container(container), m_current(current) {};
    public:
        virtual ~Iterator() = default;

        Iterator(const Iterator &other) = default;

        Iterator(Iterator &&other)

        noexcept =
        default;

        Iterator &operator=(const Iterator &other);

        int **getCurrent() const;

        MagicalContainer &getContainer() const;

        bool operator==(const Iterator &other) const; // equality operator

        bool operator!=(const Iterator &other) const; // inequality operator

        bool operator<(const Iterator &other) const; // less than operator

        bool operator>(const Iterator &other) const; // greater than operator

        void checkType(const Iterator &other) const; // checks if two iterators are of the same type
    };

    /**
       * Iterator for accessing prime numbers in the MagicalContainer.
       */

    class MagicalContainer::PrimeIterator : public Iterator {
    private:
        PrimeIterator(MagicalContainer &container, int **current) : Iterator(container,
                                                                             current) {};
    public:
        PrimeIterator(MagicalContainer &container) : Iterator(container, container.m_primes.empty()
                                                                         ? nullptr
                                                                         : &container.m_primes.at(0)) {};

        PrimeIterator(const PrimeIterator &other) : Iterator(other.m_container, other.m_current) {};


        PrimeIterator(PrimeIterator &other) = default;

        int &operator*();

        PrimeIterator &operator++();

        PrimeIterator begin();

        PrimeIterator end();
    };

    /**
     * Iterator for accessing elements in ascending order in the MagicalContainer.
     */

    class MagicalContainer::AscendingIterator : public Iterator {
    private:
        AscendingIterator(MagicalContainer &container, int **current) : Iterator(container, current) {};
    public:
        AscendingIterator(MagicalContainer &container) : Iterator(container, container.m_elements.empty()
                                                                             ? nullptr
                                                                             : &container.m_elements.at(0)) {};

        AscendingIterator(const AscendingIterator &other) : Iterator(other.m_container, other.m_current) {};

        int &operator*(); // dereference operator

        AscendingIterator &operator++(); // prefix increment operator

        AscendingIterator begin(); // begin iterator

        AscendingIterator end(); // end iterator
    };

    /**
    * Iterator for accessing elements in side-cross order in the MagicalContainer.
    */

    class MagicalContainer::SideCrossIterator : public Iterator {
    private:
        bool m_changed;
        unsigned long m_next;

    private:
        SideCrossIterator(MagicalContainer &container, int **current) : Iterator(container, current), m_next(0),
                                                                        m_changed(false) {};

    public:

        SideCrossIterator(MagicalContainer &container) : Iterator(container, container.m_elements.empty()
                                                                             ? nullptr
                                                                             : &container.m_elements.at(0)),
                                                         m_next(0), m_changed(false) {};

        SideCrossIterator(const SideCrossIterator &other) : Iterator(other.m_container, other.m_current),
                                                            m_next(other.m_next),
                                                            m_changed(other.m_changed) {}; // copy constructor

        SideCrossIterator(SideCrossIterator &other) = default;

        SideCrossIterator &operator=(SideCrossIterator &other);

        int &operator*();

        void updateCurrentAndNext(); // updates the current and next elements

        SideCrossIterator &operator++(); // prefix increment operator

        SideCrossIterator begin(); // begin iterator

        SideCrossIterator end(); // end iterator


    };

}
