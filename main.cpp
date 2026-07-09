// Name: Simran Ghimire
// Course: CSCE 3444
// Project: AI Smart Study Assistant for UNT Students
// Feature: Dashboard, Assignment Management, Study Planner, Progress Tracking

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Assignment {
    string title;
    string course;
    string dueDate;
    string priority;
    bool completed;
};

vector<Assignment> assignments;

void showDashboard() {
    cout << "\n===== AI Smart Study Assistant Dashboard =====\n";
    cout << "Welcome back, Student!\n";
    cout << "Upcoming Assignments: " << assignments.size() << endl;

    int completed = 0;
    for (auto &a : assignments) {
        if (a.completed) completed++;
    }

    cout << "Completed Tasks: " << completed << endl;
    cout << "Pending Tasks: " << assignments.size() - completed << endl;
    cout << "Study Reminder: Start with your highest priority assignment.\n";
}

void addAssignment() {
    Assignment a;
    cin.ignore();

    cout << "\nEnter assignment title: ";
    getline(cin, a.title);

    cout << "Enter course name: ";
    getline(cin, a.course);

    cout << "Enter due date: ";
    getline(cin, a.dueDate);

    cout << "Enter priority (High/Medium/Low): ";
    getline(cin, a.priority);

    a.completed = false;
    assignments.push_back(a);

    cout << "Assignment added successfully!\n";
}

void viewAssignments() {
    cout << "\n===== Assignment Management =====\n";

    if (assignments.empty()) {
        cout << "No assignments added yet.\n";
        return;
    }

    for (int i = 0; i < assignments.size(); i++) {
        cout << i + 1 << ". " << assignments[i].title << endl;
        cout << "   Course: " << assignments[i].course << endl;
        cout << "   Due Date: " << assignments[i].dueDate << endl;
        cout << "   Priority: " << assignments[i].priority << endl;
        cout << "   Status: " << (assignments[i].completed ? "Completed" : "Pending") << endl;
    }
}

void markCompleted() {
    viewAssignments();

    if (assignments.empty()) return;

    int choice;
    cout << "\nEnter assignment number to mark complete: ";
    cin >> choice;

    if (choice >= 1 && choice <= assignments.size()) {
        assignments[choice - 1].completed = true;
        cout << "Assignment marked as completed!\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

void generateStudyPlan() {
    cout << "\n===== AI Study Planner =====\n";

    if (assignments.empty()) {
        cout << "Add assignments first to generate a study plan.\n";
        return;
    }

    int hours;
    cout << "Enter available study hours today: ";
    cin >> hours;

    cout << "\nRecommended Study Plan:\n";

    for (auto &a : assignments) {
        if (!a.completed) {
            cout << "- Study " << a.course << " for assignment: " << a.title << endl;
            cout << "  Priority: " << a.priority << ", Due: " << a.dueDate << endl;
        }
    }

    cout << "\nProductivity Suggestion: Start with High priority tasks first.\n";
    cout << "Available study hours recorded: " << hours << " hour(s)\n";
}

void showProgress() {
    cout << "\n===== Progress Tracking =====\n";

    if (assignments.empty()) {
        cout << "No progress yet. Add assignments first.\n";
        return;
    }

    int completed = 0;
    for (auto &a : assignments) {
        if (a.completed) completed++;
    }

    double percent = (double)completed / assignments.size() * 100;

    cout << "Completed: " << completed << endl;
    cout << "Pending: " << assignments.size() - completed << endl;
    cout << "Overall Progress: " << percent << "% complete\n";
}

int main() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "AI Smart Study Assistant\n";
        cout << "1. View Dashboard\n";
        cout << "2. Add Assignment\n";
        cout << "3. View Assignments\n";
        cout << "4. Generate AI Study Plan\n";
        cout << "5. Mark Assignment Completed\n";
        cout << "6. View Progress\n";
        cout << "7. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                showDashboard();
                break;
            case 2:
                addAssignment();
                break;
            case 3:
                viewAssignments();
                break;
            case 4:
                generateStudyPlan();
                break;
            case 5:
                markCompleted();
                break;
            case 6:
                showProgress();
                break;
            case 7:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}