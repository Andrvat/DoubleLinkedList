#pragma once

#include "LinkedListsException.h"

#include <cstdlib>
#include <iostream>

namespace LinkedLists {

    /**
     * @class DoubleLinkedList
     *
     * @brief Implements a template doubly linked list
     *        It uses a single-pointer implementation that points
     *        to both the beginning of the list and the end (ring view)
     *
     * @author Andrey Valitov
     *
     * @version 1.3 - After Google Tests
     *                Changed implementations of push back & front methods...
     *                pop back & front methods
     *                Added throw in erase when we get the iterator to nonexistent element
     *
     * @tparam T
     */
    template<class T>
    class DoubleLinkedList {
    private:

        struct Node {
            T data;
            Node *prev;
            Node *next;
        };

        Node *nodePointer_;

        size_t doubleLinkedListSize_;
    public:

        /**
         * @class iterator
         *
         * @brief Implements the basic features of the classic non-const iterator from STL
         *        This allows to use an simple way to get and handle list elements
         *
         * @version 1.0 - After Google tests
         */
        class iterator {
        private:

            /*
             * Make class iterator friend of class DoubleLinkedList
             * It allows to use private data of class iterator
             */
            friend class DoubleLinkedList<T>;

            Node *iteratorPointer_;
        public:

            /**
             * @brief Iterator constructor by node pointer
             *        This method is used when creating
             *        a new object based on a pointer
             *        to one list node
             *
             * @param pNode
             */
            explicit iterator(Node *pNode) {
                iteratorPointer_ = pNode;
            };

            /**
             * @brief Copy constructor
             *
             * @param other - The iterator from which the copy is taken
             */
            iterator(const iterator &other) {
                iteratorPointer_ = other.iteratorPointer_;
            };

            /**
             * @brief Copy assignment operator
             *
             * @param other - The iterator from which the copy is taken
             * @return current iterator object
             */
            iterator &operator=(const iterator &other) {
                // Self-assignment protection
                if (this != &other) {
                    iteratorPointer_ = other.iteratorPointer_;
                }
                return *this;
            };

            /**
             * @brief Comparison between two iterators for inequality
             *
             * @param other - iterator that this is compared to
             * @return true, if iterators point to different nodes
             *         false, if iterators point to the same node
             */
            bool operator!=(const iterator &other) const {
                return iteratorPointer_ != other.iteratorPointer_;
            };

            /**
             * @brief Comparison between two iterators for equality
             *
             * @param other - iterator that this is compared to
             * @return true, if iterators point to the same node
             *         false, if iterators point to different nodes
             */
            bool operator==(const iterator &other) const {
                return iteratorPointer_ == other.iteratorPointer_;
            };

            /**
             * @brief Dereferencing the iterator
             *
             * @return data, which the iterator points to
             */
            T &operator*() {
                return iteratorPointer_->data;
            };

            /**
             * @return Pointer to data, which the iterator points to
             */
            T *operator->() {
                return &(iteratorPointer_->data);
            };

            /**
             * @brief The iterator incrementing
             *
             * @return iterator that points to the next element after the current one
             */
            iterator &operator++() {
                iteratorPointer_ = iteratorPointer_->next;
                return *this;
            };

            /**
            * @brief The iterator incrementing
            *
            * @return iterator that points to the current element
            */
            iterator operator++(int) {
                iterator old = *this;
                ++(*this);
                return old;

            };

            /**
             * @brief The iterator decrementing
             *
             * @return iterator that points to the previous element before the current one
             */
            iterator &operator--() {
                iteratorPointer_ = iteratorPointer_->prev;
                return *this;
            };

            /**
             * @brief The iterator decrementing
             *
             * @return iterator that points to the current element
             */
            iterator operator--(int) {
                iterator old = *this;
                --(*this);
                return old;
            };

            /**
             *
             * @brief Offset the iterator by an arbitrary integer
             *
             * @param shift - the offset value of the iterator
             * @param it - iterator to which the offset is applied
             * @return iterator after applying the offset
             */
            friend iterator operator+(const int shift, const iterator &it) {
                class iterator current(it);
                for (int i = 0; i < shift; i++) {
                    ++(current);
                }
                return current;
            }

