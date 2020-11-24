/*
 * 04 November 2020
 * Program to create a structure to represent time and create functions to
 * a) Read time
 * b) Display time
 * c) Update Time
 * d) Add two times
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _time {
    int hr;
    int min;
    int sec;
} Time;

void ReadTime(Time* t) {
    printf("Enter Hrs: ");
    scanf("%d", &t->hr);
    printf("Enter Mins: ");
    scanf("%d", &t->min);
    printf("Enter Secs: ");
    scanf("%d", &t->sec);

    // Correct in case of invalid input
    t->min += t->sec / 60;
    t->sec %= 60;
    t->hr += t->min / 60;
    t->min %= 60;
}

void DisplayTime(Time t) {
    printf("The time is %d:%d:%d \n", t.hr, t.min, t.sec);
}

void UpdateTime(Time* t) {
    // Increment t by 1 second
    t->sec++;
    t->min += t->sec / 60;
    t->sec %= 60;
    t->hr += t->min / 60;
    t->min %= 60;
}

Time* addTime(Time t1, Time t2) {
    Time* addedTime = (Time*) malloc(sizeof(Time));
    addedTime->sec = t1.sec + t2.sec;
    addedTime->min = t1.min + t2.min;
    addedTime->hr = t1.hr + t2.hr;

    // Correct invalid time
    addedTime->min += addedTime->sec / 60;
    addedTime->sec %= 60;
    addedTime->hr += addedTime->min / 60;
    addedTime->min %= 60;

    return addedTime;
}

int main() {
    Time t1;
    Time t2;
    Time* tempTime;
    int isRunning = 1;
    while (isRunning) {
        printf("\n\n\n0. Exit \n");
        printf("1. Read time t1\n");
        printf("2. Read time t2\n");
        printf("3. Display time t1\n");
        printf("4. Display time t2\n");
        printf("5. Update t1\n");
        printf("6. Update t2\n");
        printf("7. Add t1 and t2\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 0:
                isRunning = 0;
                break;
            case 1:
                ReadTime(&t1);
                break;
            case 2:
                ReadTime(&t2);
                break;
            case 3:
                DisplayTime(t1);
                break;
            case 4:
                DisplayTime(t2);
                break;
            case 5:
                UpdateTime(&t1);
                break;
            case 6:
                UpdateTime(&t2);
                break;
            case 7:
                tempTime = addTime(t1, t2);
                printf("Added time : ");
                DisplayTime(*tempTime);
                free(tempTime);
                break;
        }
    }

    return 0;
}
