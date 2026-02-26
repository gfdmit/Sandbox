#include <array>

#include "main_tests.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 5> arr;
  int size = (int)arr.size();
  EXPECT_EQ(size, 5);
}

TEST(ArrayTest, InitListConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ((size_t)arr[i], (i) + 1);
  }
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> arrCopy(arr);
  for (size_t i = 0; i < arrCopy.size(); ++i) {
    EXPECT_EQ(arrCopy[i], arr[i]);
  }
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> arrMoved(std::move(arr));
  for (size_t i = 0; i < arrMoved.size(); ++i) {
    EXPECT_EQ(arrMoved[i], static_cast<int>(i) + 1);
  }
}

TEST(ArrayTest, Begin) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.begin();
  EXPECT_EQ(*it, 1);
  *it = 10;
  EXPECT_EQ(arr[0], 10);
}

TEST(ArrayTest, End) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto it = arr.end();
  auto beginIt = arr.begin();
  EXPECT_EQ(it, beginIt + 4);
}

TEST(ArrayTest, At_OutOfBounds) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_THROW(arr.at(10), std::out_of_range);
}

TEST(ArrayTest, Front) {
  s21::array<int, 5> arr = {9, 2, 3, 4, 5};
  int value = arr.front();
  EXPECT_EQ(value, 9);
}

TEST(ArrayTest, Back) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 9};
  int value = arr.back();
  EXPECT_EQ(value, 9);
}

TEST(ArrayTest, Empty_Array) {
  s21::array<int, 5> arr = {};
  EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, Not_Empty_Array) {
  s21::array<int, 2> arr = {1, 2};
  EXPECT_TRUE(!arr.empty());
}

TEST(ArrayTest, MaxSize) {
  s21::array<int, 5> arr;
  // The max size of an array with a specified size is the same as its declared
  // size
  EXPECT_EQ((int)arr.max_size(), 5);
}

TEST(ArrayTest, Swap) {
  s21::array<int, 5> arr1 = {1, 1, 1, 1, 1};
  s21::array<int, 5> arr2 = {0, 0, 0, 0, 0};
  arr1.swap(arr2);
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], 0);
  }
  for (size_t i = 0; i < arr2.size(); ++i) {
    EXPECT_EQ(arr2[i], 1);
  }
}

TEST(ArrayTest, Fill) {
  s21::array<int, 5> arr;
  arr.fill(100);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 100);
  }
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::array<int, 5> arr1 = {1, 1, 1, 1, 1};
  s21::array<int, 5> arr2 = {0, 0, 0, 0, 0};
  arr1 = std::move(arr2);
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], 0);
  }
  for (size_t i = 0; i < arr2.size(); ++i) {
    EXPECT_EQ(arr2[i], 0);
  }
}
