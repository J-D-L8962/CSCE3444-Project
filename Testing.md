# Functional Testing

## Registration Testing
Expected Result: User enters account information and a strong password.

Actual Result: Password validation checks for length, uppercase letters, lowercase letters, numbers, and special characters.

Status: PASS

---

## Login Testing
Expected Result: User logs in with valid credentials.

Actual Result: Test user can log in using test@unt.edu and Password123!.

Status: PASS

---

## Logout Testing
Expected Result: User session ends after logout.

Actual Result: User ID is cleared and logged-in status is set to false.

Status: PASS

---

## Assignment Creation Testing
Expected Result: User can create an assignment with title, course, due date, priority, and notes.

Actual Result: Assignment is stored in the assignment list.

Status: PASS

---

## Assignment Retrieval Testing
Expected Result: User can view only their own assignments.

Actual Result: Assignments are displayed based on the current logged-in user ID.

Status: PASS

---

## Assignment Deletion Testing
Expected Result: User receives a confirmation prompt before deleting an assignment.

Actual Result: Assignment is deleted only if the user confirms with Y.

Status: PASS