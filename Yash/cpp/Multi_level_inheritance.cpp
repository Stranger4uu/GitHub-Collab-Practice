#include <iostream>
#include <string>

using namespace std;

class Person {
protected:
	string name;

public:
	void setName(const string& personName) {
		name = personName;
	}

	void showName() const {
		cout << "Name       : " << name << endl;
	}
};


class Student : public Person {
protected:
	int rollNo;

public:
	void setRollNo(int rollNumber) {
		rollNo = rollNumber;
	}

	void showRollNo() const {
		cout << "Roll No.   : " << rollNo << endl;
	}
};


class Result : public Student {
private:
	float marks;

public:
	void setMarks(float studentMarks) {
		marks = studentMarks;
	}

	void showResult() const {
		cout << "Marks      : " << marks << endl;
		if (marks >= 40.0f) {
			cout << "Status     : Pass" << endl;
		} else {
			cout << "Status     : Fail" << endl;
		}
	}

	void displayAll() const {
		cout << "\n--- Student Record ---" << endl;
		showName();
		showRollNo();
		showResult();
	}
};

int main() {
	Result student1;

	student1.setName("Yash");
	student1.setRollNo(101);
	student1.setMarks(86.5f);

	student1.displayAll();

	return 0;
}
