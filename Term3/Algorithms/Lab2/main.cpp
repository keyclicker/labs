#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
using namespace std;

template <typename T>
int partition(T &a, T &b, int beg, int end) {
  int pivot = (beg + end) / 2;
  int current = beg - 1;
  int shadow = -1;

  for (int i = beg; i <= end; ++i) {
    if (a[i] < b[pivot])
      std::swap(a[++current], a[i]);

    if (a[i] == b[pivot])
      shadow = i;
  }

  std::swap(a[current + 1], a[shadow]);
  std::swap(b[current + 1], b[pivot]);

  pivot = current + 1;
  current = beg - 1;

  for (int i = beg; i <= end; ++i)
    if (b[i] < a[pivot])
      std::swap(b[++current], b[i]);

  return current + 1;
}

template <typename T>
void sort(T &a, T &b, size_t beg, size_t end) {
  if (beg >= end)
    return;

  int pivot = partition(a, b, beg, end);

  sort(a, b, beg, pivot - 1);
  sort(a, b, pivot + 1, end);
}


int main() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(0, 100);

  int n;
  cin >> n;

  vector<int> nuts(n), bolts(n);
  for (int i = 0; i < n; ++i) {
    int rnd = dist(mt);
    nuts[i] = rnd;
    bolts[i] = rnd;
  }

  shuffle(nuts.begin(), nuts.end(), mt);


  for (auto a : nuts) {
    cout << a << ' ';
  }
  cout << endl;

  for (auto b : bolts) {
    cout << b << ' ';
  }
  cout << endl;

  sort(nuts, bolts, 0, n);

  for (int i = 0; i < n; ++i) {
    cout << '(' << nuts[i] << ", " << bolts[i] << ")" << endl;
  }

}
