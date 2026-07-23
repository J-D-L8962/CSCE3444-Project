#ifndef PASSWORD_VALIDATION_H
#define PASSWORD_VALIDATION_H

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool validatePassword(const string& password) {
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    if (password.length() < 8) {
        cout << "Password must be at least 8 characters long.\n";
        return false;
    }

    for (char ch : password) {
        if (isupper(ch)) hasUpper = true;
        else if (islower(ch)) hasLower = true;
        else if (isdigit(ch)) hasDigit = true;
        else if (ispunct(ch)) hasSpecial = true;
    }

    if (!hasUpper) {
        cout << "Password must contain at least one uppercase letter.\n";
        return false;
    }

    if (!hasLower) {
        cout << "Password must contain at least one lowercase letter.\n";
        return false;
    }

    if (!hasDigit) {
        cout << "Password must contain at least one number.\n";
        return false;
    }

    if (!hasSpecial) {
        cout << "Password must contain at least one special character.\n";
        return false;
    }

    return true;
}

#endif