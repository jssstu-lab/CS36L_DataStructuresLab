#include <stdio.h>

#define MAX_QUEUE_ARR_SIZE 10

typedef struct {
    int items[MAX_QUEUE_ARR_SIZE];
    int ridx, fidx;
} Queue;

void initQueue(Queue *q) {
    q->ridx = -1;
    q->fidx = 0;
}

void enqueue(Queue *q) {
    if (q->ridx == MAX_QUEUE_ARR_SIZE-1) {
        // Queue is full
        printf("Queue is full. \n");
        return;
    }

    int item;
    printf("Enter element to enqueue: ");
    scanf("%d", &item);
    q->items[++q->ridx] = item;
}

void dequeue(Queue *q) {
    if (q->fidx > q->ridx) {
        // Queue is empty
        printf("Queue is empty. \n");
        return;
    }

    int item = q->items[q->fidx++];
    printf("Dequeued %d \n", item);

    if (q->fidx > q->ridx) {
        // reset front and rear "pointers"
        q->fidx = 0;
        q->ridx = -1;
    }
}

void display(Queue *q) {
    if (q->fidx > q->ridx) {
        // Queue is empty
        printf("Queue is empty. \n");
        return;
    }

    int i;
    for (i = q->fidx; i <= q->ridx; i++)
        printf("%d ", q->items[i]);
    printf("\n");
}

void printMenu() {
    printf("1. Enqueue \n");
    printf("2. Dequeue \n");
    printf("3. Display queue \n");
    printf("4. Exit \n");
}

int main() {
    Queue q;
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