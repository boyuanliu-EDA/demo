// 线程函数中数据未定义错误

#include <iostream>
#include <thread>
#include <memory>

std::thread t;
int a = 1;


void foo(int& x) {  // 引用
    x += 1;
}

void test() {
    //int a = 1;
    t = std::thread(foo,std::ref(a));
}

void test2(int *x) {
    *x += 1;
    std::cout << *x << std::endl;
} 

class A {
    public:
    void foo() {
        std::cout << "hello" << std::endl;
    }
};

class B {
private:
friend void thread_foo();
void foo() {
    std::cout << "hello " << std::endl;
}
};

void thread_foo() {
    std::shared_ptr<B> a = std::make_shared<B>();
    
    std::thread t(&B::foo, a);
    t.join();
}

// int main() {

//     int* ptr = new int(1);
//     std::thread t(test2,ptr);
//     delete ptr;
    
//     //test();
//     // int a = 1;
//     // std::thread t(foo,std::ref(a));


//     t.join();

//     std::cout << a << std::endl;
    
//     return 0;
// }

int main() {
    
    thread_foo();
 

    return 0;

}
