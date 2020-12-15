#include <stdio.h>

#define MAX_QUEUE_ARR_SIZE 10

typedef struct {
    int items[MAX_QUEUE_ARR_SIZE];
    int fidx, ridx;
    int size;
} CircularQueue;

void initQueue(CircularQueue* q) {
    q->fidx = 0;
    q->ridx = -1;
    q->size = 0;
}

void enqueue(CircularQueue* q) {
    if (q->size == MAX_QUEUE_ARR_SIZE) {
        printf("Queue is full. \n");
        return;
    }

    int item;
    printf("Enter item to enqueue: ");
    scanf("%d", &item);

    q->items[++q->ridx % MAX_QUEUE_ARR_SIZE] = item;
    q->size++;
}

void dequeue(CircularQueue* q) {
    if (q->size == 0) {
        printf("Queue is empty. \n");
        return;
    }

    int item = q->items[q->fidx++ % MAX_QUEUE_ARR_SIZE];
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
        printf("%d ", q->items[(q->fidx + i) % MAX_QUEUE_ARR_SIZE]);
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
    return 0;
}