            /**
             *
             * @brief Offset the iterator by an arbitrary integer
             *
             * @param it - iterator to which the offset is applied
             * @param shift - the offset value of the iterator
             * @return iterator after applying the offset
             */
            friend iterator operator+(const iterator &it, const int shift) {
                return shift + iterator(it);
            }
        };

        /**
         * @class const_iterator
         *
         * @brief Implements the basic features of the classic const iterator from STL
         *        This allows to use an simple way to get and handle list elements
         *
         *        Implementation features are described in the class iterator
         *
         * @version 1.0 - After Google tests
         */
        class const_iterator {
        private:

            friend class DoubleLinkedList<T>;

            Node *constIteratorPointer_;
        public:
            explicit const_iterator(Node *ptr) {
                constIteratorPointer_ = ptr;
            };

            const_iterator(const const_iterator &other) {
                constIteratorPointer_ = other.constIteratorPointer_;
            }

            const_iterator &operator=(const const_iterator &other) {
                if (this != &other) {
                    constIteratorPointer_ = other.constIteratorPointer_;
                }
                return *this;
            };

            bool operator!=(const const_iterator &other) const {
                return constIteratorPointer_ != other.constIteratorPointer_;
            };

            bool operator==(const const_iterator &other) const {
                return constIteratorPointer_ == other.constIteratorPointer_;
            };

            const T &operator*() const {
                return constIteratorPointer_->data;
            };

            const T *operator->() const {
                return &(constIteratorPointer_->data);
            };

            const_iterator &operator++() {
                constIteratorPointer_ = constIteratorPointer_->next;
                return *this;
            };

            const_iterator operator++(int) {
                const_iterator old = *this;
                ++(*this);
                return old;
            };

            const_iterator &operator--() {
                constIteratorPointer_ = constIteratorPointer_->prev;
                return *this;
            };

            const_iterator operator--(int) {
                const_iterator old = *this;
                --(*this);
                return old;
            };

            friend const_iterator operator+(const int shift, const const_iterator &it) {
                class const_iterator current(it);
                for (int i = 0; i < shift; i++) {
                    ++(current);
                }
                return current;
            }

            friend const_iterator operator+(const const_iterator &it, const int shift) {
                return shift + const_iterator(it);
            }
        };

        /**
         * @brief Constructor - empty list initialization
         */
        DoubleLinkedList() {
            nodePointer_ = new Node();
            nodePointer_->prev = nodePointer_;
            nodePointer_->next = nodePointer_;
            doubleLinkedListSize_ = 0;
        };

        /**
         * @brief Copy constructor
         *        It initializes a new list from an existing list by copying it completely
         *
         * @param other - copy source
         */
        DoubleLinkedList(const DoubleLinkedList &other) : DoubleLinkedList() {
            doubleLinkedListSize_ = 0;
            Node *current = other.nodePointer_->next;
            while (current != other.nodePointer_) {
                push_back(current->data);
                current = current->next;
            }
        };

        /**
         * @brief Move constructor
         *        Moves full control over the existing list to the newly created object
         *
         * @param other - list, the control on which need to move
         */
        DoubleLinkedList(DoubleLinkedList &&other) noexcept: DoubleLinkedList() {
            nodePointer_ = other.nodePointer_;
            doubleLinkedListSize_ = other.doubleLinkedListSize_;
            other.doubleLinkedListSize_ = 0;
            other.nodePointer_ = nullptr;
        };

        /**
         * @brief Destructor
         *        Clear non-empty list and delete single node pointer
         */
        ~DoubleLinkedList() {
            if (!empty()) {
                clear();
            }
            delete nodePointer_;
        };

        /**
         * @brief Copy assignment
         *        It rewrites an existing list from another existing list by copying it completely
         *
         * @param other - the list to copy from
         * @return rewritten existing list
         */
        DoubleLinkedList &operator=(const DoubleLinkedList &other) {
            if (this != &other) {
                if (!empty()) {
                    clear();
                }
                Node *current = other.nodePointer_->next;
                while (current != other.nodePointer_) {
                    push_back(current->data);
                    current = current->next;
                }
            }
            return *this;
        };

