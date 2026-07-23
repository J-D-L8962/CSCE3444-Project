#include <iostream>
#include <string>
#include "Passwrod_Validation.h"
#include "AssignmentCreation_DbIntegragtion.h"

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

=======
#include <iostream>
#include <string>
#include "Passwrod_Validation.h"
#include "AssignmentCreation_DbIntegragtion.h"

using namespace std;

struct User {
    int id;
    string username;
    string email;
    string password;
    string preferences;
};

User testUser = {
    1,
    "testuser",
    "test@unt.edu",
    "Password123!",
    "Prefers evening study sessions"
};

bool isLoggedIn = false;
int currentUserId = -1;

bool login() {
    string email;
    string password;

    cout << "\n--- Login ---\n";
    cout << "Email: ";
    cin >> email;

    cout << "Password: ";
    cin >> password;

    if (email == testUser.email && password == testUser.password) {
        isLoggedIn = true;
        currentUserId = testUser.id;
        cout << "Login successful. Welcome, " << testUser.username << "!\n";
        return true;
    }

    cout << "Login failed. Invalid email or password.\n";
    return false;
}

void logout() {
    isLoggedIn = false;
    currentUserId = -1;
    cout << "Logout successful. Session ended.\n";
}

void registerUserDemo() {
    string username;
    string email;
    string password;
    string preferences;

    cout << "\n--- Registration Demo ---\n";

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter email: ";
    cin >> email;

    cout << "Enter password: ";
    cin >> password;

    if (!validatePassword(password)) {
        cout << "Registration failed due to weak password.\n";
        return;
    }

    cin.ignore();

    cout << "Enter study preferences: ";
    getline(cin, preferences);

    cout << "Registration test passed. User information and preferences are valid.\n";
}
void updateProfile() {
    string newValue;

    cin.ignore();

    cout << "\n--- Update Profile ---\n";
    cout << "Leave a field blank to keep the current value.\n";

    cout << "Current username: " << testUser.username << endl;
    cout << "New username: ";
    getline(cin, newValue);

    if (!newValue.empty()) {
        testUser.username = newValue;
    }

    cout << "Current email: " << testUser.email << endl;
    cout << "New email: ";
    getline(cin, newValue);

    if (!newValue.empty()) {
        testUser.email = newValue;
    }

    cout << "Current preferences: " << testUser.preferences << endl;
    cout << "New preferences: ";
    getline(cin, newValue);

    if (!newValue.empty()) {
        testUser.preferences = newValue;
    }

    cout << "Profile updated successfully.\n";
}
>>>>>>> main
int main() {
    int choice;

    do {
<<<<<<< simran
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
=======
        cout << "\n===== AI Smart Study App Backend Demo =====\n";
cout << "1. Register User Test\n";
cout << "2. Login\n";
cout << "3. Create Assignment\n";
cout << "4. View Assignments\n";
cout << "5. Delete Assignment\n";
cout << "6. Edit Assignment\n";
cout << "7. Mark Assignment Completed\n";
cout << "8. View Progress Analytics\n";
cout << "9. Update Profile\n";
cout << "10. Logout\n";
cout << "0. Exit\n";
cout << "Choose an option: ";
>>>>>>> main
        cin >> choice;

        switch (choice) {
            case 1:
<<<<<<< simran
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
=======
                registerUserDemo();
                break;

            case 2:
                login();
                break;

            case 3:
                if (isLoggedIn) {
                    createAssignment(currentUserId);
                } else {
                    cout << "Please log in first.\n";
                }
                break;

            case 4:
                if (isLoggedIn) {
                    viewAssignments(currentUserId);
                } else {
                    cout << "Please log in first.\n";
                }
                break;

            case 5:
                if (isLoggedIn) {
                    deleteAssignment(currentUserId);
                } else {
                    cout << "Please log in first.\n";
                }
                break;

            case 6:
    if (isLoggedIn) {
        editAssignment(currentUserId);
    } else {
        cout << "Please log in first.\n";
    }
    break;

case 7:
    if (isLoggedIn) {
        markAssignmentCompleted(currentUserId);
    } else {
        cout << "Please log in first.\n";
    }
    break;

case 8:
    if (isLoggedIn) {
        showProgressAnalytics(currentUserId);
    } else {
        cout << "Please log in first.\n";
    }
    break;

case 9:
    if (isLoggedIn) {
        updateProfile();
    } else {
        cout << "Please log in first.\n";
    }
    break;

case 10:
    if (isLoggedIn) {
        logout();
    } else {
        cout << "No user is currently logged in.\n";
    }
    break;

         case 0:
    cout << "Exiting program.\n";
    break;   
>>>>>>> main
            default:
                cout << "Invalid option. Try again.\n";
        }

<<<<<<< simran
    } while (choice != 7);
=======
    } while (choice != 0);
