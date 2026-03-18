// once call
// 单例设计模式是一种常见的设计模式，用于确保某个类只能创建一个实例。由于单例实例是全局唯一的
// 因此在多线程环境中使用单例模式时，需要考虑线程安全问题

#include<iostream>
#include<thread>
#include<mutex>

class Log {
    private:
        static Log* log;
        static std::once_flag once;
    
        Log() = default;
        
        static void init() {
            log = new Log();
        }
    
    public:
        Log(const Log&) = delete;
        Log& operator=(const Log&) = delete;
    
        static Log& GetInstance() {
            std::call_once(once, init);
            return *log;  // 现在安全了，因为 init 完成后 log 一定被初始化
        }
    
        void printLog(const std::string& msg) {
            std::cout << __TIME__ << " " << msg << std::endl;
        }
    };
    
    // 静态成员定义
    Log* Log::log = nullptr;
    std::once_flag Log::once;

void func() {
    Log::GetInstance().printLog("error");
}

int main() {
    std::thread t1(func);
    std::thread t2(func);
    t1.join();
    t2.join();
}