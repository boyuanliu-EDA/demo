// this is the standard usage of boost  serialization
// 序列化 = 对象 -> 字节流
// 反序列化 = 字节流 -> 对象

// 序列化： 将对象的状态信息转换为可以存储或传输的形式的过程
// 反序列化：将存储或传输的形式重新构建为对象的过程
#include <iostream>
#include <fstream>
#include <string>
#include <exception>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Person {
    private:

    std::string name;
    int age;
    double salary;

    // key extern class
    friend class boost::serialization::access;

    // temple
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & name;   // serialize name
        ar & age;    // serialize age
        ar & salary; // serialize salary
    }

    public:
        Person() {} // must

        Person(const std::string& n, int a, double s): name(n),age(a),salary(s) {};

        void display() const {
            std::cout << "Name: " << name << ", Age: " << age << ", salary: " << salary << std::endl;
        }

        // De serialization
        static Person loadFromFile(const std::string& filename) {
            Person person;

            std::ifstream ifs(filename);
            if (!ifs) {
                throw std::runtime_error("cannot open file" + filename);
            }

            try {
                boost::archive::text_iarchive ia(ifs);
                ia >> person;
            } catch (...) {
                throw std::runtime_error("deserialization fail: " + filename);
            }

            return person;
        }

        // Serialization
        void saveToFile (const std::string& filename) const {
            std::ofstream ofs(filename);

            if (!ofs) {
                throw std::runtime_error("cannot create file: " + filename);
            }

            try {
                boost::archive::text_oarchive oa(ofs);
                oa << *this;
            } catch (...) {
                throw std::runtime_error("fail on serialization: " + filename);
            }
        }

        // get interface
        std::string getName() const { return name; }
        int getAge() const { return age; }
        double getSalary() const { return salary; }


        // set interface
        void setName(const std::string& n) { name = n; }
        void setAge(int a) { age = a; }
        void setSalary(double s) { salary = s; }

};

int main() {
    // 1 create object
    Person john("John Doe", 30, 5000.0);
    std::cout << "original object: ";
    john.display();

    // 2 save to file
    john.saveToFile("person.dat");
    std::cout << "have saved to file" << std::endl;
    
    // 3 load from file
    std::cout << "load from file..." << std::endl;
    auto p2 = Person::loadFromFile("person.dat");
    p2.display();
}