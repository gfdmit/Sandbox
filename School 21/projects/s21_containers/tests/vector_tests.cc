#include "main_tests.h"

TEST(VectorTest, Constructor_Empty) {
  s21::vector<int> v;
  EXPECT_EQ((int)v.size(), 0);
}

// TEST(VectorTest, Constructor) {
//   size_t size = 10;
//   s21::vector<int> v(size);
//   for (size_t i = 0; i < size; ++i) {
//     EXPECT_EQ(v[i], 0);
//   }
// }

TEST(VectorTest, InitializerConstructor) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, Copy_Empty) {
  s21::vector<int> v1;
  s21::vector<int> v2(v1);
  EXPECT_EQ((int)v2.size(), 0);
}

TEST(VectorTest, CopyConstructor) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(v1);
  EXPECT_EQ((int)v2.size(), (int)v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(VectorTest, Move_Empty) {
  s21::vector<int> v1;
  s21::vector<int> v2(std::move(v1));
  EXPECT_EQ((int)v2.size(), 0);
}

TEST(VectorTest, MoveConstructor) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::vector<int> v2(std::move(v1));
  EXPECT_EQ(v2[3], 4);
}

TEST(VectorTest, MoveOperator) {
  s21::vector<int> v1 = {1, 2, 3, 4};
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ((int)v2.size(), 4);
}

TEST(VectorTest, MoveOperator_Empty) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
}

TEST(VectorTest, At_ValidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(2), 3);
}

TEST(VectorTest, At_InvalidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_THROW(v.at(5), std::out_of_range);
  EXPECT_THROW(v.at(10), std::out_of_range);
}

TEST(VectorTest, IndexOperator_ValidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, IndexOperator_InvalidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_ANY_THROW(v[5]);
  EXPECT_ANY_THROW(v[10]);
}

TEST(VectorTest, Data_ValidVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  int* dataPtr = v.data();
  EXPECT_EQ(*++dataPtr, 2);
  *dataPtr = 10;
  EXPECT_EQ(v[1], 10);
}

TEST(VectorTest, Begin_ValidVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  *it = 10;
  EXPECT_EQ(v[0], 10);
}

TEST(VectorTest, End_ValidVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.end();
  EXPECT_EQ(*--it, 5);
}

TEST(VectorTest, MaxSize) {
  s21::vector<int> b;
  EXPECT_GT(b.max_size(), (std::size_t)1);
}

TEST(VectorTest, Reserve_IncreaseCapacity) {
  s21::vector<int> v;
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity + 10;
  v.reserve(newCapacity);
  EXPECT_GE(v.capacity(), newCapacity);
}

TEST(VectorTest, ShrinkToFit_EmptyVector) {
  s21::vector<int> v;
  v.shrink_to_fit();
  EXPECT_GE((int)v.capacity(), 0);
}

TEST(VectorTest, ShrinkToFit_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  size_t initialCapacity = v.capacity();
  v.pop_back();
  v.shrink_to_fit();
  EXPECT_LE(v.capacity(), initialCapacity);
}

TEST(VectorTest, Insert_Beginning) {
  s21::vector<int> v = {2, 3, 4};
  auto it = v.insert(v.begin(), 1);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(*it, 1);
}

TEST(VectorTest, Insert_Middle) {
  s21::vector<int> v = {1, 3, 4};
  auto iter = v.begin();
  auto it = v.insert(++iter, 2);
  EXPECT_EQ((int)v.size(), 4);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(*it, 2);
}

TEST(VectorTest, Insert_End) {
  s21::vector<int> v = {1, 2, 3};
  auto it = v.insert(v.end(), 4);
  EXPECT_EQ((int)v.size(), 4);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(*it, 4);
}

TEST(VectorTest, Erase_Beginning) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.begin());
  EXPECT_EQ((int)v.size(), 3);
  EXPECT_EQ(v[0], 2);
}

TEST(VectorTest, Erase_Middle) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(++v.begin());
  EXPECT_EQ((int)v.size(), 3);
  EXPECT_EQ(v[1], 3);
}

TEST(VectorTest, Iterator_const_eq) {
  s21::vector<int> v1 = {1, 2, 1};
  s21::vector<int> v2 = {0, 2, 0};
  auto iter1 = ++v1.begin();
  auto iter2 = ++v2.begin();
  int res = 0;
  if (iter1 == iter2) res = 1;
  EXPECT_EQ(res, 1);
}

TEST(VectorTest, Erase_End) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(--v.end());
  EXPECT_EQ((int)v.size(), 3);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PushBack_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3};
  v.push_back(4);
  EXPECT_EQ((int)v.size(), 4);
  EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, PopBack_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3};
  v.pop_back();
  EXPECT_EQ(v.back(), 2);
}

TEST(VectorTest, Swap_NonEmptyVectors) {
  s21::vector<int> v1 = {1, 1, 1};
  s21::vector<int> v2 = {0, 0, 0};

  v1.swap(v2);
  EXPECT_EQ(v1[0], 0);
  EXPECT_EQ(v1[2], 0);

  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 1);
}

TEST(VectorTest, Iterator_eq) {
  s21::vector<int> v1 = {1, 2, 1};
  s21::vector<int> v2 = {0, 2, 0};
  auto iter1 = ++v1.begin();
  auto iter2 = ++v2.begin();
  int res = 0;
  if (iter1 == iter2) res = 1;
  EXPECT_EQ(res, 1);
}
