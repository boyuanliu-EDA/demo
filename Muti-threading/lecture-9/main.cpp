// 异步并发 async future packaged—_task promise

// async future
// 是C++引入的一个函数模板，用于异步执行一个函数，并返回一个std::future对象
// 表示异步操作的结果
// 使用std::async可以方便地进行异步编程，避免了手动创建线程和管理线程的麻烦

#include<iostream>
#include<future>

int func() {
    int i = 0;
    for (i = 0; i < 1000; i++) {
       i++;
    }
    return i;
}

int main() {
    std::future<int> future_result = std::async(std::launch::async, func); // 把func给到async的时候，func已经在运行了，其运行结果会被保存到furture_result里
    std::cout << func() << std::endl;

    std::cout << future_result.get() << std::endl; // 在get的时候，async的func没有运行完，get会等待future_result出结果才会继续运行

    return 0;
}