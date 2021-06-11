#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

template <typename T>
class Heap {
private:
  std::size_t childrenCount;
  vector<T> data;

  void heapifyUp(std::size_t idx) {
    while (idx > 0 && data[idx] > data[getParent(idx)]) {
      std::swap(data[idx], data[getParent(idx)]);
      idx = getParent(idx);
    }
  }

  void heapifyDown(std::size_t idx) {
    while (getChild(idx, 0) < data.size()) {
      std::size_t peak_child = getChild(idx, 0);

      for (int i = 1; i < childrenCount; ++i)
        if (getChild(idx, i) < data.size() &&
            data[getChild(idx, i)] > data[peak_child])
          peak_child = getChild(idx, i);

      if (data[peak_child] > data[idx]) {
        std::swap(data[idx], data[peak_child]);
        idx = peak_child;
      }
      else {
        return;
      }
    }
  }


public:
  explicit Heap(size_t childrenCount): childrenCount(childrenCount) {}

  std::size_t getChild(std::size_t parent, std::size_t child) {
    return parent * childrenCount + 1 + child;
  }

  std::size_t getParent(std::size_t child) {
    return (child - 1) / childrenCount;
  }

  T getMax() {
    return data.front();
  }

  T extractMax() {
    int max = getMax();

    std::swap(data.front(), data.back());
    data.pop_back();
    heapifyDown(0);

    return max;
  }
  оануtemplate <typename FT>
  void insert(FT&& val) {
    data.emplace_back(std::forward<FT>(val));
    heapifyUp(data.size() - 1);
  }

  void increaseKey(size_t idx, const T& value) {
    data[idx] += value;
    if (value >= 0) {
      heapifyUp(idx);
    }
    else {
      heapifyDown(idx);
    }
  }


  friend std::ostream& operator<<(std::ostream& out, const Heap<T> &heap) {
    bool first = true;
    out << "{";
    for (const auto& e : heap.data) {
      if (!first)
        out << ", ";
      else
        first = false;
      out << e;
    }
    return out << "}";
  }

  static void print(std::ostream& out, const Heap<T> &heap) {
    int j = 0;
    for (int i = 0; j < heap.data.size(); ++i) {
      if (i == 0) {
        cout << heap.data[j] << endl;
        j++;
      }
      else {
        for (int k = 0; k < i * heap.childrenCount; ++k) {
          if ((j+k) < heap.data.size())
            cout << heap.data[j+k] << ' ';
          else
            cout << "_ ";
        }
        j += i * heap.childrenCount;
        cout << endl;
      }

    }

  }

};


int main() {
  Heap<int> h(2);


  for (int i = 0; i < 10; ++i) {
    h.insert(rand() % 20);
  }

  cout << h << endl;
  Heap<int>::print(cout, h);
  cout << endl;

  cout << "Extract max: " << h.extractMax() << endl;
  Heap<int>::print(cout, h);
  cout << endl;

  h.increaseKey(0, -1);

  Heap<int>::print(cout, h);
  cout << endl;

  h.increaseKey(0, 20);

  Heap<int>::print(cout, h);
  cout << endl;



  return 0;
}
