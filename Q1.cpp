#include <iostream>
using namespace std;

class Mentor; // Forward declaration to resolve dependencies

class Student {
private:
    string studentID, name;
    int age;
    string* sportsInterests;
    int numInterests;
    Mentor* mentorAssigned;

public:
    Student(string id, string n, int a, int numInterests) {
        studentID = id;
        name = n;
        age = a;
        this->numInterests = numInterests;
        sportsInterests = new string[numInterests]; // Dynamic allocation
        mentorAssigned = NULL;
    }
    
    string getName(){
    	return name;
	}

    ~Student() {
        delete[] sportsInterests; // Free allocated memory
    }

    void registerForMentorship(Mentor* m);
    void viewMentorDetails();
    void updateSportsInterest(string newInterest);

    void addInterest(int index, string interest) {
        if (index >= 0 && index < numInterests) {
            sportsInterests[index] = interest;
        }
    }
};

class Mentor {
private:
    string mentorID, name;
    string* sportsExpertise;
    int maxLearners;
    Student** assignedLearners;
    int numExpertise;
    int currentLearners;

public:
    Mentor(string id, string n, int numExpertise, int maxL) {
        mentorID = id;
        name = n;
        this->numExpertise = numExpertise;
        sportsExpertise = new string[numExpertise];
        maxLearners = maxL;
        assignedLearners = new Student*[maxL];
        currentLearners = 0;
    }

    ~Mentor() {
        delete[] sportsExpertise;
        delete[] assignedLearners;
    }

    bool assignLearner(Student* s) {
        if (currentLearners < maxLearners) {
            assignedLearners[currentLearners++] = s;
            return true;
        }
        return false;
    }

    void viewLearners() {
        cout << "Mentor: " << name << "'s Learners:\n";
        for (int i = 0; i < currentLearners; i++) {
            cout << "- " << assignedLearners[i]->getName() << endl;
        }
    }

    string getName() { return name; }
};

void Student::registerForMentorship(Mentor* m) {
    if (m->assignLearner(this)) {
        mentorAssigned = m;
        cout << name << " has been assigned to mentor " << m->getName() << endl;
    } else {
        cout << "Mentor " << m->getName() << " has no available slots." << endl;
    }
}

void Student::viewMentorDetails() {
    if (mentorAssigned) {
        cout << "Mentor assigned: " << mentorAssigned->getName() << endl;
    } else {
        cout << "No mentor assigned." << endl;
    }
}

void Student::updateSportsInterest(string newInterest) {
    if (numInterests > 0) {
        sportsInterests[0] = newInterest;
        cout << "Updated sports interest: " << newInterest << endl;
    }
}

int main() {
    Student s1("S001", "Saad", 20, 3);
    s1.addInterest(0, "Tennis");
    s1.addInterest(1, "Football");
    s1.addInterest(2, "Badminton");

    Mentor m1("M001", "Ali", 2, 3);

    s1.registerForMentorship(&m1);
    s1.viewMentorDetails();
    s1.updateSportsInterest("Basketball");
}
