#include <iostream>
#include <memory>
#include <list>
using namespace std;

int S = 0;

class Base {
protected:
  list<shared_ptr<Base>> objects;
  int N;

  virtual void change(int &S) = 0;
  void baseChange(int &S) {
    S = 2*S - N + 32;
  }
public:
  const list<shared_ptr<Base>> &getObjects() const {
    return objects;
  }
  list<shared_ptr<Base>> &getObjects() {
    return objects;
  }
  int getN() {
    return N;
  }
  virtual ~Base() {
    baseChange(S);
  }
  friend int fun(const list<shared_ptr<Base>> &ls, int &s);
};

class Alpha : public Base {
protected:
  static int counter;
  void change(int &S) override {
    S = S - N + 4;
  }
public:
  Alpha() {
    N = counter++;
  }
  ~Alpha() {
    change(S);
  }
};

class Beta : public Base {
protected:
  static int counter;
  void change(int &S) override {
    S = S + N;
  }
public:
  Beta() {
    N = counter++;
  }
  ~Beta() {
    change(S);
  }
};

class Gamma : public Base {
protected:
  static int counter;
  void change(int &S) override {
    S = S + 3 * N - 32;
  }
public:
  Gamma() {
    N = counter++;
  }
  ~Gamma() {
    change(S);
  }
};

int Alpha::counter = 1;
int Beta::counter = 1;
int Gamma::counter = 1;

int fun(const list<shared_ptr<Base>> &ls, int &s) {
  for (auto a : ls) {
    a->change(s);
    a->baseChange(s);
    fun(a->getObjects(), s);
  }
}

int fun(const list<shared_ptr<Base>> &ls) {
  int s = S;
  fun(ls, s);
  return s;
}

void allCombos() {

}

int main() {
  //Task 1 (сорі за такі блоки)
  cout << S << endl;
  {
    Alpha a1, a2;
    cout << a1.getN() << ' ' << a2.getN() << endl;
  }
  cout << S << endl;
  {
    Beta b1, b2;
    cout << b1.getN() << ' ' << b2.getN() << endl;
  }
  cout << S << endl;
  {
    Gamma g1, g2;
    cout << g1.getN() << ' ' << g2.getN() << endl;
  }
  cout << S << endl;
  cout << endl;

  //Task 2
  S = 0;
  cout << S << endl;

  auto b = make_shared<Beta>();
  b->getObjects().emplace_back(make_shared<Gamma>());
  b->getObjects().emplace_back(make_shared<Gamma>());

  list<shared_ptr<Base>> lis = {make_shared<Alpha>(), make_shared<Alpha>(),
                                make_shared<Beta>(), move(b)};

  cout << fun(lis) << endl;
  lis.clear();
  cout << S << endl;
}
