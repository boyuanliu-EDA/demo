#include <iostream>
#include <variant>
#include <string>

// 使用最简单的数据类型：int 和 std::string
void processValue(std::variant<int, std::string> value) {
    // 定义 visitor - 根据不同类型执行不同操作
    auto visitor = [](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        
        if constexpr (std::is_same_v<T, int>) {
            std::cout << "整数: " << arg << " (两倍是: " << arg * 2 << ")" << std::endl;
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "字符串: \"" << arg << "\" (长度: " << arg.length() << ")" << std::endl;
        }
    };
    
    // 调用 visit 处理值
    std::visit(visitor, value);
}

int main() {
    // 测试整数
    processValue(42);
    
    // 测试字符串
    processValue(std::string("Hello"));
    
    // 也可以直接使用字面量
    processValue(100);
    processValue(std::string("World"));
    
    return 0;
}