>>>>>>> main

    return 0;
}

struct User {
    int id;
    string username;
    string email;
    string password;
    string preferences;
};

User testUser = {
    1,
    "testuser",
    "test@unt.edu",
    "Password123!",
    "Prefers evening study sessions"
};

bool isLoggedIn = false;
int currentUserId = -1;

bool login() {
    string email;
    string password;

    cout << "\n--- Login ---\n";
    cout << "Email: ";
    cin >> email;

    cout << "Password: ";
    cin >> password;

    if (email == testUser.email && password == testUser.password) {
        isLoggedIn = true;
        currentUserId = testUser.id;
        cout << "Login successful. Welcome, " << testUser.username << "!\n";
        return true;
    }

    cout << "Login failed. Invalid email or password.\n";
    return false;
}

void logout() {
    isLoggedIn = false;
    currentUserId = -1;
    cout << "Logout successful. Session ended.\n";
}

void registerUserDemo() {
    string username;
    string email;
    string password;
    string preferences;

    cout << "\n--- Registration Demo ---\n";

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter email: ";
    cin >> email;

    cout << "Enter password: ";
    cin >> password;

    if (!validatePassword(password)) {
        cout << "Registration failed due to weak password.\n";
        return;
    }

    cin.ignore();

    cout << "Enter study preferences: ";
    getline(cin, preferences);

    cout << "Registration test passed. User information and preferences are valid.\n";
}
void updateProfile() {
    string newValue;

    cin.ignore();

    cout << "\n--- Update Profile ---\n";
    cout << "Leave a field blank to keep the current value.\n";

    cout << "Current username: " << testUser.username << endl;
    cout << "New username: ";
    getline(cin, newValue);

    if (!newValue.empty()) {
        testUser.username = newValue;
    }

    cout << "Current email: " << testUser.email << endl;
    cout << "New email: ";
    getline(cin, newValue);

    if (!newValue.empty()) {
        testUser.email = newValue;
    }

    cout << "Current preferences: " << testUser.preferences << endl;
    cout << "New preferences: ";
    getline(cin, newValue);

    if (!newValue.empty()) {
        testUser.preferences = newValue;
    }

    cout << "Profile updated successfully.\n";
}
int main() {
    int choice;

    do {
        cout << "\n===== AI Smart Study App Backend Demo =====\n";
cout << "1. Register User Test\n";
cout << "2. Login\n";
cout << "3. Create Assignment\n";
cout << "4. View Assignments\n";
cout << "5. Delete Assignment\n";
cout << "6. Edit Assignment\n";
cout << "7. Mark Assignment Completed\n";
cout << "8. View Progress Analytics\n";
cout << "9. Update Profile\n";
cout << "10. Logout\n";
cout << "0. Exit\n";
cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUserDemo();
                break;

            case 2:
                login();
                break;

            case 3:
                if (isLoggedIn) {
                    createAssignment(currentUserId);
                } else {
                    cout << "Please log in first.\n";
                }
                break;

            case 4:
                if (isLoggedIn) {
                    viewAssignments(currentUserId);
                } else {
                    cout << "Please log in first.\n";
                }
                break;

            case 5:
                if (isLoggedIn) {
                    deleteAssignment(currentUserId);
                } else {
                    cout << "Please log in first.\n";
                }
                break;

            case 6:
    if (isLoggedIn) {
        editAssignment(currentUserId);
    } else {
        cout << "Please log in first.\n";
    }
    break;

case 7:
    if (isLoggedIn) {
        markAssignmentCompleted(currentUserId);
    } else {
        cout << "Please log in first.\n";
    }
    break;

case 8:
    if (isLoggedIn) {
        showProgressAnalytics(currentUserId);
    } else {
        cout << "Please log in first.\n";
    }
    break;

case 9:
    if (isLoggedIn) {
        updateProfile();
    } else {
        cout << "Please log in first.\n";
    }
    break;

case 10:
    if (isLoggedIn) {
        logout();
    } else {
        cout << "No user is currently logged in.\n";
    }
    break;

         case 0:
    cout << "Exiting program.\n";
    break;   
            default:
                cout << "Invalid option. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
