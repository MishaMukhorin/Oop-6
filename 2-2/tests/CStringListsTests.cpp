#include <gtest/gtest.h>
#include "../CStringList.h"  // Include your CStringList header file

// Test fixture for CStringList
class CStringListTest : public ::testing::Test {
protected:
    CStringList list;

    void SetUp() override {
        // Code here will be called immediately after the constructor (right before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right before the destructor).
    }
};

// Test default constructor
TEST_F(CStringListTest, DefaultConstructor) {
    EXPECT_EQ(list.GetSize(), 0);
    EXPECT_TRUE(list.IsEmpty());
}

// Test adding elements to the beginning
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
}

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

// Test ClearList
TEST_F(CStringListTest, ClearList) {
    list.AddToEnd("Hello");
    list.AddToEnd("World");

    list.ClearList();

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
    EXPECT_EQ(*rit, "World");
    rit++;
    EXPECT_EQ(*rit, "Hello");
    rit++;
    EXPECT_EQ(rit, list.rend());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
