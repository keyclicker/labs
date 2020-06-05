#include "sorting.hpp"
#include "Lab1/Database.hpp"
#include "Lab1/Message.hpp"


#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
using namespace std;

int main() {
  random_device rd;
  default_random_engine re(rd());
  uniform_int_distribution<int> rand(0, 10);
  uniform_int_distribution<int> drand(0, 1028);

  //------------------------- Work test ----------------------------------------

  cout << "--------------- Work test ---------------" << endl;
  cout << "100 sorting tests of random generated array (size = 1000):\n"
       << endl;

  int r = 0, c = 0, s = 0, ss = 0;

  for (int j = 0; j < 100; ++j)
  {
    std::vector<int> a;

    for (int i = 0; i < 10; ++i)
      a.emplace_back(drand(re));

    sorting::radix_sort(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) r++;

    a.clear();
    for (int i = 0; i < 1000; ++i)
      a.emplace_back(drand(re));

    sorting::counting_sort(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) c++;

    a.clear();
    for (int i = 0; i < 1000; ++i)
      a.emplace_back(drand(re));

    sorting::std_sort(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) s++;

    a.clear();
    for (int i = 0; i < 1000; ++i)
      a.emplace_back(drand(re));

    sorting::std_stable_sort(a.begin(), a.end());
    if (std::is_sorted(a.begin(), a.end())) ss++;

    a.clear();
    for (int i = 0; i < 1000; ++i)
      a.emplace_back(drand(re));
  }

  cout << "      Radix sort: " << setw(4) << r <<  "  tests passed" << endl;
  cout << "   Counting sort: " << setw(4) << c <<  "  tests passed" << endl;
  cout << "       std::sort: " << setw(4) << s <<  "  tests passed" << endl;
  cout << "std::stable_sort: " << setw(4) << ss << "  tests passed" << endl;


  cout << endl;

  cout << "Creating message database DB1 with 10 random messages" << endl;
  Database<Message> db1 = Database<Message>::Generate(10);

  cout << "Compact printing of DB1:" << endl;
  db1.printCompact();
  cout << endl;

  cout << "Sorting by ID with std::stable_sort ()" << endl;
  db1.std_stable_sortById();

  cout << "Compact printing of DB1:" << endl;
  db1.printCompact();
  cout << endl;

  cout << "Sorting by Type with Counting Sort" << endl;
  db1.std_stable_sortByType();

  cout << "Compact printing of DB1:" << endl;
  db1.printCompact();
  cout << endl;

  cout << "Creating message database DB2 with 10 random messages" << endl;
  Database<Message> db2 = Database<Message>::Generate(10);

  cout << "Compact printing of DB2:" << endl;
  db2.printCompact();
  cout << endl;

  cout << "Sorting by ID (if ID is the same sorting by Type) with std::stable_sort ()" << endl;
  db2.std_stable_sortByType();
  db2.std_stable_sortById();

  cout << "Compact printing of DB2:" << endl;
  db2.printCompact();
  cout << endl;

  cout << "Sorting by Type (if Type is the same sorting by ID) with std::stable_sort ()" << endl;
  db2.std_stable_sortById();
  db2.std_stable_sortByType();

  cout << "Compact printing of DB2:" << endl;
  db2.printCompact();
  cout << endl;


  cout << "Creating message database DB3 with 10 random messages" << endl;
  Database<Message> db3 = Database<Message>::Generate(10);

  cout << "Compact printing of DB3:" << endl;
  db3.printCompact();
  cout << endl;

  cout << "Sorting by ID with Radix Sort" << endl;
  db3.sortById();

  cout << "Compact printing of DB3:" << endl;
  db3.printCompact();
  cout << endl;

  cout << "Sorting by Type with Counting Sort" << endl;
  db3.sortByType();

  cout << "Compact printing of DB3:" << endl;
  db3.printCompact();
  cout << endl;


  cout << "Creating message database DB4 with 10 random messages" << endl;
  Database<Message> db4 = Database<Message>::Generate(10);

  cout << "Compact printing of DB4:" << endl;
  db4.printCompact();
  cout << endl;

  cout << "Sorting by ID with Counting Sort(if ID is the same sorting by Type with Radix Sort)" << endl;
  db4.sortByType();
  db4.sortById();

  cout << "Compact printing of DB4:" << endl;
  db4.printCompact();
  cout << endl;

  cout << "Sorting by Type with Radix Sort (if Type is the same sorting by ID with Counting sort)" << endl;
  db4.sortById();
  db4.sortByType();

  cout << "Compact printing of DB4:" << endl;
  db4.printCompact();
  cout << endl;

}