// C++ 跨平台线程池
#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<condition_variable>
#include<queue>
#include<functional>

class ThreadPool {
private:
    std::vector<std::thread> threads;   //线程数组
    std::queue<std::function<void()>> tasks;

    std::mutex mtx;
    std::condition_variable condition;

    bool stop;


public:

    ThreadPool(int numThread):stop(false) {
        for (int i = 0; i < numThread;i++) {
            threads.emplace_back([this]{
                while(1) {
                    std::unique_lock<std::mutex> lock(mtx);
                    condition.wait(lock,[this]{
                        return !tasks.empty() || stop;
                    });

                    if(stop && tasks.empty()) {
                        return;
                    }

                    std::function<void()> task(std::move(tasks.front()));
                    tasks.pop();
                    lock.unlock();
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mtx);
            stop = true;
        }

        condition.notify_all();
        for (auto& t : threads) {
            t.join();
        }
      
    }

    template<class F,class... Args>
    void enqueue(F &&f, Args&&... args) {   //函数模板中两个&是万能引用，如果是左值引用就用左值引用，如果是右值引用就用右值引用。
        std::function<void()> task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

        std::unique_lock<std::mutex> lock(mtx);
        tasks.emplace(std::move(task));
        condition.notify_one();
    }
};


int main() {

    ThreadPool pool(4);

    for (int i = 0; i < 10; i++) {
        pool.enqueue([i]{
            std::cout << "task:" << i <<" is runing" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "task:" << i << " is done" << std::endl;
        });
    }
    return 0;
}