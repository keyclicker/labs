#include <string>
#include <bitset>
#include <unordered_map>
#include <iostream>

#include "des.hpp"
#include "des_perm.hpp"

Data F(const Data &data, const Data &key) {
  auto ed_block = data.permutate(exp_d, 48);
  auto xb = key ^ ed_block;

  auto s_block = Data(32);
  for (int i = 0; i < 8; i++) {
    size_t row = 2 * xb[i * 6] + xb[i * 6 + 5];
    size_t col = 8 * xb[i * 6 + 1] + 4 * xb[i * 6 + 2]
                 + 2 * xb[i * 6 + 3] + xb[i * 6 + 4];

    auto val = s[i][row][col];

    s_block[i * 4] = val >> 3 & 1;
    s_block[i * 4 + 1] = val >> 2 & 1;
    s_block[i * 4 + 2] = val >> 1 & 1;
    s_block[i * 4 + 3] = val & 1;
  }

  return s_block.permutate(per, 32);
}

Data des_block(const Data &block, const std::vector <Data> &round_keys) {
  auto ip_block = block.permutate(initial_perm, 64);
  auto [left, right] = ip_block.halve();

  for (size_t i = 0; i < 16; i++) {
    left = left ^ F(right, round_keys[i]);
    std::swap(left, right);
  }

  return (right + left).permutate(final_perm, 64);
}

auto get_keys(const Data &key) {
  auto p_key = key.permutate(keyp, 56);
  auto [left, right] = p_key.halve();

  std::vector<Data> round_keys(16);
  for (size_t i = 0; i < 16; i++) {
    left = left.shift_left(shift_table[i]);
    right = right.shift_left(shift_table[i]);

    auto round_key = (left + right).permutate(key_comp, 48);
    round_keys[i] = round_key;
  }

  return round_keys;
}

Data des_encrypt_block(const Data &block, const Data &key) {
  auto rkb = get_keys(key);
  return des_block(block, rkb);
}

Data des_decrypt_block(const Data &block, const Data &key) {
  auto rkb = get_keys(key);
  reverse(rkb.begin(), rkb.end());
  return des_block(block, rkb);
}

const Data default_iv = Data::from_hex("675A69675E5A6B5A");

Data des_cfb_encrypt(const Data &data, const Data &key) {
  auto chunks = data.chop(64);

  auto iv = default_iv;
  for (size_t i = 0; i < chunks.size(); i++) {
    iv = chunks[i] ^ des_encrypt_block(iv, key);
    chunks[i] = iv;
  }

  return Data::join(chunks);
}

Data des_cfb_decrypt(const Data &data, const Data &key) {
  auto chunks = data.chop(64);

  auto iv = default_iv;
  for (size_t i = 0; i < chunks.size(); i++) {
    auto c = des_encrypt_block(iv, key);
    iv = chunks[i];
    chunks[i] = chunks[i] ^ c;
  }

  return Data::join(chunks);
}