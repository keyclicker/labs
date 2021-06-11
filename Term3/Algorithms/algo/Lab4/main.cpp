#include <iostream>
#include <vector>
#include <list>
using namespace std;

template<typename T>
struct Record {
  int8_t key;
  T value;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const vector<Record<T>> &vec) {
  for (auto &a : vec)
    out << int(a.key) << ": " << a.value << endl;

  return out;
}

//1,2 - O(n) + Stable
template<typename T>
void countingSort(vector<Record<T>> &vec) {
  list<T> ls[2];
  for (auto &a: vec)
    ls[a.key].push_back(a.value);

  vec.clear();
  for (auto &a: ls[0])
    vec.push_back(Record<T>{0, a});
  for (auto &a: ls[1])
    vec.push_back(Record<T>{1, a});
}

//1,3 - O(n) + No additional memory
template<typename T>
void hoareSort(vector<Record<T>> &vec) {
  int i = 0;
  int j = vec.size() - 1;

  while (true) {
    while (vec[i].key == 0) ++i;
    while (vec[j].key == 1) --j;

    if (i >= j) break;

    swap(vec[i], vec[j]);
  }
}

//2,3 - Stable + No additional memory
template<typename T>
void insertionSort(vector<Record<T>> &vec) {
  for (int i = 0; i < vec.size(); ++i) {
    auto key = vec[i];
    auto j = i - 1;

    while (j >= 0 && vec[j].key > key.key) {
      vec[j + 1] = vec[j];
      j = j - 1;
    }
    vec[j + 1] = key;
  }
}


int main() {
  vector<Record<int>> recs;

  srand (time(NULL));
  for (int i = 0; i < 5; ++i) {
    recs.push_back(Record<int>{int8_t(rand() % 2), rand() % 50});
  }

  cout << recs << endl;

  auto cs = recs;
  countingSort(cs);

  cout << "Counting sort:\n" << cs << endl;

  auto is = recs;
  insertionSort(is);

  cout << "Insertion Sort:\n" << is << endl;

  auto hs = recs;
  hoareSort(hs);

  cout << "Hoare Sort:\n" << hs << endl;
  return 0;
}
