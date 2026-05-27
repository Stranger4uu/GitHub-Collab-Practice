#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Subject {
private:
    string name;
    float marks;
    float maxMarks;

public:
   
    Subject(string n = "", float m = 0, float mm = 100)
        : name(n), marks(m), maxMarks(mm) {}

    
    inline string getName()     const { return name; }
    inline float  getMarks()    const { return marks; }
    inline float  getMaxMarks() const { return maxMarks; }

   
    inline float getPercentage() const {
        return (marks / maxMarks) * 100;
    }

    void display() const {
        cout << "  " << left << setw(20) << name
             << setw(10) << marks
             << setw(10) << maxMarks
             << fixed << setprecision(2) << getPercentage() << "%\n";
    }
};


class Student {
protected:
    int    rollNo;
    string name;
    int    numSubjects;
    Subject subjects[10]; 
    float  totalMarks;
    float  totalMaxMarks;

public:
    static int totalStudents;   
    static float classTotal;   

   
    Student(int roll, string n, Subject subs[], int count)
        : rollNo(roll), name(n), numSubjects(count),
          totalMarks(0), totalMaxMarks(0) {
        for (int i = 0; i < count; i++) {
            subjects[i]   = subs[i];
            totalMarks    += subs[i].getMarks();
            totalMaxMarks += subs[i].getMaxMarks();
        }
        totalStudents++;
        classTotal += getPercentage();
        cout << "[Student Added] " << name << " (Roll No: " << rollNo << ")\n";
    }

    
    virtual ~Student() {
        cout << "[Record Removed] " << name << "\n";
    }

   
    int    getRollNo()     const { return rollNo; }
    string getName()       const { return name; }
    float  getTotalMarks() const { return totalMarks; }

    
    float getPercentage() const {
        return (totalMarks / totalMaxMarks) * 100;
    }

    
    inline string getGrade() const {
        float p = getPercentage();
        if      (p >= 90) return "A+";
        else if (p >= 80) return "A";
        else if (p >= 70) return "B";
        else if (p >= 60) return "C";
        else if (p >= 50) return "D";
        else              return "F";
    }

    
    inline string getStatus() const {
        for (int i = 0; i < numSubjects; i++) {
            if (subjects[i].getMarks() < 33) return "FAIL";
        }
        return "PASS";
    }

    
    virtual void display() const {
        cout << "\n────────────────────────────────────\n";
        cout << "  Roll No    : " << rollNo      << "\n";
        cout << "  Name       : " << name        << "\n";
        cout << "  Percentage : " << fixed << setprecision(2)
             << getPercentage()   << "%\n";
        cout << "  Grade      : " << getGrade()  << "\n";
        cout << "  Status     : " << getStatus() << "\n";
        cout << "  ── Subjects ──\n";
        cout << "  " << left << setw(20) << "Subject"
             << setw(10) << "Marks"
             << setw(10) << "Max"
             << "Percentage\n";
        for (int i = 0; i < numSubjects; i++) {
            subjects[i].display();
        }
    }

    
    virtual void saveToFile(ofstream& file) const {
        file << "REGULAR " << rollNo << " " << name << " " << numSubjects << "\n";
        for (int i = 0; i < numSubjects; i++) {
            file << subjects[i].getName() << " "
                 << subjects[i].getMarks() << " "
                 << subjects[i].getMaxMarks() << "\n";
        }
    }

    
    bool operator>(const Student& other) const {
        return getPercentage() > other.getPercentage();
    }

    bool operator==(const Student& other) const {
        return getPercentage() == other.getPercentage();
    }

    
    friend void printRankComparison(const Student& s1, const Student& s2);
    friend float getClassAverage();
};


int   Student::totalStudents = 0;
float Student::classTotal    = 0;


void printRankComparison(const Student& s1, const Student& s2) {
    cout << "\n── Rank Comparison ──\n";
    cout << s1.name << " → " << fixed << setprecision(2)
         << s1.getPercentage() << "% (" << s1.getGrade() << ")\n";
    cout << s2.name << " → " << fixed << setprecision(2)
         << s2.getPercentage() << "% (" << s2.getGrade() << ")\n";

    if (s1 > s2)
        cout << "🏆 " << s1.name << " ranks higher!\n";
    else if (s2 > s1)
        cout << "🏆 " << s2.name << " ranks higher!\n";
    else
        cout << "🤝 Both students are tied!\n";
}


class RegularStudent : public Student {
    string section;

public:
    RegularStudent(int roll, string n, Subject subs[], int count, string sec)
        : Student(roll, n, subs, count), section(sec) {}

    ~RegularStudent() override {
        cout << "[Regular Student Record Closed]\n";
    }

    void display() const override {
        Student::display(); 
        cout << "  Section    : " << section << "\n";
        cout << "  Type       : Regular Student\n";
    }

