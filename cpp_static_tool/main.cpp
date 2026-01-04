// math_tool.cpp
#include <iostream>
#include <cmath>

class MathTool {
public:
    // 计算最大值
    static int max(int a, int b) {
        return (a > b) ? a : b;
    }
    
    // 计算最小值
    static int min(int a, int b) {
        return (a < b) ? a : b;
    }
    
    // 计算绝对值
    static int abs(int value) {
        return (value < 0) ? -value : value;
    }
    
    // 计算平方
    static int square(int x) {
        return x * x;
    }
    
    // 判断是否为偶数
    static bool isEven(int number) {
        return number % 2 == 0;
    }
    
    // 阶乘计算
    static long long factorial(int n) {
        if (n <= 1) return 1;
        long long result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }
};

int main() {
    std::cout << "=== 数学工具类演示 ===\n\n";
    
    // 演示各种静态函数的使用
    std::cout << "1. 最大值计算:\n";
    std::cout << "   max(5, 9) = " << MathTool::max(5, 9) << std::endl;
    std::cout << "   max(-3, 0) = " << MathTool::max(-3, 0) << std::endl;
    
    std::cout << "\n2. 最小值计算:\n";
    std::cout << "   min(5, 9) = " << MathTool::min(5, 9) << std::endl;
    
    std::cout << "\n3. 绝对值计算:\n";
    std::cout << "   abs(-10) = " << MathTool::abs(-10) << std::endl;
    std::cout << "   abs(7) = " << MathTool::abs(7) << std::endl;
    
    std::cout << "\n4. 平方计算:\n";
    std::cout << "   square(4) = " << MathTool::square(4) << std::endl;
    std::cout << "   square(-5) = " << MathTool::square(-5) << std::endl;
    
    std::cout << "\n5. 奇偶判断:\n";
    std::cout << "   isEven(10) = " << (MathTool::isEven(10) ? "true" : "false") << std::endl;
    std::cout << "   isEven(7) = " << (MathTool::isEven(7) ? "true" : "false") << std::endl;
    
    std::cout << "\n6. 阶乘计算:\n";
    std::cout << "   factorial(5) = " << MathTool::factorial(5) << std::endl;
    std::cout << "   factorial(0) = " << MathTool::factorial(0) << std::endl;
    
    // 实际应用示例
    std::cout << "\n=== 实际应用示例 ===\n";
    int a = -15, b = 20;
    int maxValue = MathTool::max(MathTool::abs(a), MathTool::abs(b));
    std::cout << "max(|" << a << "|, |" << b << "|) = " << maxValue << std::endl;
    
    // 判断平方是否为偶数
    int num = 6;
    int squared = MathTool::square(num);
    std::cout << num << " 的平方是 " << squared 
              << ", 它是" << (MathTool::isEven(squared) ? "偶数" : "奇数") << std::endl;
    
    return 0;
}