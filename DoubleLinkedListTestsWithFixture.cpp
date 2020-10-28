#include "DoubleLinkedList.h"
#include "LinkedListsException.h"
#include "gtest/gtest.h"

#include <string>

namespace googleTests {

    const static size_t GENERATED_DOUBLE_NUMBERS_NUMBER = 6;
    const char *OUTPUT_STRING_WITH_NON_EMPTY_LIST_ELEMENTS = "[1.101 <---> 2.202 <---> 3.303 <---> 4.404 <---> 5.505 <---> 6.606]\n";

    class DoubleLinkedListFixture : public ::testing::Test {
    protected:

        void TearDown() override {
            delete emptyListWithDoubles;
            delete nonEmptyListWithDoubles;
        }

        void SetUp() override {
            emptyListWithDoubles = new LinkedLists::DoubleLinkedList<double>();

            nonEmptyListWithDoubles = new LinkedLists::DoubleLinkedList<double>();
            fillCertainDoublesToList(*nonEmptyListWithDoubles);
        }

        LinkedLists::DoubleLinkedList<double> *emptyListWithDoubles;
        LinkedLists::DoubleLinkedList<double> *nonEmptyListWithDoubles;

    public:
        static void fillCertainDoublesToList(LinkedLists::DoubleLinkedList<double> &list) {
            // look at GENERATED_DOUBLE_NUMBERS_NUMBER
            list.push_back(1.101);
            list.push_back(2.202);
            list.push_back(3.303);
            list.push_back(4.404);
            list.push_back(5.505);
            list.push_back(6.606);
        }

    };

    TEST_F(DoubleLinkedListFixture, IsEmpty) {
        EXPECT_EQ(true, emptyListWithDoubles->empty());
        EXPECT_EQ(0, emptyListWithDoubles->size());
    }

    TEST_F(DoubleLinkedListFixture, FrontBackMethodsInEmptyList) {
        EXPECT_THROW(emptyListWithDoubles->front(), LinkedLists::LinkedListsException);
        EXPECT_THROW(emptyListWithDoubles->back(), LinkedLists::LinkedListsException);
    }

    TEST_F(DoubleLinkedListFixture, IsNotEmpty) {
        EXPECT_EQ(false, nonEmptyListWithDoubles->empty());
        EXPECT_EQ(GENERATED_DOUBLE_NUMBERS_NUMBER, nonEmptyListWithDoubles->size());
    }

    TEST_F(DoubleLinkedListFixture, IsEmptyAfterCleaning) {
        nonEmptyListWithDoubles->clear();
        EXPECT_EQ(true, nonEmptyListWithDoubles->empty());
        EXPECT_EQ(0, nonEmptyListWithDoubles->size());
    }

    TEST_F(DoubleLinkedListFixture, FrontBackMethodsAfterCleaning) {
        nonEmptyListWithDoubles->clear();
        EXPECT_THROW(nonEmptyListWithDoubles->front(), LinkedLists::LinkedListsException);
        EXPECT_THROW(nonEmptyListWithDoubles->back(), LinkedLists::LinkedListsException);
    }

    TEST_F(DoubleLinkedListFixture, AreListsEqual) {
        auto newListWithDoubles = new LinkedLists::DoubleLinkedList<double>();
        fillCertainDoublesToList(*newListWithDoubles);
        EXPECT_EQ(true, (*newListWithDoubles) == (*nonEmptyListWithDoubles));
        EXPECT_EQ(false, (*newListWithDoubles) != (*nonEmptyListWithDoubles));
        delete newListWithDoubles;
    }

    TEST_F(DoubleLinkedListFixture, CopyConstructor) {
        LinkedLists::DoubleLinkedList<double> newListWithDoubles = *nonEmptyListWithDoubles;
    }

    TEST_F(DoubleLinkedListFixture, CopyAssignment) {
        auto *newListWithDoubles = new LinkedLists::DoubleLinkedList<double>();
        *newListWithDoubles = *nonEmptyListWithDoubles;
        delete newListWithDoubles;
    }

    TEST_F(DoubleLinkedListFixture, MoveConstructor) {
        LinkedLists::DoubleLinkedList<double> newListWithDoubles = std::move(*nonEmptyListWithDoubles);
    }

    TEST_F(DoubleLinkedListFixture, MoveAssignment) {
        auto *newListWithDoubles = new LinkedLists::DoubleLinkedList<double>();
        *newListWithDoubles = std::move(*nonEmptyListWithDoubles);
        delete newListWithDoubles;
    }

