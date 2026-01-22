#include <iostream>
using namespace std;

class IntList{
private:
class Node {
    public:
    int value; // the data stored
    Node* next; // pointer to the next Node

    // constructor
    Node(int val = 0): value(val), next(nullptr) {
        std::cout << "create node, value=" << value;
        std::cout << ", address=" << this << std::endl;
    }

    // destructor
    ~Node() {
        std::cout << "destroy the node, value=" << value;
        std::cout << ", address=" << this << std::endl;
    }
};

// pointer to the head
Node* head;
// element count
int size;

public:
// constructor of IntList
IntList(): head(nullptr),size(0) {
    std::cout << "=== IntList 构造 ===" << std::endl;
    std::cout << "head初始化为nullptr, size=0" << std::endl;
}

// destructor
~IntList() {
    std::cout << "\n === IntList destructor ===" << std::endl;
    std::cout << "start release all the Nodes ..." << std::endl;

    Node* current  = head;
    int count = 0;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
        count++;
    }
    std::cout << "release " << count << " Nodes" << std::endl;
    head = nullptr;
    size = 0;
}

// add an element to the end of the list
void push_back(int value) {
    std::cout << "\n=== push_back(" << value << ") ===" << std::endl;

    // create a new Node
    Node* newNode = new Node(value);

    if (head == nullptr) {
        // case1, the list is empty
        std::cout << "the list is empty, newNode becomes the head" << std::endl;
        head = newNode;
    } else {
        // case2, the list is not empty, search the last Node
        std::cout << "search the last Node ..." << std::endl;
        Node* current = head;
        int steps = 0;

        while (current->next != nullptr) {
            current = current->next;
            steps++;
        }

        std::cout << "find the last node, traverse:" << steps << " steps" << std::endl;
        std::cout << "最后一个节点的地址: " << current << std::endl;

        
    // connect new node to the end of list
    current->next = newNode;
    std::cout << "将新节点连接到末尾" << std::endl;
    }
    size++;
    std::cout << "添加完成,size=" << size << std::endl;
}

// add element to the head of list
void push_front(int value) {
    cout << "\n=== push_front(" << value << ") ===" << endl;
    
    Node* newNode = new Node(value);
    
    // 新节点的next指向原来的头节点
    newNode->next = head;
    cout << "新节点->next = " << head << " (原头节点地址)" << endl;
    
    // 更新头指针指向新节点
    head = newNode;
    cout << "head = " << head << " (新节点地址)" << endl;
    
    size++;
    cout << "添加完成，size=" << size << endl;
}

void print() const {
    cout << "\n=== 链表状态 ===" << endl;
    cout << "大小: " << size << endl;
    cout << "头指针: " << head << endl;
    
    if (head == nullptr) {
        cout << "链表为空" << endl;
        return;
    }
    
    cout << "元素: ";
    Node* current = head;
    int count = 0;
    
    while (current != nullptr) {
        cout << current->value;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        
        // 每3个元素换行显示
        count++;
        if (count % 3 == 0 && current->next != nullptr) {
            cout << "\n        ";  // 缩进对齐
        }
        
        current = current->next;
    }
    cout << " -> NULL" << endl;
    
    // 显示节点地址信息
    cout << "\n详细节点信息:" << endl;
    current = head;
    int index = 0;
    
    while (current != nullptr) {
        cout << "  节点[" << index << "]: ";
        cout << "地址=" << current;
        cout << "，值=" << current->value;
        cout << "，next=" << current->next << endl;
        
        current = current->next;
        index++;
    }
}
};

void demonstrateIntList() {
    cout << "======= IntList 详细演示 =======\n" << endl;
    
    IntList list;
    
    // 1. 添加元素到末尾
    cout << "\n1. 添加元素到末尾:" << endl;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.print();
    
    // 2. 添加元素到头部
    cout << "\n2. 添加元素到头部:" << endl;
    list.push_front(5);
    list.print();
}

int main() {
    demonstrateIntList();
    return 0;
}