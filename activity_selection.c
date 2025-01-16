#include <stdio.h>
#include <stdlib.h>

// Struct to represent an activity with start and finish times
typedef struct {
    int start;
    int finish;
} Activity;

// Function to sort activities by their finish times
void sortByFinishTime(Activity activities[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (activities[i].finish > activities[j].finish) {
                Activity temp = activities[i];
                activities[i] = activities[j];
                activities[j] = temp;
            }
        }
    }
}

// Function to print the selected activities that can be performed by a single person
void printMaxActivities(Activity activities[], int n) {
    int i = 0;
    printf("Selected activities are:\n");
    printf("Activity (%d, %d)\n", activities[i].start, activities[i].finish); // Select the first activity

    // Consider the rest of the activities
    for (int j = 1; j < n; j++) {
        
        // If this activity starts after the last selected activity finishes, select it
        if (activities[j].start >= activities[i].finish) {
            printf("Activity (%d, %d)\n", activities[j].start, activities[j].finish);
            i = j;
        
            
        }
    }
}

int main() {
    int n;
    printf("Enter the number of activities: ");
    scanf("%d", &n);

    // Dynamically allocate memory for activities
    Activity *activities = (Activity *)malloc(n * sizeof(Activity));

    if (activities == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Take input for start and finish times for each activity
    for (int i = 0; i < n; i++) {
        printf("Enter start and finish time for activity %d (format: start finish): ", i + 1);
        scanf("%d %d", &activities[i].start, &activities[i].finish);
    }


    sortByFinishTime(activities, n);
    
    printMaxActivities(activities, n);

    free(activities);

    return 0;
}
