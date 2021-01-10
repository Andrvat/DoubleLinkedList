#include "DoubleLinkedList.h"
#include "LinkedListsException.h"
#include "gtest/gtest.h"

#include <string>

namespace googleTests {


    const static size_t GENERATED_DOUBLE_NUMBERS_AMOUNT = 6;
    const static double FIRST_VALUE_IN_TEST_LIST = 1.101;
    const static double SECOND_VALUE_IN_TEST_LIST = 2.202;
    const static double THIRD_VALUE_IN_TEST_LIST = 3.303;
    const static double FOURTH_VALUE_IN_TEST_LIST = 4.404;
    const static double FIFTH_VALUE_IN_TEST_LIST = 5.505;
    const static double SIXTH_VALUE_IN_TEST_LIST = 6.606;

    const char *OUTPUT_STRING_WITH_NON_EMPTY_LIST_ELEMENTS = "[1.101 <---> 2.202 <---> 3.303 <---> 4.404 <---> 5.505 <---> 6.606]\n";
    const char *OUTPUT_STRING_WITH_EMPTY_LIST_ELEMENTS = "[]\n";

    class DoubleLinkedListFixtureClassTest : public ::testing::Test {
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
            // look at GENERATED_DOUBLE_NUMBERS_AMOUNT
            list.push_back(FIRST_VALUE_IN_TEST_LIST);
            list.push_back(SECOND_VALUE_IN_TEST_LIST);
            list.push_back(THIRD_VALUE_IN_TEST_LIST);
            list.push_back(FOURTH_VALUE_IN_TEST_LIST);
            list.push_back(FIFTH_VALUE_IN_TEST_LIST);
            list.push_back(SIXTH_VALUE_IN_TEST_LIST);
        }

    };

    TEST_F(DoubleLinkedListFixtureClassTest, IsEmpty) {
        EXPECT_EQ(true, emptyListWithDoubles->empty());
        EXPECT_EQ(0, emptyListWithDoubles->size());
    }

    TEST_F(DoubleLinkedListFixtureClassTest, FrontBackMethodsInEmptyList) {
        EXPECT_THROW(emptyListWithDoubles->front(), LinkedLists::LinkedListsException);
        EXPECT_THROW(emptyListWithDoubles->back(), LinkedLists::LinkedListsException);
    }

    TEST_F(DoubleLinkedListFixtureClassTest, IsNotEmpty) {
        EXPECT_EQ(false, nonEmptyListWithDoubles->empty());
        EXPECT_EQ(GENERATED_DOUBLE_NUMBERS_AMOUNT, nonEmptyListWithDoubles->size());
    }

    TEST_F(DoubleLinkedListFixtureClassTest, IsEmptyAfterCleaning) {
        nonEmptyListWithDoubles->clear();
        EXPECT_EQ(true, nonEmptyListWithDoubles->empty());
        EXPECT_EQ(0, nonEmptyListWithDoubles->size());
    }

    TEST_F(DoubleLinkedListFixtureClassTest, FrontBackMethodsAfterCleaning) {
        nonEmptyListWithDoubles->clear();
        EXPECT_THROW(nonEmptyListWithDoubles->front(), LinkedLists::LinkedListsException);
        EXPECT_THROW(nonEmptyListWithDoubles->back(), LinkedLists::LinkedListsException);
    }

    TEST_F(DoubleLinkedListFixtureClassTest, AreListsEqual) {
        auto newListWithDoubles = new LinkedLists::DoubleLinkedList<double>();
        fillCertainDoublesToList(*newListWithDoubles);
        EXPECT_EQ(true, (*newListWithDoubles) == (*nonEmptyListWithDoubles));
        EXPECT_EQ(false, (*newListWithDoubles) != (*nonEmptyListWithDoubles));
        delete newListWithDoubles;
    }

    TEST_F(DoubleLinkedListFixtureClassTest, CopyConstructor) {
        LinkedLists::DoubleLinkedList<double> newListWithDoubles = *nonEmptyListWithDoubles;
    }

    TEST_F(DoubleLinkedListFixtureClassTest, CopyAssignment) {
        auto *newListWithDoubles = new LinkedLists::DoubleLinkedList<double>();
        *newListWithDoubles = *nonEmptyListWithDoubles;
        delete newListWithDoubles;
    }

    TEST_F(DoubleLinkedListFixtureClassTest, MoveConstructor) {
        LinkedLists::DoubleLinkedList<double> newListWithDoubles = std::move(*nonEmptyListWithDoubles);
    }

    TEST_F(DoubleLinkedListFixtureClassTest, MoveAssignment) {
        auto *newListWithDoubles = new LinkedLists::DoubleLinkedList<double>();
        *newListWithDoubles = std::move(*nonEmptyListWithDoubles);
        delete newListWithDoubles;
    }

    TEST_F(DoubleLinkedListFixtureClassTest, IteratorsMethods) {
        auto newListWithDoubles = new LinkedLists::DoubleLinkedList<double>(*nonEmptyListWithDoubles);
        LinkedLists::DoubleLinkedList<double>::const_iterator doublesListItr = newListWithDoubles->cbegin();
        LinkedLists::DoubleLinkedList<double>::const_iterator emptyListItr = nonEmptyListWithDoubles->cbegin();
        while (doublesListItr != newListWithDoubles->cend() && emptyListItr != nonEmptyListWithDoubles->cend()) {
            EXPECT_EQ(*doublesListItr, *emptyListItr);
            doublesListItr++;
            ++emptyListItr;
        }
        delete newListWithDoubles;
    }

    TEST_F(DoubleLinkedListFixtureClassTest, PrintNotEmptyList) {
        std::stringstream listOutputStream;
        listOutputStream << *nonEmptyListWithDoubles;
        std::string generatedFullString(listOutputStream.str());
        const char *generatedCString = generatedFullString.c_str();
        EXPECT_STREQ(OUTPUT_STRING_WITH_NON_EMPTY_LIST_ELEMENTS, generatedCString);
    }

    TEST_F(DoubleLinkedListFixtureClassTest, PrintEmptyList) {
        std::stringstream listOutputStream;
        listOutputStream << *emptyListWithDoubles;
        std::string generatedFullString(listOutputStream.str());
        const char *generatedCString = generatedFullString.c_str();
        EXPECT_STREQ(OUTPUT_STRING_WITH_EMPTY_LIST_ELEMENTS, generatedCString);
    }

    TEST_F(DoubleLinkedListFixtureClassTest, MergesTwoLists) {
        fillCertainDoublesToList(*nonEmptyListWithDoubles);

        auto *newListGeneratedMergeOperator = new LinkedLists::DoubleLinkedList<double>(
                *nonEmptyListWithDoubles + *nonEmptyListWithDoubles);

        LinkedLists::DoubleLinkedList<double>::const_iterator doublesListItr = nonEmptyListWithDoubles->cbegin();
        LinkedLists::DoubleLinkedList<double>::const_iterator emptyListItr = newListGeneratedMergeOperator->cbegin();
        while (doublesListItr != nonEmptyListWithDoubles->cend() && emptyListItr != newListGeneratedMergeOperator->cend()) {
            EXPECT_EQ(*doublesListItr, *emptyListItr);
            doublesListItr++;
            ++emptyListItr;
        }

        delete newListGeneratedMergeOperator;
    }

    TEST_F(DoubleLinkedListFixtureClassTest, AddAnotherList) {
        fillCertainDoublesToList(*nonEmptyListWithDoubles);

        auto *newListGeneratedMergeOperator = new LinkedLists::DoubleLinkedList<double>(*nonEmptyListWithDoubles);
        *newListGeneratedMergeOperator += *nonEmptyListWithDoubles;

        LinkedLists::DoubleLinkedList<double>::const_iterator doublesListItr = nonEmptyListWithDoubles->cbegin();
        LinkedLists::DoubleLinkedList<double>::const_iterator emptyListItr = newListGeneratedMergeOperator->cbegin();
        while (doublesListItr != nonEmptyListWithDoubles->cend() && emptyListItr != newListGeneratedMergeOperator->cend()) {
            EXPECT_EQ(*doublesListItr, *emptyListItr);
            doublesListItr++;
            ++emptyListItr;
        }

        delete newListGeneratedMergeOperator;
    }

    TEST_F(DoubleLinkedListFixtureClassTest, FrontBackPop) {
        auto *saveOriginalList = new LinkedLists::DoubleLinkedList<double>(*nonEmptyListWithDoubles);
        fillCertainDoublesToList(*nonEmptyListWithDoubles);
        fillCertainDoublesToList(*nonEmptyListWithDoubles);
        for (size_t i = 0; i < GENERATED_DOUBLE_NUMBERS_AMOUNT; i++) {
            nonEmptyListWithDoubles->pop_back();
            nonEmptyListWithDoubles->pop_front();
        }
        EXPECT_EQ(true, *saveOriginalList == *nonEmptyListWithDoubles);
        EXPECT_EQ(false, *saveOriginalList != *nonEmptyListWithDoubles);

        delete saveOriginalList;
    }

    TEST_F(DoubleLinkedListFixtureClassTest, InsertRemoveMethods) {
        auto *saveOriginalList = new LinkedLists::DoubleLinkedList<double>(*nonEmptyListWithDoubles);
        double newValue = GENERATED_DOUBLE_NUMBERS_AMOUNT + 1 + 0.01 * (GENERATED_DOUBLE_NUMBERS_AMOUNT + 1);
        nonEmptyListWithDoubles->insert(nonEmptyListWithDoubles->begin() + 2, newValue);
        nonEmptyListWithDoubles->insert(nonEmptyListWithDoubles->begin(), newValue);
        nonEmptyListWithDoubles->insert(nonEmptyListWithDoubles->end() + (-1), newValue);

        nonEmptyListWithDoubles->remove(newValue);

        EXPECT_EQ(true, *saveOriginalList == *nonEmptyListWithDoubles);
        EXPECT_EQ(false, *saveOriginalList != *nonEmptyListWithDoubles);

        delete saveOriginalList;
    }


}