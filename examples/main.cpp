#include "../include/ThreadPool.h"
#include <iostream>
#include <chrono>

int square(int x) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return x * x;
}

int main() {
    ThreadPool pool(4);

    auto f1 = pool.submit(square, 5);
    auto f2 = pool.submit(square, 10);
    auto f3 = pool.submit([]() {
        return std::string("Hello from Thread Pool!");
    });

    std::cout << "5^2 = " << f1.get() << std::endl;
    std::cout << "10^2 = " << f2.get() << std::endl;
    std::cout << f3.get() << std::endl;

    auto f4 = pool.submit([]() {
        throw std::runtime_error("Something went wrong!");
        return 0;
    });

    try {
        f4.get();
    }
    catch(const std::exception &e) {
        std::cout << "Caught Exception: " << e.what() << std::endl;
    }

    return 0;
}