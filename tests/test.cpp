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
  delete a;
}

TEST(SharedPtr, CopyConstructor) {
  const SharedPtr p1= SharedPtr(new int(-1));
  SharedPtr p2 = SharedPtr (p1);
  EXPECT_EQ(*p2, *p1);
  EXPECT_EQ(p1.use_count(), 2);
  EXPECT_EQ(p2.use_count(), 2);
}

TEST(SharedPtr, MoveConstructor) {
  SharedPtr <int> p(SharedPtr(new int(7)));
  EXPECT_EQ(*p, 7);
  EXPECT_EQ(p.use_count(), 1);
  SharedPtr <int> p1(new int(0));
  SharedPtr <int> p2(std::move(p1));
  EXPECT_EQ(*p2, 0);
  EXPECT_EQ(p1.get(), nullptr);
  EXPECT_EQ(p2.use_count(), 1);
}

TEST(SharedPtr, Equal) {
  SharedPtr <int> p(new int(10));
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
  SharedPtr <int> p(new int(10));
  EXPECT_TRUE(p);
  SharedPtr <int> p1;
  EXPECT_FALSE(p1);
}

TEST(SharedPtr, GetObject) {
  SharedPtr <std::string> p(new std::string ("C++"));
  EXPECT_EQ(p->length(), 3);
}

TEST(SharedPtr, Reset) {
  SharedPtr <int> p(new int(10));
  p.reset();
  EXPECT_FALSE(p);
  int* a = new int(15);
  SharedPtr <int> p1(a);
  p.reset(a);
  EXPECT_EQ(*p, *p1);
  delete a;
}

TEST(SharedPtr, Swap) {
  SharedPtr <int> p1(new int(10));
  SharedPtr <int> p2(new int(4));
  SharedPtr <int> p3(p2);
  p1.swap(p2);
  EXPECT_EQ(*p1, 4);
  EXPECT_EQ(p1.use_count(), 2);
  EXPECT_EQ(*p2, 10);
  EXPECT_EQ(p2.use_count(), 1);
}
