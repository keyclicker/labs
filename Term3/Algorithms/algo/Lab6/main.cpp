#include <iostream>
#include <string>
using namespace std;

uint64_t modPow(uint64_t num, uint64_t pow, uint64_t mod) {
  if (num == 0) return 0;
  if (pow == 0) return 1;

  uint64_t y;
  if (pow % 2 == 0) {
    y = modPow(num, pow / 2, mod);
    y = (y * y) % mod;
  }
  else {
    y = num % mod;
    y = (y * modPow(num, pow - 1, mod) % mod) % mod;
  }

  return (y + mod) % mod;
}

constexpr uint64_t P = 256;
constexpr uint64_t Mod = UINT64_MAX / 2;

uint64_t hashString(const string &str) {
  uint64_t res = 0;
  for (long i = 0; i < str.size(); ++i) {
    res += (uint64_t(str[i]) * modPow(P, str.size() - i - 1, Mod)) % Mod;
  }
  return res % Mod;
}

uint64_t rollHash(uint64_t hash, size_t roll, const string &str) {
  if (!(roll % str.size())) return hash;
  return (((((hash - uint64_t(str[(roll-1) % str.size()]) * modPow(P, str.size()-1, Mod))
          % Mod) * P) % Mod) + uint64_t(str[(roll-1) % str.size()])) % Mod;
}
рара
string rollString(const string &str, int roll) {
  string res;
  res.resize(str.size());

  for (int i = 0; i < str.size(); ++i) {
    res[i] = str[(i + roll) % str.size()];
  }
  return res;
}

bool isRolled(const string &a, const string &b) {
  if (a.size() != b.size())
    return false;

  if (a.empty() && b.empty())
    return true;

  auto ah = hashString(a);
  auto bh = hashString(b);

  for (int i = 1; i < a.size(); ++i) {
    if (ah == bh)
      return true;
    bh = rollHash(bh, i, b);
  }

  if (ah == bh)
    return true;
  else
    return false;
}

int main() {
  srand(time(NULL));

  string str = "Hello World";

  //cout << isRolled(str, rollString(str, rand())) << endl;
  //cout << isRolled(str, "World Hello") << endl;

  int rc = 0, ac = 0;

  for (int i = 0; i < 5000; ++i) {
    auto size = 2 + rand() % 50;

    string str;
    str.resize(size);
    for (int j = 0; j < size; ++j) {
      str[j] = 'A' + rand() % ('z' - 'A');
    }

    cout << "Size: " << size << endl;
    cout << "Random string: " << str << endl;

    auto rstr = rollString(str, rand());
    cout << "Rolled string: " << rstr << endl;

    string astr;
    astr.resize(size);
    for (int j = 0; j < size; ++j) {
      astr[j] = 'A' + rand() % ('z' - 'A');
    }
    cout << "Another string: " << astr << endl;

    auto irr = isRolled(str, rstr);
    auto iar = isRolled(str, astr);
    if (irr) rc++;
    if (iar) ac++;

    cout << "Is rolled str rolled: " << irr << endl;
    cout << "Is another str rolled: " << iar << endl;

    cout << endl;
  }

  cout << endl;
  cout << "Rolled count: " << rc << endl;
  cout << "Another count: " << ac << endl;

  return 0;
}
