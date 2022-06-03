#include <iostream>
#include <vector>

#include "des.hpp"
#include "data.hpp"

using namespace std;

int main() {
//  auto block = Data::from_hex("675A69675E5A6B5A");
//  auto key = Data::from_hex("5B5A57676A56676E");
//
//  cout << "block: " << block << endl;
//  cout << "key: " << key << endl;
//  auto enc = des_encrypt_block(block, key);
//  cout << "Cipher Text: " << enc << endl;
//  auto dec = des_decrypt_block(enc, key);
//  cout << "Plain Text: " << dec << endl;

  auto text = Data::from_string("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusomod Hello world tempor.");
  auto key = Data::from_hex("5B5A57676A56676E");

  cout << "text:\n" << text.to_string() << endl;
  cout << "size: " << text.size() << endl;
  cout << "hex:\n" << text << endl;
  cout << "key:\n" << key << "\n\n";

  auto enc = des_cfb_encrypt(text, key);

  cout << "Cipher Text (hex):\n" << enc << "\n\n";

  auto dec = des_cfb_decrypt(enc, key);

  cout << "Plain Text (hex):\n" << dec << endl;
  cout << "Plain Text (string):\n" << dec.to_string() << endl;
}