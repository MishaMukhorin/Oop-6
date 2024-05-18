#include <gtest/gtest.h>
#include "../CStringList.h"
#include <algorithm>

class CStringListTest : public ::testing::Test {
protected:
    CStringList list;
};

TEST_F(CStringListTest, DefaultConstructor) {
    EXPECT_EQ(list.GetSize(), 0);
    EXPECT_TRUE(list.IsEmpty());
}

TEST_F(CStringListTest, AddToBeginning) {
    list.AddToBeginning("World");
    list.AddToBeginning("Hello");

    EXPECT_EQ(list.GetSize(), 2);
    EXPECT_FALSE(list.IsEmpty());

    auto it = list.begin();
    EXPECT_EQ(*it, "Hello");
    ++it;
    EXPECT_EQ(*it, "World");
}

// Test adding elements to the end
TEST_F(CStringListTest, AddToEnd) {
    list.AddToEnd("Hello");
    list.AddToEnd("World");

    EXPECT_EQ(list.GetSize(), 2);
    EXPECT_FALSE(list.IsEmpty());

    auto it = list.begin();
    EXPECT_EQ(*it, "Hello");
    ++it;
    EXPECT_EQ(*it, "World");
}

// Test copy constructor
TEST_F(CStringListTest, CopyConstructor) {
    list.AddToEnd("Hello");
    list.AddToEnd("World");

    CStringList copyList(list);

    EXPECT_EQ(copyList.GetSize(), 2);
    auto it = copyList.begin();
    EXPECT_EQ(*it, "Hello");
    ++it;
    EXPECT_EQ(*it, "World");

    auto originalIt = list.begin();
    auto copyIt = copyList.begin();
    while (originalIt != list.end() && copyIt != copyList.end()) {
        EXPECT_EQ(*originalIt, *copyIt);
        ++originalIt;
        ++copyIt;
    }
    EXPECT_EQ(originalIt, list.end());
    EXPECT_EQ(copyIt, copyList.end());
    //done проверить равенство
}

// Test move constructor
TEST_F(CStringListTest, MoveConstructor) {
    list.AddToEnd("Hello");
    list.AddToEnd("World");

    CStringList moveList(std::move(list));

    EXPECT_EQ(moveList.GetSize(), 2);
    auto it = moveList.begin();
    EXPECT_EQ(*it, "Hello");
    ++it;
    EXPECT_EQ(*it, "World");

    EXPECT_EQ(list.GetSize(), 0);
    EXPECT_TRUE(list.IsEmpty());
}

// Test copy assignment operator
TEST_F(CStringListTest, CopyAssignmentOperator) {
    list.AddToEnd("Hello");
    list.AddToEnd("World");

    CStringList copyList;
    copyList = list;

    EXPECT_EQ(copyList.GetSize(), 2);
    auto it = copyList.begin();
    EXPECT_EQ(*it, "Hello");
    ++it;
    EXPECT_EQ(*it, "World");
}    //todo проверить равенство


// Test move assignment operator
TEST_F(CStringListTest, MoveAssignmentOperator) {
    list.AddToEnd("Hello");
    list.AddToEnd("World");

    CStringList moveList;
    moveList = std::move(list);

    EXPECT_EQ(moveList.GetSize(), 2);
    auto it = moveList.begin();
    EXPECT_EQ(*it, "Hello");
    ++it;
    EXPECT_EQ(*it, "World");

    EXPECT_EQ(list.GetSize(), 0);
    EXPECT_TRUE(list.IsEmpty());
}

// Test Clear
TEST_F(CStringListTest, ClearList) {
    list.AddToEnd("Hello");
    list.AddToEnd("World");

    list.Clear();

    EXPECT_EQ(list.GetSize(), 0);
    EXPECT_TRUE(list.IsEmpty());
}

// Test Insert
TEST_F(CStringListTest, Insert) {
    list.AddToEnd("Hello");
    list.AddToEnd("World");

    auto it = list.begin();
    ++it;
    list.Insert(it, "Inserted");

    EXPECT_EQ(list.GetSize(), 3);
    it = list.begin();
    EXPECT_EQ(*it, "Hello");
    ++it;
    EXPECT_EQ(*it, "Inserted");
    ++it;
    EXPECT_EQ(*it, "World");
}

// Test Erase
TEST_F(CStringListTest, Erase) {
    list.AddToEnd("Hello");
    list.AddToEnd("World");

    auto it = list.begin();
    list.Erase(it);

    EXPECT_EQ(list.GetSize(), 1);
    it = list.begin();
    EXPECT_EQ(*it, "World");
}

// Test iterators
TEST_F(CStringListTest, Iterators) {
    list.AddToEnd("Hello");
    list.AddToEnd("World");

    auto it = list.begin();
    EXPECT_EQ(*it, "Hello");
    ++it;
    EXPECT_EQ(*it, "World");
    ++it;
    EXPECT_EQ(it, list.end());

    auto rit = list.rbegin();
    EXPECT_EQ(rit.m_node->data, "World");
    ++rit;
    EXPECT_EQ(rit.m_node->data, "Hello");
    ++rit;
    EXPECT_EQ(rit, list.rend());
}

TEST_F(CStringListTest, ConstantIterators) {
    list.AddToEnd("Hello");
    list.AddToEnd("World");

    auto it = list.cbegin();
    EXPECT_EQ(*it, "Hello");
    ++it;
    EXPECT_EQ(*it, "World");
    ++it;
    EXPECT_TRUE(it == list.cend());

    auto rit = list.crbegin();
    EXPECT_EQ(*rit, "World");
    ++rit;
    EXPECT_EQ(*rit, "Hello");
    ++rit;
    EXPECT_TRUE(rit == list.crend());
}

TEST_F(CStringListTest, STLCompatibility) {
    list.AddToEnd("World");
    list.AddToEnd("Hello");
    list.AddToEnd("Foo");
    list.AddToEnd("Bar");

    std::transform(list.begin(), list.end(), list.begin(),
                   [](const std::string &s) {
                        std::string result;
                        result.reserve(s.length());
                        std::transform(s.begin(), s.end(), std::back_inserter(result),
                                      [](unsigned char c) { return std::tolower(c); });
                        return result; });
    auto it = list.begin();
    EXPECT_EQ(*it, "world");
    ++it;
    EXPECT_EQ(*it, "hello");
    ++it;
    EXPECT_EQ(*it, "foo");
    ++it;
    EXPECT_EQ(*it, "bar");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
