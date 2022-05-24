#include <iostream>
#include <string>
using namespace std;

#include "Data.hpp"
#include "des.hpp"

int main() {

  // Data block("keyclick");

  // Data key = Data("password").sha256().sliceBytes(0, 8);

  Data key = Data::fromHexString("5b5a57676a56676e");
  Data block = Data::fromHexString("675a69675e5a6b5a");

  cout << "block: " << block.toHexString() << endl;
  cout << "key: " << key.toHexString() << endl;

  cout << endl;

  Data encrypted = desEncryptBlock(block, key);

  cout << "encrypted block: " << encrypted.toHexString() << endl;
}