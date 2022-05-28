#include <iostream>
#include <string>
using namespace std;

#include "Data.hpp"
#include "des.hpp"
#include "kce.hpp"

int main() {

  // Data block("keyclick");

  // Data key = Data("password").sha256().sliceBytes(0, 8);

  // Data key = Data::fromHexString("5b5a57676a56676e");
  // Data block = Data::fromHexString("675a69675e5a6b5a");

  // cout << "block: " << block.toHexString() << endl;
  // cout << "key: " << key.toHexString() << endl;

  // cout << endl;

  // Data encrypted = desEncryptBlock(block, key);

  // cout << "encrypted block: " << encrypted.toHexString() << endl;

  Data key = Data::fromString("password");
  Data block = Data::fromString("I'm trying to use a std::stringstream to buffer data that should get written to a file, but may not be written if errors show up during the creation of the data (the data is generated through user input), and since the data is not guaranteed to be written, I had two ideas, 1. write the data to a temporary file as the data is being created and then move it to the file destination if it is correct or delete it if it is incorrect or 2. store the data on the memory in something like a std::stringstream and then if it ends up being correct just write that onto the std::ofstream. I was wondering if stringstream has a default size limit (and if it does, what it is set to) as to know if it is a feasible idea or if I will run into issues due to a size limit I didn't know of. (Yes, I could also just use an std::string or a C string alternatively I suppose, but I was already using an ofstream before so I wouldn't have to change any of the code by switching to a stringstream)");

  cout << "key: " << key.toString() << endl;
  cout << "key hash: " << key.md5().toHexString() << endl;

  cout << "hex: " << block.toHexString() << endl;
  cout << "text: " << block.toString() << endl;

  Data encrypted = kce(block, key);

  cout << "encrypted hex: " << encrypted.toHexString() << endl;
  cout << "encrypted text: " << encrypted.toString() << endl;

  Data decrypted = kce(encrypted, key);

  cout << "decrypted hex: " << decrypted.toHexString() << endl;
  cout << "decrypted text: " << decrypted.toString() << endl;
}