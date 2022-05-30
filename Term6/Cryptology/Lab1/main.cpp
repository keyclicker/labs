#include <iostream>
#include <string>
using namespace std;

#include "Data.hpp"
#include "des.hpp"

int main() {
  // auto block = Data::fromHexString("675a69675e5a6b5a");
  // auto key = Data::fromHexString("5b5a57676a56676e");
  auto block = Data::fromHexString("123456ABCD132536");
  auto key = Data::fromHexString("AABB09182736CCDD");


  cout << "str: " << block.toString() << endl;

  Data encrypted = desBlock(block, key);
  // Data decrypted = desBlock(encrypted, key);
}