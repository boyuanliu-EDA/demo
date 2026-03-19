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
    
    std::packaged_task<int()> task(func); // 包裹成了packaged_task但是没有在后台运行

    auto future_result = task.get_future();

    // 手动开辟线程
    std::thread t1(std::move(task)); //子线程
    std::cout << func() << std::endl; //主线程

    t1.join();
    std::cout << future_result.get() << std::endl; // 在get的时候，async的func没有运行完，get会等待future_result出结果才会继续运行

    return 0;
}