#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <functional>

// 模拟一个简单的哈希表
class SimpleHashSet {
private:
    std::vector<std::list<int>> buckets;
    int bucket_count;
    
    // 简单哈希函数
    size_t hash(int value) const {
        return static_cast<size_t>(value) % bucket_count;
    }
    
public:
    SimpleHashSet(int capacity = 1000) : bucket_count(capacity) {
        buckets.resize(bucket_count);
    }
    
    void insert(int value) {
        size_t index = hash(value);
        buckets[index].push_back(value);
    }
    
    // 哈希查找（类似 unordered_set.find() 的实现）
    bool hash_find(int value) const {
        size_t index = hash(value);
        
        // 只在对应的桶中线性查找
        for (int item : buckets[index]) {
            if (item == value) {
                return true;
            }
        }
        return false;
    }
    
    // 获取所有元素（用于模拟 std::find）
    std::vector<int> getAllElements() const {
        std::vector<int> all_elements;
        for (const auto& bucket : buckets) {
            for (int item : bucket) {
                all_elements.push_back(item);
            }
        }
        return all_elements;
    }
};

// 线性查找（类似 std::find 的实现）
bool linear_find(const std::vector<int>& container, int value) {
    for (int item : container) {
        if (item == value) {
            return true;
        }
    }
    return false;
}

int main() {
    const int DATA_SIZE = 160000;
    SimpleHashSet hash_set(1000);  // 1000个桶
    
    std::cout << "=== 哈希表结构解析 ===" << std::endl;
    std::cout << "哈希表桶数量: 1000" << std::endl;
    std::cout << "总元素数量: " << DATA_SIZE << std::endl;
    std::cout << "平均每个桶的元素: " << DATA_SIZE / 1000.0 << std::endl;
    std::cout << std::endl;
    
    // 插入数据
    for (int i = 0; i < DATA_SIZE; ++i) {
        hash_set.insert(i);
    }
    
    // 获取所有元素（模拟 unordered_set 的迭代器）
    std::vector<int> all_elements = hash_set.getAllElements();
    
    const int TEST_COUNT = 1000;
    
    // 测试哈希查找
    auto start1 = std::chrono::high_resolution_clock::now();
    int found1 = 0;
    for (int i = 0; i < TEST_COUNT; ++i) {
        if (hash_set.hash_find(i)) {
            found1++;
        }
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1);
    
    std::cout << "=== 哈希查找 (hash_find) ===" << std::endl;
    std::cout << "工作原理: " << std::endl;
    std::cout << "  1. 对值" << TEST_COUNT/2 << "计算哈希: " << TEST_COUNT/2 << " % 1000 = " << TEST_COUNT/2 % 1000 << std::endl;
    std::cout << "  2. 只在第" << TEST_COUNT/2 % 1000 << "个桶中查找" << std::endl;
    std::cout << "  3. 该桶约有 " << DATA_SIZE / 1000 << " 个元素" << std::endl;
    std::cout << "时间复杂度: O(1) 平均" << std::endl;
    std::cout << "总耗时: " << duration1.count() << " 纳秒" << std::endl;
    std::cout << "平均每次: " << duration1.count() / TEST_COUNT << " 纳秒" << std::endl;
    
    // 测试线性查找
    auto start2 = std::chrono::high_resolution_clock::now();
    int found2 = 0;
    for (int i = 0; i < TEST_COUNT; ++i) {
        if (linear_find(all_elements, i)) {
            found2++;
        }
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);
    
    std::cout << "\n=== 线性查找 (linear_find) ===" << std::endl;
    std::cout << "工作原理: " << std::endl;
    std::cout << "  1. 从第一个元素开始遍历" << std::endl;
    std::cout << "  2. 依次检查每个元素是否匹配" << std::endl;
    std::cout << "  3. 需要遍历平均 " << DATA_SIZE / 2 << " 个元素才能找到" << std::endl;
    std::cout << "时间复杂度: O(n)" << std::endl;
    std::cout << "总耗时: " << duration2.count() << " 纳秒" << std::endl;
    std::cout << "平均每次: " << duration2.count() / TEST_COUNT << " 纳秒" << std::endl;
    
    // 详细计算查找次数
    std::cout << "\n=== 查找次数分析 ===" << std::endl;
    std::cout << "哈希查找单次最大检查元素数: " << DATA_SIZE / 1000 << " (桶的大小)" << std::endl;
    std::cout << "线性查找单次平均检查元素数: " << DATA_SIZE / 2 << " (一半的元素)" << std::endl;
    std::cout << "性能差异倍数: " << (double)duration2.count() / duration1.count() << " 倍" << std::endl;
    std::cout << "理论查找次数比: " << (double)(DATA_SIZE / 2) / (DATA_SIZE / 1000) << " 倍" << std::endl;
    
    // 模拟一次具体的查找过程
    std::cout << "\n=== 具体查找示例 ===" << std::endl;
    int search_value = 123456;
    std::cout << "查找值: " << search_value << std::endl;
    
    // 哈希查找过程
    size_t hash_index = static_cast<size_t>(search_value) % 1000;
    std::cout << "哈希查找过程:" << std::endl;
    std::cout << "  1. 计算哈希: " << search_value << " % 1000 = " << hash_index << std::endl;
    std::cout << "  2. 只检查第" << hash_index << "个桶中的约" << DATA_SIZE/1000 << "个元素" << std::endl;
    std::cout << "  3. 总共检查约" << DATA_SIZE/1000 << "次比较" << std::endl;
    
    // 线性查找过程
    std::cout << "\n线性查找过程:" << std::endl;
    std::cout << "  1. 从元素0开始检查" << std::endl;
    std::cout << "  2. 依次检查: 0, 1, 2, ..." << std::endl;
    std::cout << "  3. 需要检查" << search_value << "次比较才能找到" << search_value << std::endl;
    std::cout << "  4. 如果找不存在的元素，需要检查所有" << DATA_SIZE << "个元素" << std::endl;
    
    return 0;
}