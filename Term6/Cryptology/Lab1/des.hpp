#pragma once

#include "data.hpp"

Data des_block(const Data &block, const std::vector<Data> &round_keys);

auto get_keys(const Data &keyy);

Data des_encrypt_block(const Data &block, const Data &key);

Data des_decrypt_block(const Data &block, const Data &key);

Data des_cfb_encrypt(const Data &data, const Data &key);

Data des_cfb_decrypt(const Data &data, const Data &key);
