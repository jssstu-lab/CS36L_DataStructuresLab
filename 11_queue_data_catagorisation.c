#include <stdio.h>

#define MAX_QUEUE_ARR_SIZE 50

typedef struct {
    int items[MAX_QUEUE_ARR_SIZE];
    int ridx, fidx;
} Queue;

void initQueue(Queue *q) {
    q->ridx = -1;
    q->fidx = 0;
}

void enqueue(Queue *q, int i) {
    if (q->ridx == MAX_QUEUE_ARR_SIZE-1) {
        // Queue is full
        printf("Queue is full. \n");
        return;
    }

    q->items[++q->ridx] = i;
}

int dequeue(Queue *q) {
    if (q->fidx > q->ridx) {
        // Queue is empty
        printf("Queue is empty. \n");
        return;
    }

    int item = q->items[q->fidx++];

    if (q->fidx > q->ridx) {
        // reset front and rear "pointers"
        q->fidx = 0;
        q->ridx = -1;
    }

    return item;
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
    Queue q[4];
    int i;
    for (i = 0; i < 4; i++)
        initQueue(&q[i]);

    int d;
    printf("-1 to terminate: \n");
    do {
        scanf("%d", &d);
        if (d == -1) break;
        if (d < 10) {
            enqueue(&q[0], d);
        } else if (d <= 19) {
            enqueue(&q[1], d);
        } else if (d <= 29) {
            enqueue(&q[2], d);
        } else {
            enqueue(&q[3], d);
        }
    } while (1);

    for (i = 0; i < 4; i++) {
        printf("Catogory %d: ", i+1);
        display(&q[i]);
    }
    return 0;
}