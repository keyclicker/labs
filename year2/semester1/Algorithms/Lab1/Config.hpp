#pragma once
#include <cstddef>

constexpr std::size_t
        FileSize = 9500000,
        ChunkSize = 1000000,
        ChunkCount = FileSize / ChunkSize; ////todo