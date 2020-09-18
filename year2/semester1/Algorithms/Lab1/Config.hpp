#pragma once
#include <cmath>

constexpr size_t ceil(float num)
{
  return (static_cast<float>(static_cast<size_t>(num)) == num)
         ? static_cast<size_t>(num)
         : static_cast<size_t>(num) + ((num > 0) ? 1 : 0);
}

constexpr std::size_t
        FileSize = 1000,
        ChunkSize = 100,
        ChunkCount = FileSize / ChunkSize; ////todo