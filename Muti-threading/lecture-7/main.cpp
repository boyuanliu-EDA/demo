// condition variable 与其使用场景


#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<condition_variable>
#include<queue>

std::mutex mtx;
std::condition_variable con_var;
std::queue<int> g_queue;

void Producer() {
        for (int i = 0; i < 10; i++) {
            std::unique_lock<std::mutex> lock(mtx);
            g_queue.push(i);
            // 如果加任务，要通知消费者取任务
            con_var.notify_one();
            std::cout << "task Producer: " << i << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
}

void Consumer() {
    while (1) {
        std::unique_lock<std::mutex> lock(mtx);
        // 如果队列为空，需要等待
        con_var.wait(lock,[](){return !g_queue.empty();});
        int value =g_queue.front();
        g_queue.pop();

        std::cout << "Consumer" << value << std::endl;
    }
    
}

int main() {
    std::thread  t1(Producer);
    std::thread  t2(Consumer);
    t1.join();
    t2.join();

    return 0;
}





