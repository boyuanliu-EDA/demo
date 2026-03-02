// 3互斥量解决多线程数据共享问题

/*
在多个线程中共享数据时，需要注意线程安全问题，
如果多个线程同时访问一个变量，并且其中至少一个线程对该变量进行了写操作
那么就会出现数据竞争问题。数据竞争可能会导致程序崩溃、产生未定义的结果，或者得到错误的结果。
为了避免数据竞争问题，需要使用同步机制来确保多个线程之间对共享数据的访问是安全的。
常见的同步机制包括互斥量，条件变量，原子操作等。
*/

/*
什么叫线程安全：如果多线程程序每一次的运行结果和单线程运行的结果始终
是一样的，那么你的线程就是安全的。
*/

#include <iostream>
#include <thread>
#include <mutex>

int a = 0;

std::mutex mtx;

void fun() {
    for(int i = 0; i < 10000; i++) {
        mtx.lock();
        a += 1;
        mtx.unlock();
    }
}

int main() {
    std::thread t1(fun);
    std::thread t2(fun);

    t1.join();
    t2.join();

    std::cout << a << std::endl;
    return 0;
}