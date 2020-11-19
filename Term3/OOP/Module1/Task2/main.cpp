#include <iostream>
#include <algorithm>
#include <cmath>
#include <list>
using namespace std;

using Int = long long;

Int fac(int val) {
  Int res = 1;
  for (Int i = 1; i <= val; ++i) {
    res *= i;
  }
  return res;
}

list<Int> f(int n) {
  list<Int> res;
  if (n > 0) {
    for (Int k = 2; k < 175; ++k) {
      res.push_back((fac(n)-n*n) % k);
    }
  }
  else if (n < 0) {
    res.push_back((n*n*n*(n+1)) % 274);
  }
  else {
    res = {3, 0, 47};
  }
  return res;
}

list<Int> f(float d) {
  list<Int> res;
  for (Int k = 2; k < 175; ++k) {
    res.push_back(Int(exp(1 / cos(k*d))) % 374);
  }
  return res;
}

list<Int> f(string s) {
  erase_if(s, [](char c) { return (c < '0' || c > '9');});
  list<Int> res;
  for (Int i = 0; i < s.size(); i += 2) {
    Int k = (s[i] - '0') * 10 + (s[i + 1] - '0');
    res.push_back(Int(pow(k,k)) % 574);
  }
  return res;
}

list<Int> f(int a, int b) {
  auto al = f(a);
  auto bl = f(b);

  list<Int> res;
  auto ai = al.begin(), bi = bl.begin();
  for (; ai != al.end(); ++ai, ++bi) {
    for (int j = 0; j < *bi; ++j) {
      res.push_back(*ai);
    }
  }
  return res;
}

list<Int> f(const list<list<Int>> &v) {
  list<Int> res;
  for (auto a : v) {
    for (auto b = a.rbegin(); b != a.rend(); b++) {
      res.push_back(*b);
    }
  }
  return res;
}

template<typename... Args>
list<Int> f(Args... a) {
  return {3, 0, 47};
}

int main() {
    auto a = f(0);
}
