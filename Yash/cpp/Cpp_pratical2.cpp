#include<iostream>
using namespace std;

class A{
    public:
        void showA(){
            cout<<"it is base class"<<endl;
        }
};

class B : public A{
    public:
        void showB(){
            cout<<"it is derived class"<<endl;
        }
};

class C : public B {
    public:
        void showC(){
            cout<<"it is class C"<<endl;
        }
};

int main(){
    C obj;
    obj.showA();
    obj.showB();
    obj.showC();
}