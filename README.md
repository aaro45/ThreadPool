# Thread Pool Library (C++17)

A reusable fixed-size **Thread Pool** implementation in modern **C++17** built using the Standard Library concurrency primitives. The library provides an efficient way to execute asynchronous tasks by reusing a fixed number of worker threads instead of creating a new thread for every task.

---

## Features

- Fixed-size worker thread pool
- Thread-safe task queue
- Generic templated `submit()` API
- Supports arbitrary callable objects (functions, lambdas, functors)
- Asynchronous task execution using `std::future`
- Return value support through `std::packaged_task`
- Exception propagation from worker threads
- Graceful shutdown using RAII
- Thread-safe synchronization using mutexes and condition variables
- Benchmark comparing:
  - Sequential execution
  - Thread-per-task execution
  - Thread Pool execution

---

## Project Structure

```
ThreadPool/
│
├── benchmark/
│   └── benchmark.cpp
│
├── examples/
│   └── main.cpp
│
├── include/
│   └── ThreadPool.h
│
├── src/
│   └── ThreadPool.cpp
│
├── tests/
│   └── threadpool_test.cpp
│
├── CMakeLists.txt
├── README.md
├── LICENSE
└── .gitignore
```

---

## Architecture

```
                    submit()

                        │
                        ▼

              +------------------+
              |   Task Queue     |
              |  (Thread Safe)   |
              +------------------+
                        │
                        ▼
          +------+------+------+------+
          |             |             |
          ▼             ▼             ▼
      Worker 1      Worker 2      Worker N
          │             │             │
          └─────────────┼─────────────┘
                        │
                        ▼
                 Execute Task
                        │
                        ▼
              std::future returned
```

---

## Technologies Used

- C++17
- STL
- `std::thread`
- `std::mutex`
- `std::condition_variable`
- `std::future`
- `std::packaged_task`
- `std::queue`
- `std::function`

---

## Usage

```cpp
#include "ThreadPool.h"
#include <iostream>

int main() {

    ThreadPool pool(4);

    auto future = pool.submit([]() {
        return 42;
    });

    std::cout << future.get() << std::endl;
}
```

Output

```
42
```

---

## Building

### Using CMake

```bash
mkdir build
cd build

cmake ..

cmake --build .
```

### Using g++

Example

```bash
g++ -std=c++17 examples/main.cpp src/ThreadPool.cpp -Iinclude -pthread -o main
```

Benchmark

```bash
g++ -std=c++17 benchmark/benchmark.cpp src/ThreadPool.cpp -Iinclude -pthread -o benchmark
```

---

## Benchmark

The benchmark compares three execution models.

1. Sequential execution
2. Thread-per-task execution
3. Thread Pool execution

Example benchmark results

| Execution Model | Time |
|-----------------|------|
| Sequential | ~4422 ms |
| Thread per Task | ~575 ms |
| Thread Pool | ~570 ms |

> **Note:** For CPU-bound workloads, computation dominates the runtime, so thread creation overhead becomes relatively small. The primary advantage of a thread pool is the reuse of worker threads, reducing repeated thread creation and providing a scalable task execution model for applications that continuously submit tasks.

---

## Design Decisions

### Why a Thread Pool?

Creating a new operating system thread for every task introduces overhead due to:

- Thread creation
- Context switching
- Scheduling
- Thread destruction

A thread pool avoids this by maintaining a fixed number of worker threads that continuously process tasks from a shared queue.

---

### Synchronization

The implementation uses:

- `std::mutex` for protecting shared resources.
- `std::condition_variable` to suspend worker threads when the queue is empty.
- `std::unique_lock` for condition-variable waiting.
- `std::lock_guard` for lightweight locking where waiting is not required.

---

### Exception Handling

Exceptions thrown inside worker threads are automatically propagated to the calling thread using:

- `std::packaged_task`
- `std::future`

This allows users to safely retrieve results without manually handling thread synchronization.

---

## Future Improvements

Possible extensions include:

- Dynamic thread pool resizing
- Priority task scheduling
- Work stealing scheduler
- Lock-free task queue
- Task cancellation
- Timed task scheduling
- Performance metrics
- Custom thread affinity

---

## Learning Outcomes

This project provided hands-on experience with:

- Multithreading in C++17
- Producer–consumer architecture
- Synchronization primitives
- RAII-based resource management
- Template programming
- Asynchronous programming
- Thread-safe data structures
- Performance benchmarking

---

## License

This project is licensed under the MIT License.