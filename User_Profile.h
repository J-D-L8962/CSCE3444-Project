//ani
#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <stdio.h>

typedef struct
{
    char username[50];
    char email[100];
    char preferredStudyTime[30];
    int notificationsEnabled;
} UserProfile;

void display_profile(UserProfile user)
{
    printf("\n----- USER PROFILE -----\n");
    printf("Username: %s\n", user.username);
    printf("Email: %s\n", user.email);
    printf("Preferred Study Time: %s\n", user.preferredStudyTime);

    if(user.notificationsEnabled)
        printf("Notifications: Enabled\n");
    else
        printf("Notifications: Disabled\n");

    printf("------------------------\n");
}

#endif