    TEST_F(DoubleLinkedListFixture, IteratorsMethods) {
        auto newListWithDoubles = new LinkedLists::DoubleLinkedList<double>(*nonEmptyListWithDoubles);
        LinkedLists::DoubleLinkedList<double>::const_iterator it1 = newListWithDoubles->cbegin();
        LinkedLists::DoubleLinkedList<double>::const_iterator it2 = nonEmptyListWithDoubles->cbegin();
        while (it1 != newListWithDoubles->cend() && it2 != nonEmptyListWithDoubles->cend()) {
            EXPECT_EQ(*it1, *it2);
            it1++;
            ++it2;
        }
        delete newListWithDoubles;
    }

    TEST_F(DoubleLinkedListFixture, PrintNotEmptyList) {
        std::stringstream listOutputStream;
        listOutputStream << *nonEmptyListWithDoubles;
        std::string generatedFullString(listOutputStream.str());
        const char *generatedCString = generatedFullString.c_str();
        EXPECT_STREQ(OUTPUT_STRING_WITH_NON_EMPTY_LIST_ELEMENTS, generatedCString);
    }

    TEST_F(DoubleLinkedListFixture, PrintEmptyList) {
        std::stringstream listOutputStream;
        listOutputStream << *emptyListWithDoubles;
        std::string generatedFullString(listOutputStream.str());
        const char *generatedCString = generatedFullString.c_str();
        EXPECT_STREQ("[]\n", generatedCString);
    }

    TEST_F(DoubleLinkedListFixture, MergesTwoLists) {
        fillCertainDoublesToList(*nonEmptyListWithDoubles);

        auto *newListGeneratedMergeOperator = new LinkedLists::DoubleLinkedList<double>(
                *nonEmptyListWithDoubles + *nonEmptyListWithDoubles);

        LinkedLists::DoubleLinkedList<double>::const_iterator it1 = nonEmptyListWithDoubles->cbegin();
        LinkedLists::DoubleLinkedList<double>::const_iterator it2 = newListGeneratedMergeOperator->cbegin();
        while (it1 != nonEmptyListWithDoubles->cend() && it2 != newListGeneratedMergeOperator->cend()) {
            EXPECT_EQ(*it1, *it2);
            it1++;
            ++it2;
        }

        delete newListGeneratedMergeOperator;
    }

    TEST_F(DoubleLinkedListFixture, AddAnotherList) {
        fillCertainDoublesToList(*nonEmptyListWithDoubles);

        auto *newListGeneratedMergeOperator = new LinkedLists::DoubleLinkedList<double>(*nonEmptyListWithDoubles);
        *newListGeneratedMergeOperator += *nonEmptyListWithDoubles;

        LinkedLists::DoubleLinkedList<double>::const_iterator it1 = nonEmptyListWithDoubles->cbegin();
        LinkedLists::DoubleLinkedList<double>::const_iterator it2 = newListGeneratedMergeOperator->cbegin();
        while (it1 != nonEmptyListWithDoubles->cend() && it2 != newListGeneratedMergeOperator->cend()) {
            EXPECT_EQ(*it1, *it2);
            it1++;
            ++it2;
        }

        delete newListGeneratedMergeOperator;
    }

    TEST_F(DoubleLinkedListFixture, FrontBackPop) {
        auto *saveOriginalList = new LinkedLists::DoubleLinkedList<double>(*nonEmptyListWithDoubles);
        fillCertainDoublesToList(*nonEmptyListWithDoubles);
        fillCertainDoublesToList(*nonEmptyListWithDoubles);
        for (size_t i = 0; i < GENERATED_DOUBLE_NUMBERS_NUMBER; i++) {
            nonEmptyListWithDoubles->pop_back();
            nonEmptyListWithDoubles->pop_front();
        }
        EXPECT_EQ(true, *saveOriginalList == *nonEmptyListWithDoubles);
        EXPECT_EQ(false, *saveOriginalList != *nonEmptyListWithDoubles);

        delete saveOriginalList;
    }

    TEST_F(DoubleLinkedListFixture, InsertRemoveMethods) {
        auto *saveOriginalList = new LinkedLists::DoubleLinkedList<double>(*nonEmptyListWithDoubles);
        double newValue = GENERATED_DOUBLE_NUMBERS_NUMBER + 1 + 0.01 * (GENERATED_DOUBLE_NUMBERS_NUMBER + 1);
        nonEmptyListWithDoubles->insert(nonEmptyListWithDoubles->begin() + 2, newValue);
        nonEmptyListWithDoubles->insert(nonEmptyListWithDoubles->begin(), newValue);
        nonEmptyListWithDoubles->insert(nonEmptyListWithDoubles->end() + (-1), newValue);

        nonEmptyListWithDoubles->remove(newValue);

        EXPECT_EQ(true, *saveOriginalList == *nonEmptyListWithDoubles);
        EXPECT_EQ(false, *saveOriginalList != *nonEmptyListWithDoubles);

        delete saveOriginalList;
    }


}