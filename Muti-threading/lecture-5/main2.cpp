#include<iostream>
#include<thread>
#include<mutex>

int shared_data = 0;

std::timed_mutex mtx;

void func() {
    for (int i = 0; i < 2; ++i) {
        std::unique_lock<std::timed_mutex> lg(mtx,std::defer_lock); // no lock , the consturction function is empty
        //std::unique_lock<std::mutex> lg(mtx,std::defer_lock);

        // how to lock with delay
        if(lg.try_lock_for(std::chrono::seconds(2))){
            std::this_thread::sleep_for(std::chrono::seconds(1));
            shared_data++;
        }
       
    }
}

int main() {
    std::thread t1(func);
    std::thread t2(func);
    t1.join();
    t2.join();

    std::cout << shared_data << std::endl;
    return 0;
}