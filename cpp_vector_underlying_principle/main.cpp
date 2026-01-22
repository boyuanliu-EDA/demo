#include <iostream>
#include <vector>
#include <list>
#include <chrono>

class IntVector {
    private:
    int* data;
    int capacity;
    int size;

    public:
    IntVector() {
        capacity = 2;
        size = 0;
        data = new int[capacity]; // alloacte space at heap
        std::cout << "allocate " << capacity << " space, address:" << data << std::endl;
    }

    ~IntVector() {
        std::cout << "release memory"<< std::endl;
        delete[] data;
        data = nullptr; // prevent dangling pointer
    }

    void push_back(int value) {
        std::cout << "\n === push_back( " <<value << " ) ===" << std::endl;

        // check whether need to expend capacity
        if (size == capacity) {
            std::cout << "capacity is full, need to expand capacity" << std::endl; 

            // step1 calc new capacity
            int newCapacity = capacity * 2;
            std::cout << "new capacity:" << newCapacity << std::endl;

            // step2 Apply for a new and larger memory space
            int* newData = new int[newCapacity];
            std::cout << "new address:" << newData << std::endl;

            // step3 copy old data into new memory
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
                std::cout << "copy data[" << i << "] = " << data[i] << "to newData[" << i << "]" << std::endl;
            }

            // step4 release old memory
            std::cout << "release old memory" << std::endl;
            delete[] data;

            //step5 update pointer and capacity
            data = newData;
            capacity = newCapacity;
        } else {
            std::cout << "the capacity is enough, add element directly" << std::endl;
        }

        // add new element to the tail of array
        std::cout << "put " << value << " into data[" << size << "]" << std::endl;
        data[size] = value; // put new value into size
        size++;

        std::cout << "Finish adding, current: size=" << size << ", capacity=" << capacity << std::endl;
    }
};

void demonstrateVector() {
    std::cout << "=== IntVector 工作原理演示 ===\n" << std::endl;
    
    // 1. 创建vector
    std::cout << "1. 创建 IntVector 对象" << std::endl;
    IntVector vec;
    
    // 2. 添加元素（演示扩容）
    std::cout << "\n2. 添加3个元素:" << std::endl;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);  // 第3个会触发扩容
}

int main() {
    demonstrateVector();


    
    std::cout << "\n=== 程序结束，自动调用析构函数 ===" << std::endl;
    // 注意：局部对象vec会在main函数结束时自动调用析构函数
    // 释放动态分配的内存，避免内存泄漏
    
    return 0;
}