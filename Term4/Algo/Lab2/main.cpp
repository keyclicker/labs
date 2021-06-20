#include <iostream>
#include <string>
using namespace std;

#include "SplayTree.hpp"


int main() {
  SplayTree<int, std::string> st;

  st.insert(65, "Beatles");
  st.insert(67, "The Doors");
  st.insert(11, "Cream");
  st.insert(1, "Jimmy Hendrix");
  st.insert(27, "Jim Morrison");
  st.insert(15, "Love");

  st.print();
  cout << endl;

  cout << "67 - " << st[67] << endl;
  cout << "11 - " << st[11] << endl;
  cout << endl;

  st[11] = "Queen";
  cout << "st[11] = \"Queen\"" << endl;
  cout << "11 - " << st[11] << endl;
  cout << endl;


  st.del(11);
  cout << "st.del(11)" << endl;
  cout << endl;

  st.print();


  return 0;
}