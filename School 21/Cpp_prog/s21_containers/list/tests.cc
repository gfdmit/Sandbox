#include <gtest/gtest.h>

//#include "s21_list.h"

TEST(ListTest, Constructor_Empty) {
  s21::list<int> v;
  EXPECT_EQ((int)v.size(), 0);
}

TEST(ListTest, Constructor) {
  size_t size = 10;
  s21::list<int> v(size);
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(v[i], 0);
  }
}

TEST(ListTest, InitializerConstructor) {
  s21::list<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
}

TEST(ListTest, Copy_Empty) {
  s21::list<int> v1;
  s21::list<int> v2(v1);
  EXPECT_EQ((int)v2.size(), 0);
}

TEST(ListTest, CopyConstructor) {
  s21::list<int> v1 = {1, 2, 3};
  s21::list<int> v2(v1);
  EXPECT_EQ((int)v2.size(), (int)v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(ListTest, Move_Empty) {
  s21::list<int> v1;
  s21::list<int> v2(std::move(v1));
  EXPECT_EQ((int)v2.size(), 0);
}

TEST(ListTest, MoveConstructor) {
  s21::list<int> v1 = {1, 2, 3, 4, 5};
  s21::list<int> v2(std::move(v1));
  EXPECT_EQ(v2[3], 4);
}

TEST(ListTest, MoveOperator) {
  s21::list<int> v1 = {1, 2, 3, 4};
  s21::list<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ((int)v2.size(), 4);
}

TEST(ListTest, MoveOperator_Empty) {
  s21::list<int> v1;
  s21::list<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
}

TEST(ListTest, Begin_ValidList) {
  s21::list<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  *it = 10;
  EXPECT_EQ(v[0], 10);
}

TEST(ListTest, End_ValidList) {
  s21::list<int> v = {1, 2, 3, 4, 5};
  auto it = v.end();
  EXPECT_EQ(*--it, 5);
}

TEST(ListTest, MaxSize) {
  s21::list<int> v;
  EXPECT_EQ((int)v.max_size(), 2);
}

TEST(ListTest, Insert_Beginning) {
  s21::list<int> v = {2, 3, 4};
  auto it = v.insert(v.begin(), 1);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(*it, 1);
}

TEST(ListTest, Insert_Middle) {
  s21::list<int> v = {1, 3, 4};
  auto iter = v.begin();
  auto it = v.insert(++iter, 2);
  EXPECT_EQ((int)v.size(), 4);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(*it, 2);
}

TEST(ListTest, Insert_End) {
  s21::list<int> v = {1, 2, 3};
  auto it = v.insert(v.end(), 4);
  EXPECT_EQ((int)v.size(), 4);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(*it, 4);
}

TEST(ListTest, Erase_Beginning) {
  s21::list<int> v = {1, 2, 3, 4};
  v.erase(v.begin());
  EXPECT_EQ((int)v.size(), 3);
  EXPECT_EQ(v[0], 2);
}

TEST(ListTest, Erase_Middle) {
  s21::list<int> v = {1, 2, 3, 4};
  v.erase(++v.begin());
  EXPECT_EQ((int)v.size(), 3);
  EXPECT_EQ(v[1], 3);
}

TEST(ListTest, Erase_End) {
  s21::list<int> v = {1, 2, 3, 4};
  v.erase(--v.end());
  EXPECT_EQ((int)v.size(), 3);
  EXPECT_EQ(v[2], 3);
}

TEST(ListTest, PushBack_NonEmptyList) {
  s21::list<int> v = {1, 2, 3};
  v.push_back(4);
  EXPECT_EQ((int)v.size(), 4);
  EXPECT_EQ(v[3], 4);
}

TEST(ListTest, PopBack_NonEmptyList) {
  s21::list<int> v = {1, 2, 3};
  v.pop_back();
  EXPECT_EQ(v.back(), 2);
}

TEST(ListTest, Swap_NonEmptyLists) {
  s21::list<int> v1 = {1, 1, 1};
  s21::list<int> v2 = {0, 0, 0};

  v1.swap(v2);
  EXPECT_EQ(v1[0], 0);
  EXPECT_EQ(v1[2], 0);

  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 1);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}