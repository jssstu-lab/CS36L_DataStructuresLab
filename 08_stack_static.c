#include <stdio.h>

#define MAX_STACKARR_SIZE 10

typedef struct stack {
    int topIdx;
    int items[MAX_STACKARR_SIZE];
} Stack;

void push(Stack* s) {
    if (s->topIdx == MAX_STACKARR_SIZE-1) {
        printf("Stack is full. Stack overflow. \n");
        return;
    }

    int ele;
    printf("Enter element to push into stack: ");
    scanf("%d", &ele);

    s->items[++s->topIdx] = ele;
}

int pop(Stack* s) {
    if (s->topIdx == -1) {
        printf("Stack is empty. Stack underflow. \n");
        return -1;
    }
    int popedEle = s->items[s->topIdx--];
    printf("Popped element : %d\n", popedEle);
    return popedEle;
}

int peek(Stack* s) {
    if (s->topIdx == -1) {
        printf("Stack is empty. \n");
        return -1;
    }
    printf("Top of the stack has the element : %d\n", s->items[s->topIdx]);
    return s->items[s->topIdx];
}

void display(Stack *s) {
    if (s->topIdx == -1) {
        printf("Stack is empty. \n");
        return;
    }

    printf("top = %d\n", s->topIdx);
    int i;
    for (i = 0; i <= s->topIdx; i++)
        printf("%d ", s->items[i]);
    printf("\n");
}

void initStack(Stack *s) {
    s->topIdx = -1;
}

void printMenu() {
    printf("\n\n\n\n\n\n");
    printf("1. Display Stack\n");
    printf("2. Push elements into stack\n");
    printf("3. Pop elements from stack\n");
    printf("4. Peek top of stack\n");
    printf("5. Exit\n");
}

int main() {
    Stack s;
    initStack(&s);

    int isRunning = 1;
    while (isRunning) {
        printMenu();
        int ch;
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1:
                display(&s);
                break;
            case 2:
                push(&s);
                display(&s);
                break;
            case 3:
                pop(&s);
                display(&s);
                break;
            case 4:
                peek(&s);
                display(&s);
                break;
            case 5:
                isRunning = 0;
                break;
            default:
                printf("Invalid choice. \n");
        }
    }
    return 0;
}