#include <iostream>
#include <unordered_set>
#include <chrono>
#include <algorithm>

int main() {
    // 创建包含16万个整数的unordered_set
    std::unordered_set<int> data_set;
    const int DATA_SIZE = 160000;
    
    for (int i = 0; i < DATA_SIZE; ++i) {
        data_set.insert(i);
    }
    
    std::cout << "数据集大小: " << data_set.size() << std::endl;
    
    // 查找存在的元素（前1000个）
    const int TEST_COUNT = 1000;
    
    // 测试1: 使用unordered_set自己的find方法（哈希查找）
    auto start1 = std::chrono::high_resolution_clock::now();
    int found1 = 0;
    
    for (int i = 0; i < TEST_COUNT; ++i) {
        if (data_set.find(i) != data_set.end()) {
            found1++;
        }
    }
    
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1);
    
    std::cout << "\n=== 测试1: 使用 unordered_set.find() ===" << std::endl;
    std::cout << "找到的元素: " << found1 << "/" << TEST_COUNT << std::endl;
    std::cout << "总耗时: " << duration1.count() << " 纳秒" << std::endl;
    std::cout << "平均每次查找: " << duration1.count() / TEST_COUNT << " 纳秒" << std::endl;
    
    // 测试2: 使用std::find（线性查找）
    auto start2 = std::chrono::high_resolution_clock::now();
    int found2 = 0;
    
    for (int i = 0; i < TEST_COUNT; ++i) {
        if (std::find(data_set.begin(), data_set.end(), i) != data_set.end()) {
            found2++;
        }
    }
    
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);
    
    std::cout << "\n=== 测试2: 使用 std::find() ===" << std::endl;
    std::cout << "找到的元素: " << found2 << "/" << TEST_COUNT << std::endl;
    std::cout << "总耗时: " << duration2.count() << " 纳秒" << std::endl;
    std::cout << "平均每次查找: " << duration2.count() / TEST_COUNT << " 纳秒" << std::endl;
    
    // 性能对比
    std::cout << "\n=== 性能对比 ===" << std::endl;
    std::cout << "std::find() 比 unordered_set.find() 慢 " 
              << (double)duration2.count() / duration1.count() << " 倍" << std::endl;
    
    return 0;
}