#ifndef ASSIGNMENT_CREATION_DB_INTEGRATION_H
#define ASSIGNMENT_CREATION_DB_INTEGRATION_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Assignment {
    int id;
    int userId;
    string title;
    string course;
    string dueDate;
    string priority;
    string notes;
};

vector<Assignment> assignments;

void createAssignment(int userId) {
    Assignment newAssignment;

    newAssignment.id = assignments.size() + 1;
    newAssignment.userId = userId;

    cin.ignore();

    cout << "Enter assignment title: ";
    getline(cin, newAssignment.title);

    cout << "Enter course: ";
    getline(cin, newAssignment.course);

    cout << "Enter due date (YYYY-MM-DD): ";
    getline(cin, newAssignment.dueDate);

    cout << "Enter priority (High/Medium/Low): ";
    getline(cin, newAssignment.priority);

    cout << "Enter notes: ";
    getline(cin, newAssignment.notes);

    assignments.push_back(newAssignment);

    cout << "\nAssignment created and stored successfully.\n";
}

void viewAssignments(int userId) {
    cout << "\n--- Your Assignments ---\n";

    bool found = false;

    for (const Assignment& assignment : assignments) {
        if (assignment.userId == userId) {
            found = true;
            cout << "ID: " << assignment.id << endl;
            cout << "Title: " << assignment.title << endl;
            cout << "Course: " << assignment.course << endl;
            cout << "Due Date: " << assignment.dueDate << endl;
            cout << "Priority: " << assignment.priority << endl;
            cout << "Notes: " << assignment.notes << endl;
            cout << "------------------------\n";
        }
    }

    if (!found) {
        cout << "No assignments found.\n";
    }
}

void deleteAssignment(int userId) {
    int assignmentId;
    char confirm;

    cout << "Enter assignment ID to delete: ";
    cin >> assignmentId;

    cout << "Are you sure you want to delete this assignment? (Y/N): ";
    cin >> confirm;

    if (confirm != 'Y' && confirm != 'y') {
        cout << "Deletion cancelled.\n";
        return;
    }

    for (auto it = assignments.begin(); it != assignments.end(); ++it) {
        if (it->id == assignmentId && it->userId == userId) {
            assignments.erase(it);
            cout << "Assignment deleted successfully.\n";
            return;
        }
    }

    cout << "Assignment not found or does not belong to this user.\n";
}

#endif