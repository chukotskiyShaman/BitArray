#include <gtest/gtest.h>
#include "bitarray.h"
#include <iostream>

//
TEST(BitArrayTest, AndEQ) {
    BitArray arr1(8, 1);
    BitArray arr2(8, 1);
    arr1&=(arr2);
    EXPECT_EQ("11111111", arr1.to_string());
}

TEST(BitArrayTest, setAll) {
    BitArray arr1(8, 1);
    arr1.set();
    EXPECT_EQ("11111111", arr1.to_string());
}

TEST(BitArrayTest, resetAll) {
    BitArray arr1(8, 1);
    arr1.reset();
    EXPECT_EQ("00000000", arr1.to_string());
}


TEST(BitArrayTest, size) {
    BitArray arr1(8, 1);
    int z = arr1.size();
    EXPECT_EQ(8,z);
}

TEST(BitArrayTest, count) {
    BitArray arr1(8, 1);
    int z = arr1.count();
    EXPECT_EQ(1, true);
}


TEST(BitArrayTest, empty) {
    BitArray arr1(8, 1);
    bool z = arr1.empty();
    EXPECT_EQ(0, z);
}

TEST(BitArrayTest, ravno) {
    BitArray arr1(8, 1);
    BitArray arr2(8, 1);
    EXPECT_EQ(arr1 == arr2, true);
}

TEST(BitArrayTest, new_and) {
  BitArray arr1(8, 1);
  BitArray arr2(8, 1);
  BitArray arr3 = arr1 & arr2;
  EXPECT_EQ("11111111", arr3.to_string());
}

TEST(BitArrayTest, neravno) {
  BitArray arr1(8, 0);
  BitArray arr2(8, 1);
  EXPECT_EQ(arr1 != arr2, true);
}



int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
