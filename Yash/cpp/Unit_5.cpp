#include <iostream> // Header for cin, cout
using namespace std;
int main()
{
    int age;
    char name[20];
    cout << "Enter name and age: "; // insertion operator <<
    cin >> name >> age;             // extraction operator >>
    cout << "Name: " << name << " Age: " << age;
}
