// singleton_config.cpp
#include <iostream>
#include <string>
#include <map>

class ConfigManager {
private:
    static ConfigManager* instance;
    std::map<std::string, std::string> configData;
    
    // 私有构造函数，防止外部创建实例
    ConfigManager() {
        // 加载默认配置
        configData["server_address"] = "127.0.0.1";
        configData["server_port"] = "8080";
        configData["max_connections"] = "100";
        configData["debug_mode"] = "false";
        std::cout << "ConfigManager 初始化完成\n";
    }
    
    // 防止拷贝
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
    // 防止通过拷贝创建新实例：ConfigManager obj2 = obj1;
    //防止通过赋值创建新实例：ConfigManager obj2; obj2 = obj1;
    
public:
    // 获取单例实例的静态方法
    static ConfigManager* getInstance() {
        if (instance == nullptr) {
            instance = new ConfigManager();
        }
        return instance;
    }
    
    // 获取配置值
    std::string getConfig(const std::string& key) {
        auto it = configData.find(key);
        if (it != configData.end()) {
            return it->second;
        }
        return "";
    }
    
    // 设置配置值
    void setConfig(const std::string& key, const std::string& value) {
        configData[key] = value;
        std::cout << "配置更新: " << key << " = " << value << std::endl;
    }
    
    // 显示所有配置
    void displayAllConfigs() {
        std::cout << "\n=== 当前所有配置 ===\n";
        for (const auto& pair : configData) {
            std::cout << "  " << pair.first << " = " << pair.second << std::endl;
        }
        std::cout << "===================\n";
    }
    
    // 获取实例计数（演示用）
    static int getInstanceCount() {
        return (instance != nullptr) ? 1 : 0;
    }
    
    // 清理单例（实际项目中要小心使用）
    static void destroyInstance() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
            std::cout << "ConfigManager 实例已销毁\n";
        }
    }
};

// 初始化静态成员
ConfigManager* ConfigManager::instance = nullptr;

// 模拟不同的模块
class DatabaseModule {
public:
    void connect() {
        ConfigManager* config = ConfigManager::getInstance();
        std::string address = config->getConfig("server_address");
        std::string port = config->getConfig("server_port");
        std::cout << "[数据库模块] 连接到服务器: " << address << ":" << port << std::endl;
    }
};

class NetworkModule {
public:
    void setup() {
        ConfigManager* config = ConfigManager::getInstance();
        int maxConn = std::stoi(config->getConfig("max_connections"));
        std::cout << "[网络模块] 设置最大连接数: " << maxConn << std::endl;
    }
};

class LoggerModule {
public:
    void logInfo() {
        ConfigManager* config = ConfigManager::getInstance();
        bool debug = config->getConfig("debug_mode") == "true";
        std::cout << "[日志模块] 调试模式: " << (debug ? "开启" : "关闭") << std::endl;
    }
};

int main() {
    std::cout << "=== 单例配置管理器演示 ===\n\n";
    
    // 第一次获取实例
    std::cout << "1. 第一次获取配置管理器实例:\n";
    ConfigManager* config1 = ConfigManager::getInstance();
    config1->displayAllConfigs();
    
    // 修改一些配置
    config1->setConfig("server_port", "9090");
    config1->setConfig("debug_mode", "true");
    
    // 再次获取实例（应该是同一个）
    std::cout << "\n2. 第二次获取配置管理器实例:\n";
    ConfigManager* config2 = ConfigManager::getInstance();
    std::cout << "config1 和 config2 是同一个实例吗？ " 
              << (config1 == config2 ? "是的" : "不是") << std::endl;
    
    // 模拟不同模块使用配置
    std::cout << "\n3. 模拟不同模块使用配置:\n";
    DatabaseModule db;
    NetworkModule network;
    LoggerModule logger;
    
    db.connect();
    network.setup();
    logger.logInfo();
    
    // 再次显示配置
    config2->displayAllConfigs();
    
    std::cout << "\n4. 实例计数: " << ConfigManager::getInstanceCount() << std::endl;
    
    // 清理（实际项目中可能不需要手动清理）
    // ConfigManager::destroyInstance();
    
    return 0;
}