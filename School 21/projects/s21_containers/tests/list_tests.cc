#include <list>

#include "main_tests.h"

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

TEST(ListTest, Index_Throw) {
  s21::list<int> v = {1, 2, 3};
  EXPECT_THROW(v[3], std::out_of_range);
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

TEST(ListTest, CBegin_ValidList) {
  s21::list<int> v = {1, 2, 3, 4, 5};
  auto it = v.cbegin(), it2 = v.cend();
  EXPECT_EQ(*it, 1);
  it2 = ++it;
  EXPECT_EQ(*it2, 2);
}

TEST(ListTest, CEnd_ValidList) {
  s21::list<int> v = {1, 2, 3, 4, 5};
  auto it = v.cend();
  EXPECT_EQ(*--it, 5);
  EXPECT_EQ(*--it, 4);
}

TEST(ListTest, End_ValidList) {
  s21::list<int> v = {1, 2, 3, 4, 5};
  auto it = v.end();
  EXPECT_EQ(*--it, 5);
}

TEST(ListTest, MaxSize) {
  s21::list<int> v;
  std::list<int> v1;
  EXPECT_EQ(v.max_size(), v1.max_size());
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

TEST(ListTest, Insert_Many_Front) {
  s21::list<int> v = {5, 6, 7};
  v.insert_many_front(4, 3, 2);
  EXPECT_EQ(v[0], 2);
  EXPECT_EQ(v.size(), 6);
}

TEST(ListTest, Insert_Many_Back) {
  s21::list<int> v = {1, 2, 3};
  v.insert_many_back(4, 5, 6);
  EXPECT_EQ(v[5], 6);
  EXPECT_EQ(v.size(), 6);
}

TEST(ListTest, Insert_Many) {
  s21::list<int> v = {5, 6, 7};
  auto it = v.insert_many(v.begin(), 2, 3, 4);
  EXPECT_EQ(v[0], 2);
  EXPECT_EQ(v.size(), 6);
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

TEST(ListTest, PushFront_NonEmptyList) {
  s21::list<int> v = {2, 3, 4};
  v.push_front(1);
  EXPECT_EQ((int)v.size(), 4);
  EXPECT_EQ(v[0], 1);
}

TEST(ListTest, PushFront_EmptyList) {
  s21::list<int> v = {};
  v.push_front(1);
  EXPECT_EQ((int)v.size(), 1);
  EXPECT_EQ(v[0], 1);
}

TEST(ListTest, PushFront_AlmostEmptyList) {
  s21::list<int> v = {2};
  v.push_front(1);
  EXPECT_EQ((int)v.size(), 2);
  EXPECT_EQ(v[0], 1);
}

TEST(ListTest, PopBack_NonEmptyList) {
  s21::list<int> v = {1, 2, 3};
  v.pop_back();
  EXPECT_EQ(v.back(), 2);
}

TEST(ListTest, PopFront_NonEmptyList) {
  s21::list<int> v = {1, 2, 3};
  v.pop_front();
  EXPECT_EQ(v.front(), 2);
}

TEST(ListTest, PopFront_AlmostEmptyList) {
  s21::list<int> v = {1, 2};
  v.pop_front();
  EXPECT_TRUE(v.size() == 1);
}

TEST(ListTest, Unique) {
  s21::list<int> v = {1, 1, 2, 2, 2, 2, 4, 4, 5, 6};
  s21::list<int> exp = {1, 2, 4, 5, 6};
  v.unique();
  EXPECT_EQ(v.size(), exp.size());
  EXPECT_EQ(v[0], exp[0]);
  EXPECT_EQ(v[2], exp[2]);
  EXPECT_EQ(v[4], exp[4]);
}

TEST(ListTest, Reverse) {
  s21::list<int> v = {1, 2, 3};
  s21::list<int> exp = {3, 2, 1};
  v.reverse();
  EXPECT_EQ(v.size(), exp.size());
  EXPECT_EQ(v[0], exp[0]);
  EXPECT_EQ(v[1], exp[1]);
  EXPECT_EQ(v[2], exp[2]);
}

TEST(ListTest, Splice) {
  s21::list<int> v = {1, 5, 6};
  s21::list<int> sp = {2, 3, 4};
  v.splice(++v.begin(), sp);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
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

TEST(ListTest, Merge) {
  s21::list<int> v1 = {1, 3, 5, 7};
  s21::list<int> v2 = {2, 4, 6};
  v1.merge(v2);
  EXPECT_EQ(v1.size(), 7);
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(v1[2], 3);
  EXPECT_EQ(v1[3], 4);
  EXPECT_EQ(v1[4], 5);
  EXPECT_EQ(v1[5], 6);
  EXPECT_EQ(v1[6], 7);
}

TEST(ListTest, Sort) {
  s21::list<int> v1 = {1, 3, 6, 5, 4, 7, 2};
  v1.sort();
  EXPECT_EQ(v1.size(), 7);
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(v1[2], 3);
  EXPECT_EQ(v1[3], 4);
  EXPECT_EQ(v1[4], 5);
  EXPECT_EQ(v1[5], 6);
  EXPECT_EQ(v1[6], 7);
}