# Module 09: STL Containers

## What C++ Adds: Standard Template Library

**C has**: Nothing (roll your own or use third-party libraries)
**C++ adds**: Production-ready, template-based containers and algorithms

## Key Concept

Don't reimplement common data structures - use STL:

```cpp
#include <vector>
#include <map>
#include <string>

std::vector<int> numbers = {1, 2, 3, 4, 5};
std::map<std::string, int> ages = {{"Alice", 30}, {"Bob", 25}};
```

## Sequence Containers

### vector - Dynamic Array
```cpp
#include <vector>

std::vector<int> vec;        // Empty vector
std::vector<int> vec2(10);   // 10 elements (default-initialized)
std::vector<int> vec3(10, 5);  // 10 elements, all value 5
std::vector<int> vec4 = {1, 2, 3};  // Initializer list

vec.push_back(42);           // Add to end: O(1) amortized
vec.pop_back();              // Remove from end: O(1)
vec[0] = 10;                 // Access: O(1)
vec.size();                  // Number of elements
vec.empty();                 // Check if empty
vec.clear();                 // Remove all elements

// Iteration
for (int x : vec) {          // Range-based for
    std::cout << x << " ";
}

for (auto it = vec.begin(); it != vec.end(); ++it) {  // Iterator
    std::cout << *it << " ";
}
```

**When to use**: Default choice, random access needed, order matters

### list - Doubly Linked List  
```cpp
#include <list>

std::list<int> lst = {1, 2, 3};
lst.push_front(0);           // Add to front: O(1)
lst.push_back(4);            // Add to back: O(1)
lst.pop_front();             // Remove from front: O(1)

// No random access (no operator[])
// lst[0];  // ERROR
```

**When to use**: Frequent insertions/deletions in middle, no random access needed

### deque - Double-Ended Queue
```cpp
#include <deque>

std::deque<int> dq = {1, 2, 3};
dq.push_front(0);            // Efficient push to front
dq.push_back(4);             // Efficient push to back
dq[0] = 10;                  // Random access (slightly slower than vector)
```

**When to use**: Need to add/remove from both ends efficiently

### array - Fixed-Size Array (C++11)
```cpp
#include <array>

std::array<int, 5> arr = {1, 2, 3, 4, 5};  // Size fixed at compile-time
arr[0] = 10;                 // Random access
arr.size();                  // Returns 5

// Unlike C arrays, knows its size!
```

**When to use**: Fixed size known at compile time, want STL interface

## Associative Containers

### map - Ordered Key-Value Pairs
```cpp
#include <map>

std::map<std::string, int> ages;
ages["Alice"] = 30;          // Insert/update
ages["Bob"] = 25;
ages.insert({"Charlie", 35});

// Access
int age = ages["Alice"];     // Returns 30
int x = ages["Dave"];        // Creates entry with default value (0)!

// Safe access
if (ages.count("Alice")) {   // Check existence
    int age = ages["Alice"];
}

// Iteration (sorted by key)
for (const auto& [name, age] : ages) {  // C++17 structured binding
    std::cout << name << ": " << age << std::endl;
}
```

**When to use**: Need key-value pairs, want sorted order

### unordered_map - Hash Table (C++11)
```cpp
#include <unordered_map>

std::unordered_map<std::string, int> umap;
umap["Alice"] = 30;          // Average O(1) insert/access
umap["Bob"] = 25;

// Same interface as map, but unsorted and faster
```

**When to use**: Need key-value pairs, don't need sorting, want O(1) access

### set - Ordered Unique Elements
```cpp
#include <set>

std::set<int> s = {3, 1, 4, 1, 5};   // Automatically sorted, duplicates removed
// s contains: {1, 3, 4, 5}

s.insert(2);                 // Insert: O(log n)
s.erase(4);                  // Remove: O(log n)
bool found = s.count(3);     // Check existence: O(log n)

for (int x : s) {            // Iteration in sorted order
    std::cout << x << " ";
}
```

**When to use**: Need unique elements, want sorted order

### unordered_set - Hash Set (C++11)
```cpp
#include <unordered_set>

std::unordered_set<int> us = {3, 1, 4, 1, 5};
us.insert(2);                // Average O(1)
bool found = us.count(3);    // Average O(1)
```

