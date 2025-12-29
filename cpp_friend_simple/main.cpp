#include <iostream>
using namespace std;

// click
#define EXAMPLE_1
#define EXAMPLE_2
#define EXAMPLE_3

#ifdef EXAMPLE_1

class Box {

private:
    int length;

public:
    Box() : length(10) {}

    // extern friend function
    friend void printLength(Box box);
};

// define friend function, it can access private
void printLength(Box box) {
    std::cout << "Length:" << box.length << std::endl;
}

#endif

#ifdef EXAMPLE_2
class B;
class A {
    private:
    int numA;
    public:
    A():numA(5) {}
    friend int sum(A objA, B objB);
};

class B {
    private:
    int numB;
    public:
    B():numB(10){};
    friend int sum(A objA, B objB);
};

int sum(A objA, B objB) {
    return objA.numA + objB.numB;
}
#endif

#ifdef EXAMPLE_3

class Distance {
    private:
    int meters;

    public:
    Distance(int m = 0): meters(m) {}

    friend Distance operator+(const Distance& d1, const Distance& d2);
    friend Distance operator+(const Distance& d, int value);
    friend Distance operator+(int value,const Distance& d);

    friend ostream& operator<<(ostream& os, const Distance& d);

    void display() {std::cout << meters << " meters";}
};

Distance operator+(int value, const Distance& d) {
    return Distance(value + d.meters);
}

Distance operator+(const Distance& d, int value) {
    return Distance(d.meters + value); 
}


Distance operator+(const Distance& d1, const Distance& d2) {
    return Distance(d1.meters + d2.meters);
}

ostream& operator<<(ostream& os, const Distance& d) {
    os << d.meters << " meters";
    return os;
}

#endif

int main() {
    cout << "===== Running Friend Function Examples =====" << endl;
    
#ifdef EXAMPLE_1
    cout << "\n[Example 1] Basic friend function:" << endl;
    Box myBox;
    printLength(myBox);
#endif

#ifdef EXAMPLE_2
    cout << "\n[Example 2] Friend with two classes:" << endl;
    A objA;
    B objB;
    cout << "Sum: " << sum(objA, objB) << endl;
#endif

#ifdef EXAMPLE_3
    cout << "\n[Example 3] Friend operator overloading:" << endl;
    Distance d1(10);
    Distance d2(20);
    Distance d3 = d1 + d2;
    cout << d3 << endl;
    operator<<(cout, d3)<< endl;
    cout << "Sum: ";
    d3.display();
    cout << endl;
#endif
    
    return 0;
}
   
