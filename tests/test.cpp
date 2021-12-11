// Copyright 2021 Your Name <your_email>
#include <gtest/gtest.h>
#include <SharedPtr.hpp>
#include <string.h>

TEST(SharedPtr, DefaultConstructor) {
  SharedPtr <int> p = SharedPtr<int>();
  EXPECT_EQ(p.get(), nullptr);
  EXPECT_EQ(p.use_count(), 0);
}

TEST(SharedPtr, InitConstructor) {
  int* a = new int(5);
  SharedPtr p = SharedPtr(a);
  EXPECT_EQ(p.get(), a);
  EXPECT_EQ(p.use_count(), 1);
}

TEST(SharedPtr, CopyConstructor) {
  int* a = new int(-1);
  const SharedPtr p1= SharedPtr(a);
  SharedPtr p2 = SharedPtr (p1);
  EXPECT_EQ(*p2, *p1);
  EXPECT_EQ(p1.use_count(), 2);
  EXPECT_EQ(p2.use_count(), 2);
}

TEST(SharedPtr, MoveConstructor) {
  int* a = new int(7);
  SharedPtr p = SharedPtr(SharedPtr(a));
  EXPECT_EQ(*p, 7);
  EXPECT_EQ(p.use_count(), 1);
  int* b = new int(0);
  SharedPtr <int> p1(b);
  SharedPtr <int> p2(std::move(p1));
  EXPECT_EQ(*p2, 0);
  EXPECT_EQ(p1.get(), nullptr);
  EXPECT_EQ(p2.use_count(), 1);
  delete a;
  delete b;
}

TEST(SharedPtr, Equal) {
  int* a = new int(10);
  SharedPtr <int> p(a);
  SharedPtr <int> p1 = p;
  EXPECT_EQ(*p, *p1);
  EXPECT_EQ(p.use_count(), 2);
  EXPECT_EQ(p1.use_count(), 2);
  SharedPtr <int> p2 = std::move(p);
  EXPECT_EQ(*p2, 10);
  EXPECT_EQ(p.get(), nullptr);
  EXPECT_EQ(p2.use_count(), 2);
}

TEST(SharedPtr, Bool) {
  int* a = new int(10);
  SharedPtr <int> p(a);
  EXPECT_TRUE(p);
  SharedPtr <int> p1;
  EXPECT_FALSE(p1);
}

TEST(SharedPtr, GetObject) {
  auto* str = new std::string("C++");
  auto* p = new SharedPtr <std::string> (str);
  EXPECT_EQ((*p)->length(), 3);
  delete str;
  delete p;
}

TEST(SharedPtr, Reset) {
  int* a = new int(10);
  SharedPtr <int> p(a);
  p.reset();
  EXPECT_FALSE(p);
  int* b = new int(15);
  SharedPtr <int> p1(b);
  p.reset(b);
  EXPECT_EQ(*p, *p1);
  delete a;
  delete b;
}

TEST(SharedPtr, Swap) {
  int* a = new int(10);
  int* b = new int(4);
  SharedPtr <int> p1(a);
  SharedPtr <int> p2(b);
  SharedPtr <int> p3(p2);
  p1.swap(p2);
  EXPECT_EQ(*p1, 4);
  EXPECT_EQ(p1.use_count(), 2);
  EXPECT_EQ(*p2, 10);
  EXPECT_EQ(p2.use_count(), 1);
  delete a;
  delete b;
}