#include<iostream>
#include<future>
void func(std::promise<int>& f) {
    f.set_value(1000);
}

int main() {
    std::promise<int> f;
    auto future_result = f.get_future();

    std::thread t1(func, std::ref(f)); // 在线程t1里面，设置了1000，

    t1.join();

    std::cout << future_result.get() << std::endl; // 在主线程中获取这个值

    return 0;
}
