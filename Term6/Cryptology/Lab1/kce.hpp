#pragma once

#include <vector>
#include "Data.hpp"

inline Data kce(Data data, Data key) {
  Data keyHash = key.md5();

  auto blockSize = keyHash.getByteSize();
  auto blockCount = data.getByteSize() / blockSize 
  + (data.getByteSize() % blockSize > 0);

  std::vector<uint8_t> result(data.getByteSize());

  auto iterHash = keyHash;
  for (int i = 0; i < blockCount; i++) {
    iterHash = iterHash.md5() ^ keyHash;
    
    auto block = data.sliceBytes(i * blockSize, (i + 1) * blockSize);
    auto cipher = block ^ iterHash;

    for (int j = 0; j < blockSize; j++) {
      result[i * blockSize + j] = cipher.getByte(j);
    }
  }

  data.resizeBytes(keyHash.getByteSize());
  data ^= keyHash ^ keyHash.sha512();

  return data;
}