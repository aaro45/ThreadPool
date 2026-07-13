# Thread Pool Library (C++17)

A reusable fixed-size Thread Pool implemented using modern C++17 concurrency primitives.

## Features

- Fixed-size worker thread pool
- Thread-safe task queue
- Generic `submit()` API
- Supports arbitrary callable objects
- `std::future` based asynchronous result retrieval
- Exception propagation through futures
- Graceful shutdown using RAII
- Benchmark comparing:
  - Sequential execution
  - Thread-per-task
  - Thread Pool execution

---

## Project Structure

```
ThreadPool/
│
├── include/
│   └── ThreadPool.h
│
├── src/
│   └── ThreadPool.cpp
│
├── examples/
│   └── main.cpp
│
├── benchmark/
│   └── benchmark.cpp
│
├── CMakeLists.txt
└── README.md
```

---

## Usage

```cpp
ThreadPool pool(4);

auto future = pool.submit([] {
    return 42;
});

std::cout << future.get() << std::endl;
```

---

## Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

---

## Benchmark

The benchmark compares:

- Sequential execution
- Thread-per-task execution
- Thread Pool execution

to demonstrate task scheduling using a reusable worker pool.

---

## Technologies

- C++17
- std::thread
- std::future
- std::packaged_task
- std::condition_variable
- std::mutex
- STL