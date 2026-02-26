#include "main_tests.h"

TEST(StackTest, Constructor_Empty) {
  s21::stack<int> v;
  EXPECT_EQ((int)v.size(), 0);
}

TEST(StackTest, Index_Throw) {
  s21::stack<int> v = {1, 2, 3};
  EXPECT_THROW(v[3], std::out_of_range);
}

TEST(StackTest, InitializerConstructor) {
  s21::stack<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
}

TEST(StackTest, Copy_Empty) {
  s21::stack<int> v1;
  s21::stack<int> v2(v1);
  EXPECT_EQ((int)v2.size(), 0);
}

TEST(StackTest, CopyConstructor) {
  s21::stack<int> v1 = {1, 2, 3};
  s21::stack<int> v2(v1);
  EXPECT_EQ((int)v2.size(), (int)v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(StackTest, Move_Empty) {
  s21::stack<int> v1;
  s21::stack<int> v2(std::move(v1));
  EXPECT_EQ((int)v2.size(), 0);
}

TEST(StackTest, MoveConstructor) {
  s21::stack<int> v1 = {1, 2, 3, 4, 5};
  s21::stack<int> v2(std::move(v1));
  EXPECT_EQ(v2[3], 4);
}

TEST(StackTest, MoveOperator) {
  s21::stack<int> v1 = {1, 2, 3, 4};
  s21::stack<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ((int)v2.size(), 4);
}

TEST(StackTest, MoveOperator_Empty) {
  s21::stack<int> v1;
  s21::stack<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
}

TEST(StackTest, Insert_Many_Front) {
  s21::stack<int> v = {4, 5, 6};
  v.insert_many_front(3, 2, 1);
  EXPECT_EQ(v[5], 6);
  EXPECT_EQ(v.size(), 6);
}

TEST(StackTest, Push_NonEmptyStack) {
  s21::stack<int> v = {1, 2, 3};
  v.push(4);
  EXPECT_EQ((int)v.size(), 4);
  EXPECT_EQ(v[3], 4);
}

TEST(StackTest, Pop_NonEmptyStack) {
  s21::stack<int> v = {1, 2, 3};
  v.pop();
  EXPECT_EQ(v.top(), 2);
}

TEST(StackTest, Top_EmptyStack) {
  s21::stack<int> v = {};
  EXPECT_THROW(v.top(), std::out_of_range);
}

TEST(StackTest, Pop_EmptyStack) {
  s21::stack<int> v = {};
  EXPECT_THROW(v.pop(), std::out_of_range);
}

TEST(StackTest, Swap_NonEmptyStacks) {
  s21::stack<int> v1 = {1, 1, 1};
  s21::stack<int> v2 = {0, 0, 0};

  v1.swap(v2);
  EXPECT_EQ(v1[0], 0);
  EXPECT_EQ(v1[2], 0);

  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 1);
}