**When to use**: Need unique elements, don't need sorting, want O(1) access

## Container Adaptors

### stack - LIFO
```cpp
#include <stack>

std::stack<int> stk;
stk.push(1);                 // Push
stk.push(2);
int top = stk.top();         // Access top (2)
stk.pop();                   // Remove top (doesn't return value!)
bool empty = stk.empty();
```

### queue - FIFO
```cpp
#include <queue>

std::queue<int> q;
q.push(1);                   // Enqueue
q.push(2);
int front = q.front();       // Access front (1)
q.pop();                     // Dequeue
```

### priority_queue - Max Heap
```cpp
#include <queue>

std::priority_queue<int> pq;
pq.push(3);
pq.push(1);
pq.push(4);
int max = pq.top();          // Returns 4 (largest)
pq.pop();                    // Removes 4
```

## Iterators

**Key abstraction**: Unified interface for containers

```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};

// Forward iteration
for (auto it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it << " ";
}

// Reverse iteration
for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
    std::cout << *it << " ";
}

// Const iterators (read-only)
for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
    // *it = 10;  // ERROR: can't modify through const iterator
}
```

## Algorithms

```cpp
#include <algorithm>
#include <numeric>

std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};

// Sort
std::sort(vec.begin(), vec.end());  // {1, 1, 2, 3, 4, 5, 6, 9}

// Find
auto it = std::find(vec.begin(), vec.end(), 5);
if (it != vec.end()) {
    std::cout << "Found at position " << (it - vec.begin()) << std::endl;
}

// Count
int count = std::count(vec.begin(), vec.end(), 1);  // 2

// Sum
int sum = std::accumulate(vec.begin(), vec.end(), 0);

// Remove duplicates
std::sort(vec.begin(), vec.end());
auto last = std::unique(vec.begin(), vec.end());
vec.erase(last, vec.end());

// Transform
std::vector<int> doubled(vec.size());
std::transform(vec.begin(), vec.end(), doubled.begin(),
               [](int x) { return x * 2; });

// Any/All/None
bool hasOdd = std::any_of(vec.begin(), vec.end(),
                          [](int x) { return x % 2 == 1; });

// Min/Max element
auto minIt = std::min_element(vec.begin(), vec.end());
auto maxIt = std::max_element(vec.begin(), vec.end());
```

## Comparison with C

| Feature | C | C++ STL |
|---------|---|---------|
| **Dynamic array** | Manual realloc | vector<T> |
| **Hash table** | Third-party or custom | unordered_map<K, V> |
| **Linked list** | Manual implementation | list<T> |
| **Binary tree** | Manual implementation | map<K, V>, set<T> |
| **Algorithms** | Write your own | sort, find, etc. |
| **Memory management** | Manual | Automatic (RAII) |

## Container Choice Flowchart

1. **Need key-value pairs?**
   - Yes: `map` (sorted) or `unordered_map` (faster)
   - No: Continue

2. **Need unique elements only?**
   - Yes: `set` (sorted) or `unordered_set` (faster)
   - No: Continue

3. **Need to add/remove from both ends?**
   - Yes: `deque`
   - No: Continue

4. **Need frequent middle insertion/deletion?**
   - Yes: `list`
   - No: `vector` (default choice)

## Performance Comparison

| Container | Access | Insert (end) | Insert (middle) | Find |
|-----------|--------|--------------|-----------------|------|
| vector | O(1) | O(1) amortized | O(n) | O(n) |
| list | O(n) | O(1) | O(1)* | O(n) |
| deque | O(1) | O(1) | O(n) | O(n) |
| map | O(log n) | - | O(log n) | O(log n) |
| unordered_map | O(1) avg | - | O(1) avg | O(1) avg |
| set | O(log n) | - | O(log n) | O(log n) |

*If you have an iterator to the position

## Best Practices1. **Default to vector** unless you have specific needs
2. **Use unordered_map/set** for large datasets (better performance)
3. **Use range-based for** when you don't need the index
4. **Reserve capacity** for vector if you know size: `vec.reserve(1000);`
5. **Use const references** in range-based for: `for (const auto& elem : vec)`

## Next Module

**10_smart_pointers**: Automatic memory management with RAII.