        /**
         * @brief Move assignment
         *        It rewrites an existing list from another existing list by moving it completely
         *
         * @param other - the list to move from
         * @return rewritten existing list
         */
        DoubleLinkedList &operator=(DoubleLinkedList &&other) noexcept {
            if (this != &other) {
                if (!empty()) {
                    clear();
                }
                delete nodePointer_;
                nodePointer_ = other.nodePointer_;
                doubleLinkedListSize_ = other.doubleLinkedListSize_;
                other.doubleLinkedListSize_ = 0;
                other.nodePointer_ = nullptr;
            }
            return *this;
        };

        /**
         * @return non-const iterator that points to the first element in the list
         */
        iterator begin() {
            return iterator(nodePointer_->next);
        };

        /**
         * @return const iterator that points to the first element in the list
         */
        const_iterator begin() const {
            return const_iterator(nodePointer_->next);
        };

        /**
         * @return const iterator that points to the first element in the list
         */
        const_iterator cbegin() const {
            return const_iterator(nodePointer_->next);
        };

        /**
         * @return non-const iterator that points to the element after the last one in the list
         */
        iterator end() {
            return iterator(nodePointer_);
        };

        /**
         * @return const iterator that points to the element after the last one in the list
         */
        const_iterator end() const {
            return const_iterator(nodePointer_);
        };

        /**
         * @return const iterator that points to the element after the last one in the list
         */
        const_iterator cend() const {
            return const_iterator(nodePointer_);
        };

        /**
         * @return list size
         */
        [[nodiscard]] size_t size() const {
            return doubleLinkedListSize_;
        };

        /**
         * @return true, if the list is empty
         *         false, if not
         */
        [[nodiscard]] bool empty() const {
            return doubleLinkedListSize_ == 0;
        };

        /**
         * @throw LinkedLists::LinkedListsException
         *
         * @return the non-const reference to the first element in the list
         */
        T &front() {
            if (!empty()) {
                return nodePointer_->next->data;
            } else {
                throw LinkedLists::LinkedListsException("Can't return a reference to the first item in the list");
            }
        };

        /**
         * @throw LinkedLists::LinkedListsException
         *
         * @return the const reference to the first element in the list
         */
        const T &front() const {
            if (!empty()) {
                return nodePointer_->next->data;
            } else {
                throw LinkedLists::LinkedListsException("Can't return a const reference to the first item in the list");
            }
        };

        /**
         * @throw LinkedLists::LinkedListsException
         *
         * @return the non-const reference to the last element in the list
         */
        T &back() {
            if (!empty()) {
                return nodePointer_->prev->data;
            } else {
                throw LinkedLists::LinkedListsException("Can't return a reference to the last item in the list");
            }
        };

        /**
         * @throw LinkedLists::LinkedListsException
         *
         * @return the const reference to the last element in the list
         */
        const T &back() const {
            if (!empty()) {
                return nodePointer_->prev->data;
            } else {
                throw LinkedLists::LinkedListsException("Can't return a const reference to the last item in the list");
            }
        };

        /**
         * @brief Deletes the element pointed to by the position iterator.
         *
         * @param position - iterator that points to the element to delete
         * @return iterator to the next element that fell into place of the deleted one
         */
        iterator erase(iterator position) {
            if (position != end()) {

                --doubleLinkedListSize_;

                Node *saveNextNode = position.iteratorPointer_->next;
                Node *savePrevNode = position.iteratorPointer_->prev;
                savePrevNode->next = saveNextNode;
                saveNextNode->prev = savePrevNode;
                iterator current(saveNextNode);
                delete position.iteratorPointer_;
                return current;
            } else {
                throw LinkedLists::LinkedListsException("Can't erase a nonexistent element in erase method");
            }
        };

        /**
         *
         * @brief Deletes the elements pointed from begin to end (not include) iterators.
         *
         * @param begin - iterator that points to the element to start delete
         * @param end - iterator that points to the element to finish delete
         * @return iterator to end
         */
        iterator erase(iterator begin, iterator end) {
            iterator current = begin;
            while (current != end) {
                current = erase(current);
            }
            return end;
        };

        /**
         * @brief Delete all list elements which contains data = value by using iterators
         *
         * @param value - the data elements which will be deleted
         * @return number of deleted elements in the list
         */
        size_t remove(const T &value) {
            size_t counter = 0;
            iterator current = begin();
            while (current != end()) {
                if (current.iteratorPointer_->data == value) {
                    current = erase(current);
                    ++counter;
                } else {
                    ++current;
                }
            }
            return counter;
        };

