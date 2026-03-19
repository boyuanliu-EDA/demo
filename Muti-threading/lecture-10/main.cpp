// 原子操作

// std::atomic 是C++ 标准库中的一个模板类

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

std::atomic<int> shared_data;  // 原子类型自带线程安全，速度更快

void func() {
    for (int i = 0; i < 1000; ++i) {
        shared_data++;
    }
}

int main() {
    std::thread t1(func);
    std::thread t2(func);
    t1.join();
    t2.join();
    std::cout << "shared_data = " << shared_data << std::endl;
    return 0;
}