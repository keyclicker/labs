#include "sorting.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <thread>
#include <future>
using namespace std;

int main() {
  random_device rd;
  default_random_engine re(rd());
  uniform_real_distribution<double> drand(-100, 100);
  uniform_int_distribution<int> rand(0, 100);


  //------------------------- Work test ----------------------------------------

  cout << "--------------- Work test ---------------" << endl;
  cout << "100 sorting tests of random generated array (size = 1000):\n" << endl;

  int aq = 0, q = 0, am = 0, m = 0, t = 0, at = 0;

  for (int j = 0; j < 100; ++j) {
    std::vector<double> a;

    for (int i = 0; i < 1000; ++i)
      a.emplace_back(drand(re));

    sorting::quicksort(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) q++;

    a.clear();
    for (int i = 0; i < 1000; ++i)
      a.emplace_back(drand(re));

    sorting::quicksort_async(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) aq++;

    a.clear();
    for (int i = 0; i < 1000; ++i)
      a.emplace_back(drand(re));

    sorting::merge(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) m++;

    a.clear();
    for (int i = 0; i < 1000; ++i)
      a.emplace_back(drand(re));

    sorting::merge_async(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) am++;

    a.clear();
    for (int i = 0; i < 1000; ++i)
      a.emplace_back(drand(re));

    sorting::timsort(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) t++;
  }

  cout << "Async Quicksort: " << setw(4) << aq << "  tests passed" << endl;
  cout << "Quicksort: " << setw(4) << q << "  tests passed" << endl;
  cout << "Async Merge Sort: " << setw(4) << am << "  tests passed" << endl;
  cout << "Merge Sort: " << setw(4) << m << "  tests passed" << endl;
  cout << "Tim Sort: " << setw(4) << t << "  tests passed" << endl;

  cout << endl;

  cout << "----------------- Demo -----------------" << endl;
  cout << "Generating random array A with 20 integer values\n" << endl;

  std::vector<int> A;

  for (int i = 0; i < 20; ++i)
    A.emplace_back(rand(re));

  cout << "              A = {";
  for (auto a : A) {
    cout << setw(3) << a;
  }
  cout << " }\n" << endl;

  cout << "Async Quicksort:  {";

  auto B = A;
  sorting::quicksort_async(B.begin(), B.end());
  for (auto a : B) {
    cout << setw(3) << a;
  }
  cout << " }\n" << endl;

  cout << "Async Merge Sort: {";

  B = A;
  sorting::merge_async(B.begin(), B.end());
  for (auto a : B) {
    cout << setw(3) << a;
  }
  cout << " }\n" << endl;

  cout << "Tim Sort:         {";

  B = A;
  sorting::timsort(B.begin(), B.end());
  for (auto a : B) {
    cout << setw(3) << a;
  }
  cout << " }\n" << endl;

  return 0;
}