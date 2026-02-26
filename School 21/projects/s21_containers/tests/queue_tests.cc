#include "main_tests.h"

TEST(QueueTest, Constructor_Empty) {
  s21::queue<int> v;
  EXPECT_EQ((int)v.size(), 0);
}

TEST(QueueTest, Index_Throw) {
  s21::queue<int> v = {1, 2, 3};
  EXPECT_THROW(v[3], std::out_of_range);
}

TEST(QueueTest, InitializerConstructor) {
  s21::queue<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
}

TEST(QueueTest, Copy_Empty) {
  s21::queue<int> v1;
  s21::queue<int> v2(v1);
  EXPECT_EQ((int)v2.size(), 0);
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> v1 = {1, 2, 3};
  s21::queue<int> v2(v1);
  EXPECT_EQ((int)v2.size(), (int)v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(QueueTest, Move_Empty) {
  s21::queue<int> v1;
  s21::queue<int> v2(std::move(v1));
  EXPECT_EQ((int)v2.size(), 0);
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> v1 = {1, 2, 3, 4, 5};
  s21::queue<int> v2(std::move(v1));
  EXPECT_EQ(v2[3], 4);
}

TEST(QueueTest, MoveOperator) {
  s21::queue<int> v1 = {1, 2, 3, 4};
  s21::queue<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ((int)v2.size(), 4);
}

TEST(QueueTest, MoveOperator_Empty) {
  s21::queue<int> v1;
  s21::queue<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
}

TEST(QueueTest, Insert_Many_Back) {
  s21::queue<int> v = {1, 2, 3};
  v.insert_many_back(4, 5, 6);
  EXPECT_EQ(v[5], 6);
  EXPECT_EQ(v.size(), 6);
}

TEST(QueueTest, Push_NonEmptyQueue) {
  s21::queue<int> v = {1, 2, 3};
  v.push(4);
  EXPECT_EQ((int)v.size(), 4);
  EXPECT_EQ(v[3], 4);
}

TEST(QueueTest, Pop_NonEmptyQueue) {
  s21::queue<int> v = {1, 2, 3};
  v.pop();
  EXPECT_EQ(v.front(), 2);
  EXPECT_EQ(v.back(), 3);
}

TEST(QueueTest, Pop_EmptyQueue) {
  s21::queue<int> v = {};
  EXPECT_THROW(v.pop(), std::out_of_range);
}

TEST(QueueTest, Swap_NonEmptyQueues) {
  s21::queue<int> v1 = {1, 1, 1};
  s21::queue<int> v2 = {0, 0, 0};

  v1.swap(v2);
  EXPECT_EQ(v1[0], 0);
  EXPECT_EQ(v1[2], 0);

  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 1);
}