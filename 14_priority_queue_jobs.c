#include <stdio.h>

#define MAX_QUEUE_ARR_SIZE 10
#define MAX_STR_SIZE 50

typedef struct {
    int jobId;
    char jobName[MAX_STR_SIZE];
    int priority;
} Job;

void printJob(Job j) {
    printf("* * * * * * * * * * * * * * * * * * * * * \n");
    printf("Job id : %d\n", j.jobId);
    printf("Job name: %s\n", j.jobName);
    printf("Job priority: %d\n", j.priority);
    printf("* * * * * * * * * * * * * * * * * * * * * \n\n\n");
}

typedef struct {
    Job jobs[MAX_QUEUE_ARR_SIZE];
    int fIdx, rIdx;
} PriorityQueue;

void initQueue(PriorityQueue* q) {
    q->fIdx = 0;
    q->rIdx = -1;
}

void enqueue(PriorityQueue* q) {
    if (q->rIdx == MAX_QUEUE_ARR_SIZE-1) {
        // Queue is full
        printf("Queue is full. \n");
        return;
    }

    q->rIdx++;
    printf("Enter job id: ");
    scanf("%d", &q->jobs[q->rIdx].jobId);
    printf("Enter job name: ");
    scanf("%s", q->jobs[q->rIdx].jobName);
    printf("Enter job priority: ");
    scanf("%d", &q->jobs[q->rIdx].priority);
}

void dequeue(PriorityQueue* q) {
    if (q->fIdx > q->rIdx) {
        printf("Queue is empty. \n");
        return;
    }

    int minIdx = 0, min = q->jobs[0].priority, i;
    for (i = q->fIdx; i <= q->rIdx; i++) {
        if (q->jobs[i].priority < min) {
            min = q->jobs[i].priority;
            minIdx = i;
        }
    }

    Job minJob = q->jobs[minIdx];

    for (i = minIdx; i < q->rIdx; i++)
        q->jobs[i] = q->jobs[i+1];

    q->rIdx--;

    printf("Dequeued job:\n");
    printJob(minJob);
}


void display(PriorityQueue *q) {
    if (q->fIdx > q->rIdx) {
        // Queue is empty
        printf("Queue is empty. \n");
        return;
    }

    int i;
    for (i = q->fIdx; i <= q->rIdx; i++)
        printJob(q->jobs[i]);
    printf("\n");
}

void printMenu() {
    printf("1. Enqueue \n");
    printf("2. Dequeue \n");
    printf("3. Display queue \n");
    printf("4. Exit \n");
}

int main() {
    PriorityQueue q;
    initQueue(&q);

    int isRunning = 1;
    while (isRunning) {
        printMenu();
        printf("Enter your choice: ");
        int ch;
        scanf("%d", &ch);
        switch(ch) {
            case 1: enqueue(&q);
                    break;
            case 2: dequeue(&q);
                    break;
            case 3: display(&q);
                    break;
            case 4: isRunning = 0;
                    break;
            default:
                    printf("Invalid choice. \n");
        }
    }
    return 0;
}