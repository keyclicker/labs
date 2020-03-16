# Reference
```
template<typename T, size_t sz> Array;
template<typename T> List;
template<typename T> Vector;
```

### Array, Vector, List

- **size()** - Return size
- **operator[]** - access specified element 
- **at()**  - access specified element with bounds checking 
- **front()** - access the first element 
- **back()** - access the last element
- **begin()** - returns an iterator to the beginning 
- **end()** - returns an iterator to the beginning
- **print()** - prints elements with **cout <<**
- **operator<<** - overloaded operator for **std::ostream**

### List, Vector

- **push_front()** - inserts an element to the beginning
- **push_back()** - adds an element to the end
- **pop_front()** - removes the first element
- **pop_back()** - removes the last element
- **insert()** - inserts element
- **erase()** - erases elements
- **clear()** - clears the contents 

### Vector

- **capacity()** - returns the number of elements that can be held in currently allocated storage 
- **resize()** - changes the number of elements stored 
- **reserve()** - reserves storage

# Features
- **iinitializer_list** initialization
```
Vector<int> vec = {1, 2, 3, 4};
```

- Range-based loops
```
for (auto a : vec);
```

- Overloaded << operator for **std::ostream**
```
cout << vec;
>>> {1, 2, 3, 4}
```

- **std::sort** and other STL algorithms support
```
std::sort(vec.begin(), vec.end());
```

# Benchmarks
- To run benchmark choose **bench** target in your IDLE
- Pre-done benchmarks of **stl** and my containers with graphic visualisation located in **Benchmarks** directory
<div style="display: grid;">
<img src="https://github.com/keyclicker/labs/blob/master/semester2/Lab2/A/Benchmarks/PushBack.png?raw=true" width="280">
<img src="https://github.com/keyclicker/labs/blob/master/semester2/Lab2/A/Benchmarks/PushFront.png?raw=true" width="280">
<img src="https://github.com/keyclicker/labs/blob/master/semester2/Lab2/A/Benchmarks/InsertBegin.png?raw=true" width="280">
<img src="https://github.com/keyclicker/labs/blob/master/semester2/Lab2/A/Benchmarks/InitWithValue.png?raw=true" width="280">
<img src="https://github.com/keyclicker/labs/blob/master/semester2/Lab2/A/Benchmarks/ForRange.png?raw=true" width="280">
<img src="https://github.com/keyclicker/labs/blob/master/semester2/Lab2/A/Benchmarks/EraseBegin.png?raw=true" width="280">
</div>

# Interactive mode
```
create <name> -<type>              Create list, <type> = {-list, -vector}
del <name>                         Delete list
len <name>                         Get size of list
print <name>                       Print list
ls                                 List lists
append <name> <IPs>                Append IPs
insert <name> <index> <IPs>        Insert IPs
remove <name> <index>              Remove IP by index
get <name> <index>                 Get IP by index
set <name> <index> <IP>            Set IP by index
help                               Run help
demo                               Run demo
```

# Demo mode
- To run demo mode use command **demo** in interactive mode
