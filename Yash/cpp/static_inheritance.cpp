#include <iostream>
using namespace std;

class Base {
public:
    static int count;
    static void display() {
        cout << "Static method from Base" << endl;
    }
};

int Base::count = 0;

class Derived : public Base {
public:
    void increment() {
        count++;
    }
};

int main() {
    Derived d1, d2;
    d1.increment();
    d2.increment();
    cout << "Count: " << Base::count << endl;
    Base::display();
    Derived::display();
    return 0;
}