        /**
         * @brief Clear current list
         */
        void clear() {
            iterator current = begin();
            while (current != end()) {
                current = erase(current);
            }
        };

        /**
         * @brief Delete the last list element
         */
        void pop_back() {
            erase(--end());
        };

        /**
         * @brief Delete the first list element
         */
        void pop_front() {
            erase(++begin());
        };

        /**
         * @brief Insert the new element with data = value in the end of the list
         *
         * @param value - data of new element
         */
        void push_back(const T &value) {
            insert(end(), value);
        };

        /**
         * @brief Insert the new element with data = value in the begin of the list
         *
         * @param value - data of new element
         */
        void push_front(const T &value) {
            insert(begin(), value);
        };

        /**
         * @brief Inserts the new element with data = value before the element pointed to by before
         *
         * @param before - iterator, before which need to add a new element
         * @param value - new element data
         * @return iterator that points to the new element in the list
         */
        iterator insert(iterator before, const T &value) {
            Node *newNode = new Node();
            newNode->data = value;

            Node *savePrevBefore = before.iteratorPointer_->prev;
            savePrevBefore->next = newNode;
            newNode->next = before.iteratorPointer_;
            before.iteratorPointer_->prev = newNode;
            newNode->prev = savePrevBefore;

            doubleLinkedListSize_++;

            return iterator(newNode);
        };

        /**
         * @brief Adds another existing list to the end of the current list
         *
         * @param other - the list that will be attached to the end of the current one
         * @return advanced existing list
         */
        DoubleLinkedList &operator+=(const DoubleLinkedList &other) {
            if (other.empty()) {
                return *this;
            }

            Node *currentOtherNode = other.nodePointer_->next;
            while (currentOtherNode != other.nodePointer_) {
                push_back(currentOtherNode->data);
                currentOtherNode = currentOtherNode->next;
            }

            return *this;
        };

        /**
         * @brief Compares two lists element by element for the inequality
         *
         * @param left - first list to compare
         * @param right - second list to compare
         * @return true, if the lists are not equal
         *         false, if equal
         */
        friend bool operator!=(const DoubleLinkedList &left, const DoubleLinkedList &right) {
            if (&left == &right) {
                return false;
            }

            if (left.size() != right.size()) {
                return true;
            }

            auto curItLeft = left.begin();
            auto curItRight = right.begin();
            while (curItLeft != left.end() && curItRight != right.end()) {
                if (*curItLeft != *curItRight) {
                    return true;
                }
                curItLeft++;
                curItRight++;
            }
            return false;
        };

        /**
         * @brief Compares two lists element by element for the equality
         *
         * @param left - first list to compare
         * @param right - second list to compare
         * @return true, if the lists are equal
         *         false, if not
         */
        friend bool operator==(const DoubleLinkedList &left, const DoubleLinkedList &right) {
            return !(left != right);
        };

        /**
         * @brief Outputs the entire list to out using the following template:
         *        [el_1 <---> el_2 <---> ... <---> el_n]
         *
         * @param out - output stream
         * @param doubleLinkedList - the list for print to the out stream
         * @return output stream after using
         */
        friend std::ostream &operator<<(std::ostream &out, const DoubleLinkedList<T> &doubleLinkedList) {
            out << "[";
            Node *currentNode = doubleLinkedList.nodePointer_->next;
            while (currentNode != doubleLinkedList.nodePointer_) {
                out << currentNode->data;
                if (currentNode != doubleLinkedList.nodePointer_->prev) {
                    out << " <---> ";
                }
                currentNode = currentNode->next;
            }
            out << "]" << std::endl;
            return out;
        }

        /**
         * @brief Merges two lists into one
         *
         * @param left - first list to join
         * @param right - second list to join
         * @return merged list
         */
        friend LinkedLists::DoubleLinkedList<T> operator+(const LinkedLists::DoubleLinkedList<T> &left,
                                                          const LinkedLists::DoubleLinkedList<T> &right) {
            LinkedLists::DoubleLinkedList<T> list(left);
            list += right;
            return list;
        }
    };

}