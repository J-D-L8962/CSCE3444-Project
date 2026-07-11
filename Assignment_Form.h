//ani
#ifndef ASSIGNMENTFORM_H
#define ASSIGNMENTFORM_H

#include <stdio.h>

typedef struct
{
    char title[100];
    char dueDate[30];
    int priority;
} Assignment;

void create_assignment_form()
{
    Assignment assignment;

    printf("Assignment Title: ");
    scanf(" %[^\n]", assignment.title);

    printf("Due Date: ");
    scanf("%s", assignment.dueDate);

    printf("Priority (1-5): ");
    scanf("%d",&assignment.priority);

    printf("\nAssignment Saved\n");
}

#endif
