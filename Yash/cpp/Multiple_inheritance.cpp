#include <iostream>
#include <string>

using namespace std;


class Student {
protected:
	string name;
	int rollNo;

public:
	void setStudentDetails(const string& studentName, int rollNumber) {
		name = studentName;
		rollNo = rollNumber;
	}

	void showStudentDetails() const {
		cout << "Name    : " << name << endl;
		cout << "Roll No.: " << rollNo << endl;
	}
};


class Marks {
protected:
	float maths;
	float science;

public:
	void setMarks(float m, float s) {
		maths = m;
		science = s;
	}

	void showMarks() const {
		cout << "Maths   : " << maths << endl;
		cout << "Science : " << science << endl;
	}
};


class Result : public Student, public Marks {
public:
	void showResult() const {
		float total = maths + science;
		float percentage = total / 2.0f;

		cout << "\n--- Student Result ---" << endl;
		showStudentDetails();
		showMarks();
		cout << "Total   : " << total << endl;
		cout << "Percent : " << percentage << "%" << endl;
	}
};

int main() {
	Result student1;

	student1.setStudentDetails("Yash", 101);
	student1.setMarks(89.5f, 92.0f);
	student1.showResult();

	return 0;
}
