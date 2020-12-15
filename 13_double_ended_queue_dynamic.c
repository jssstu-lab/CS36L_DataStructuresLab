#include <stdio.h>
#include <stdlib.h>

#define QUEUE_INIT_CAPACITY 10

typedef struct {
    int *items;
    int fIdx, rIdx;
    int capacity;
} DEQueue;

void initQueue(DEQueue* q) {
    q->capacity = QUEUE_INIT_CAPACITY;
    q->fIdx = 0;
    q->rIdx = -1;

    q->items = (int*) malloc(q->capacity * sizeof(int));
}

void deleteQueue(DEQueue* q) {
    free(q->items);
}

void insertFront(DEQueue* q) {
    if (q->fIdx <= q->rIdx && q->fIdx == 0) {
        printf("This operation cannot be performed. \n");
        return;
    }

    int item;
    printf("Enter item to insert at front: ");
    scanf("%d", &item);
    if (q->fIdx == 0) {
        // Empty queue. Just rare insert
        *(q->items + ++q->rIdx) = item;
    } else {
        *(q->items + --q->fIdx) = item;
    }
}

void deleteFront(DEQueue* q) {
    if (q->fIdx > q->rIdx) {
        printf("Queue is empty. \n");
        return;
    }

    int item = *(q->items + q->fIdx++);
    printf("Deleted %d from front. \n", item);

    if (q->fIdx > q->rIdx) {
        q->fIdx = 0;
        q->rIdx = -1;
    }
}

void insertRear(DEQueue* q) {
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

void deleteRear(DEQueue* q) {
    if (q->fIdx > q->rIdx) {
        printf("Queue is empty. \n");
        return;
    }

    int item = *(q->items + q->rIdx--);
    printf("Deleted %d from rear. \n", item);

    if (q->fIdx > q->rIdx) {
        q->fIdx = 0;
        q->rIdx = -1;
    }
}

void display(DEQueue *q) {
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
    printf("1. InsertFront\n");
    printf("2. DeleteFront\n");
    printf("3. InsertRear\n");
    printf("4. DeleteRear\n");
    printf("5. Display\n");
    printf("6. Exit\n");
}

int main() {
    DEQueue q;
    initQueue(&q);

    int isRunning = 1;
    while (isRunning) {
        printMenu();
        printf("Enter your choice: ");
        int ch;
        scanf("%d", &ch);
        switch(ch) {
            case 1: insertFront(&q);
                    display(&q);
                    break;
            case 2: deleteFront(&q);
                    display(&q);
                    break;
            case 3: insertRear(&q);
                    display(&q);
                    break;
            case 4: deleteRear(&q);
                    display(&q);
                    break;
            case 5: display(&q);
                    break;
            case 6: isRunning = 0;
                    break;
            default:
                    printf("Invalid choice. \n");
        }
    }
    deleteQueue(&q);
    return 0;
}