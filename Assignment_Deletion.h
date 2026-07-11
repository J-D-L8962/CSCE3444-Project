//ani
#ifndef ASSIGNMENTDELETION_H
#define ASSIGNMENTDELETION_H

#include <stdio.h>

int confirm_assignment_delete()
{
    int option;

    printf("\nDelete Assignment?\n");
    printf("1. Yes\n");
    printf("2. No\n");

    scanf("%d",&option);

    if(option==1)
    {
        printf("Assignment deleted.\n");
        return 1;
    }

    printf("Deletion cancelled.\n");
    return 0;
}

#endif
