#include <gtest/gtest.h>
#include "ExternalSort.hpp"
#include "Utilities.hpp"

constexpr std::size_t
FileSize = 1000000,
ChunkSize = 200000;

TEST(Sort, SizeTest) {
  genData<int>("inputTest", FileSize);
  externalMergeSort<int>("inputTest", "outputTest", FileSize, ChunkSize);

  EXPECT_EQ(binSize<int>("inputTest"), binSize<int>("outputTest"));
}

TEST(Sort, IsSorted) {
  genData<int>("inputTest", FileSize);
  externalMergeSort<int>("inputTest", "outputTest", FileSize, ChunkSize);
  sortFile<int>("inputTest", "memSortTest", FileSize);

  EXPECT_TRUE(compFiles<int>("outputTest", "memSortTest", FileSize));
}