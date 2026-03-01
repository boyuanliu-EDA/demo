#include <iostream>
#include <thread>
#include <string>

void printA() {
    std::cout << "hello world" << std::endl;
    return;
}

void printB(std::string msg) {
    std::cout << msg << std::endl;
    return;
}

int main() {
    // 1 how to create a thread
    std::thread thread1(printB,"hello thread"); // 3 how to pass parameters to funciton
    //thread1.join(); // 2 wait until thread1 finish

    // 4 how to split main-thread and sub-thread : detach()
    // thread1.detach() 

    // 5 joinable
    bool isJoin = thread1.joinable();
    if(isJoin) {
        thread1.join();
    }
    return 0;
}