    void saveToFile(ofstream& file) const override {
        file << "REGULAR " << rollNo << " " << name
             << " " << numSubjects << " " << section << "\n";
        for (int i = 0; i < numSubjects; i++) {
            file << subjects[i].getName() << " "
                 << subjects[i].getMarks() << " "
                 << subjects[i].getMaxMarks() << "\n";
        }
    }
};


class ScholarshipStudent : public Student {
    float scholarshipPercent;

public:
    ScholarshipStudent(int roll, string n, Subject subs[], int count, float schol)
        : Student(roll, n, subs, count), scholarshipPercent(schol) {}

    ~ScholarshipStudent() override {
        cout << "[Scholarship Student Record Closed]\n";
    }

    bool isEligible() const {
        return getPercentage() >= 75.0f;
    }

    void display() const override {
        Student::display();
        cout << "  Type       : Scholarship Student\n";
        cout << "  Scholarship: " << scholarshipPercent << "%\n";
        cout << "  Eligible   : " << (isEligible() ? "YES ✓" : "NO ✗") << "\n";
    }

    void saveToFile(ofstream& file) const override {
        file << "SCHOLAR " << rollNo << " " << name
             << " " << numSubjects << " " << scholarshipPercent << "\n";
        for (int i = 0; i < numSubjects; i++) {
            file << subjects[i].getName() << " "
                 << subjects[i].getMarks() << " "
                 << subjects[i].getMaxMarks() << "\n";
        }
    }
};


Student* findTopper(Student* students[], int count) {
    Student* topper = students[0];
    for (int i = 1; i < count; i++) {
        if (*students[i] > *topper)
            topper = students[i];
    }
    return topper;
}


void saveAllStudents(Student* students[], int count) {
    ofstream file("students.txt");
    if (!file) { cout << "Error opening file!\n"; return; }
    for (int i = 0; i < count; i++) {
        students[i]->saveToFile(file);
    }
    file.close();
    cout << "\n✓ All records saved to students.txt\n";
}

void loadStudents() {
    ifstream file("students.txt");
    if (!file) { cout << "No saved data found.\n"; return; }
    cout << "\n── Saved Records ──\n";
    string line;
    while (getline(file, line)) cout << line << "\n";
    file.close();
}


int main() {
    cout << "════════════════════════════════════\n";
    cout << "    STUDENT GRADE CALCULATOR\n";
    cout << "════════════════════════════════════\n\n";

    Subject s1[] = {
        Subject("Mathematics",   88, 100),
        Subject("Physics",       76, 100),
        Subject("Chemistry",     91, 100),
        Subject("C++ Programming", 95, 100),
        Subject("English",       70, 100)
    };
    RegularStudent* r1 = new RegularStudent(101, "Yash", s1, 5, "A");


    Subject s2[] = {
        Subject("Mathematics",   72, 100),
        Subject("Physics",       68, 100),
        Subject("Chemistry",     75, 100),
        Subject("C++ Programming", 80, 100),
        Subject("English",       65, 100)
    };
    RegularStudent* r2 = new RegularStudent(102, "Harshvardhan", s2, 5, "A");


    Subject s3[] = {
        Subject("Mathematics",   93, 100),
        Subject("Physics",       89, 100),
        Subject("Chemistry",     85, 100),
        Subject("C++ Programming", 97, 100),
        Subject("English",       88, 100)
    };
    ScholarshipStudent* sc1 = new ScholarshipStudent(103, "Jaivardhan", s3, 5, 75.0f);


    Subject s4[] = {
        Subject("Mathematics",   55, 100),
        Subject("Physics",       48, 100),
        Subject("Chemistry",     62, 100),
        Subject("C++ Programming", 70, 100),
        Subject("English",       58, 100)
    };
    ScholarshipStudent* sc2 = new ScholarshipStudent(104, "Abhi", s4, 5, 50.0f);


    Student* students[] = { r1, r2, sc1, sc2 };
    int count = 4;

    
    cout << "\n══ ALL STUDENT REPORTS ══";
    for (int i = 0; i < count; i++) students[i]->display();

   
    float classAvg = Student::classTotal / Student::totalStudents;
    cout << "\n── Class Statistics ──\n";
    cout << "  Total Students : " << Student::totalStudents << "\n";
    cout << "  Class Average  : " << fixed << setprecision(2) << classAvg << "%\n";

   
    Student* topper = findTopper(students, count);
    cout << "  Class Topper   : " << topper->getName()
         << " (" << topper->getPercentage() << "%)\n";

   
    printRankComparison(*r1, *sc1);

   
    cout << "\n── Operator Overloading (> compare) ──\n";
    if (*sc1 > *r1)
        cout << sc1->getName() << " scored higher than " << r1->getName() << "\n";

    
    saveAllStudents(students, count);
    loadStudents();

    
    cout << "\n── Cleanup ──\n";
    for (int i = 0; i < count; i++) delete students[i];

    return 0;
}