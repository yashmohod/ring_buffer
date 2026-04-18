# Ring Buffer

A fixed-size circular queue in C++ that works for any type. When the buffer is
full, pushing a new element overwrites the oldest one — no dynamic allocation,
no resizing, O(1) push always.

## C++ Concepts Used

- `template<typename T, size_t N>` — non-type template parameter for compile-time fixed size
- Stack-allocated array `T data_[N]` — no heap, no destructor needed
- Circular index arithmetic — `(head_ + i) % N` instead of shifting elements
- `static_assert` + `std::is_arithmetic` — `mean()` only compiles for numeric types
- `operator[]` with head offset — correct element access after wraparound

## Usage

```cpp
RingBuffer<double, 5> buf;
buf.push(1.0);
buf.push(2.0);
buf.push(3.0);

buf.size();   // 3
buf.full();   // false
buf[0];       // 1.0 (oldest)

// Fill and overflow — oldest gets overwritten
buf.push(4.0);
buf.push(5.0);
buf.push(6.0);
buf[0];       // 2.0

buf.mean();   // 4.0

// Range-for
for (auto x : buf) std::cout << x << " ";  // 2 3 4 5 6
```

## Building & Running Tests

```bash
g++ -o tests_rb tests/test_ring_buffer.cpp
./tests_rb
```

## Project Ladder Context

This is Project 3 of a C++ learning ladder built toward quantitative systems
development. Ring buffers are used in low-latency financial systems to store
the last N price ticks. Project 4 (Expression Tree) introduces smart pointers
and move semantics.
