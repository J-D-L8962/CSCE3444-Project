//ani
#ifndef STUDYPLANNER_H
#define STUDYPLANNER_H

#include <stdio.h>

void generate_study_plan(int availableHours, int upcomingExams)
{
    printf("\n--- AI Study Plan ---\n");

    if(upcomingExams >= 3)
    {
        printf("Recommendation:\n");
        printf("- 3 hours for exam review\n");
        printf("- 2 hours for assignments\n");
    }
    else
    {
        printf("Recommendation:\n");
        printf("- Balance homework and revision.\n");
    }

    printf("Available Hours: %d\n", availableHours);
}

#endif
