#include "../include/ThreadPool.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono;

void work()
{
    volatile long long sum = 0;
    for(long long i = 0; i < 2000000; i++)
        sum += i % 7;
}

int main()
{
    const int ROUNDS = 100;
    const int TASKS = 100;

    auto start = high_resolution_clock::now();

    for (int r = 0; r < ROUNDS; r++)
    {
        for (int i = 0; i < TASKS; i++)
            work();
    }

    auto end = high_resolution_clock::now();

    cout << "Sequential: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms\n";

    start = high_resolution_clock::now();

    for (int r = 0; r < ROUNDS; r++)
    {

        vector<thread> threads;

        for (int i = 0; i < TASKS; i++)
            threads.emplace_back(work);

        for (auto &t : threads)
            t.join();
    }

    end = high_resolution_clock::now();

    cout << "Thread per Task: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms\n";

    ThreadPool pool(thread::hardware_concurrency());

    start = high_resolution_clock::now();

    for (int r = 0; r < ROUNDS; r++)
    {

        vector<future<void>> futures;

        for (int i = 0; i < TASKS; i++)
            futures.push_back(pool.submit(work));

        for (auto &f : futures)
            f.get();
    }

    end = high_resolution_clock::now();

    cout << "Thread Pool: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms\n";
}