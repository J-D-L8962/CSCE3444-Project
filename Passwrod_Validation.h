#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sodium.h>// Requires the libsodium library installed on your system

//Validating password rules
bool validate_password(const char *password) 
{
    int length = strlen(password);
    // Initialize flags to track character categories
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    //Enforce minimum length restriction
    if (length < 8) 
    {
        printf("Validation Failed: Password must be at least 8 characters long.\n");
        return false;
    }

    // Iterate through each character in the string
    for (int i = 0; i < length; i++) {
        if (isupper((unsigned char)password[i])) 
        {
            has_upper = true;
        } else if (islower((unsigned char)password[i])) 
        {
            has_lower = true;
        } else if (isdigit((unsigned char)password[i])) 
        {
            has_digit = true;
        } else if (ispunct((unsigned char)password[i])) 
        {
            has_special = true;
        }
    }

    // Evaluate flags and output targeted error messages
    if (!has_upper) 
    {
        printf("Validation Failed: Missing an uppercase letter.\n");
        return false;
    }
    if (!has_lower) 
    {
        printf("Validation Failed: Missing a lowercase letter.\n");
        return false;
    }
    if (!has_digit) 
    {
        printf("Validation Failed: Missing a number.\n");
        return false;
    }
    if (!has_special) 
    {
        printf("Validation Failed: Missing a special character (e.g., !, @, #, $).\n");
        return false;
    }

    return true;
}

//Securely hash the password using Argon2id
bool hash_password(const char *plaintext_password, char *output_buffer) 
{
    // crypto_pwhash_str automatically creates a salt, hashes, and formats the output
    int result = crypto_pwhash_str
    (
        output_buffer, 
        plaintext_password, 
        strlen(plaintext_password),
        crypto_pwhash_OPSLIMIT_SENSITIVE, 
        crypto_pwhash_MEMLIMIT_SENSITIVE
    );

    // Returns true (1) if hashing succeeds, false (0) if it fails
    return (result == 0);
}