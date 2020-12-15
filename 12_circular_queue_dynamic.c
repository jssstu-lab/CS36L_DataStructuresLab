#include <stdio.h>
#include <stdlib.h>

#define QUEUE_INIT_CAPACITY 10

typedef struct {
    int *items;
    int fidx, ridx;
    int size;
    int capacity;
} CircularQueue;

void initQueue(CircularQueue* q) {
    q->capacity = QUEUE_INIT_CAPACITY;
    q->fidx = 0;
    q->ridx = -1;
    q->size = 0;

    q->items = (int*) malloc(q->capacity * sizeof(int));
}

void deleteQueue(CircularQueue *q) {
    free(q->items);
}

void enqueue(CircularQueue* q) {
    if (q->size == q->capacity) {
        printf("Reallocating queue. \n");
        q->capacity *= 2;
        q->items = (int*) realloc(q->items, q->capacity * sizeof(int));
    }

    int item;
    printf("Enter item to enqueue: ");
    scanf("%d", &item);

    *(q->items + (++q->ridx % q->capacity)) = item;
    q->size++;
}

void dequeue(CircularQueue* q) {
    if (q->size == 0) {
        printf("Queue is empty. \n");
        return;
    }

    int item = *(q->items + (q->fidx++ % q->capacity));
    printf("Dequeued %d\n", item);
    q->size--;
}

void display(CircularQueue* q) {
    if (q->size == 0) {
        printf("Queue is empty. \n");
        return;
    }

    int i;
    for (i = 0; i < q->size; i++) {
        printf("%d ", *(q->items + ((q->fidx + i) % q->capacity)));
    }
    printf("\n");
}

void printMenu() {
    printf("1. Enqueue \n");
    printf("2. Dequeue \n");
    printf("3. Display queue \n");
    printf("4. Exit \n");
}

int main() {
    CircularQueue q;
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
    deleteQueue(&q);
    return 0;
}