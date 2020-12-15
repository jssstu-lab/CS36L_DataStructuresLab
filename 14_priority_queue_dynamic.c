#include <stdio.h>
#include <stdlib.h>

#define QUEUE_INIT_CAPACITY 10

typedef struct {
    int *items;
    int fIdx, rIdx;
    int capacity;
} PriorityQueue;

void initQueue(PriorityQueue* q) {
    q->capacity = QUEUE_INIT_CAPACITY;
    q->fIdx = 0;
    q->rIdx = -1;

    q->items = (int*) malloc(q->capacity * sizeof(int));
}

void enqueue(PriorityQueue* q) {
    if (q->rIdx == q->capacity-1) {
        // Queue is full
        printf("Reallocating queue. \n");
        q->capacity *= 2;
        q->items = (int*) realloc(q->items, q->capacity * sizeof(int));
    }

    int item;
    printf("Enter element to enqueue: ");
    scanf("%d", &item);
    *(q->items + ++q->rIdx) = item;
}

void dequeue(PriorityQueue* q) {
    if (q->fIdx > q->rIdx) {
        printf("Queue is empty. \n");
        return;
    }

    int minIdx = 0, min = *q->items, i;
    for (i = q->fIdx; i <= q->rIdx; i++) {
        if (*(q->items + i) < min) {
            min = *(q->items + i);
            minIdx = i;
        }
    }

    for (i = minIdx; i < q->rIdx; i++)
        *(q->items + i) = *(q->items + i + 1);

    q->rIdx--;

    printf("Dequeued %d \n", min);
}


void display(PriorityQueue *q) {
    if (q->fIdx > q->rIdx) {
        // Queue is empty
        printf("Queue is empty. \n");
        return;
    }

    int i;
    for (i = q->fIdx; i <= q->rIdx; i++)
        printf("%d ", *(q->items + i));
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
                    display(&q);
                    break;
            case 2: dequeue(&q);
                    display(&q);
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