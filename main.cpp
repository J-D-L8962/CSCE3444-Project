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