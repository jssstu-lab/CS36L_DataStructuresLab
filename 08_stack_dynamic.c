#include <stdio.h>
#include <stdlib.h>

#define INIT_STACK_CAPACITY 10

typedef struct stack {
    int topIdx;
    int capacity;
    int *items;
} Stack;

void push(Stack* s) {
    if (s->topIdx == s->capacity-1) {
        printf("Stack is full. Resizing stack \n");
        s->capacity = s->capacity * 2;
        s->items = (int*) realloc(s->items, s->capacity*sizeof(int));
    }

    int ele;
    printf("Enter element to push into stack: ");
    scanf("%d", &ele);

    *(s->items + ++s->topIdx) = ele;
}

int pop(Stack* s) {
    if (s->topIdx == -1) {
        printf("Stack is empty. Stack underflow. \n");
        return -1;
    }
    int popedEle = *(s->items + s->topIdx--);
    printf("Popped element : %d\n", popedEle);
    return popedEle;
}

int peek(Stack* s) {
    if (s->topIdx == -1) {
        printf("Stack is empty. \n");
        return -1;
    }
    printf("Top of the stack has the element : %d\n", *(s->items + s->topIdx));
    return *(s->items + s->topIdx);
}

void display(Stack *s) {
    if (s->topIdx == -1) {
        printf("Stack is empty. \n");
        return;
    }

    int i;
    printf("top = %d, capacity = %d\n", s->topIdx, s->capacity);
    for (i = 0; i <= s->topIdx; i++)
        printf("%d ", *(s->items + i));
    printf("\n");
}

void initStack(Stack *s) {
    s->topIdx = -1;
    s->capacity = INIT_STACK_CAPACITY;
    s->items = (int*) malloc(s->capacity * sizeof(int));
}

void deleteStack(Stack *s) {
    free(s->items);
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
    deleteStack(&s);
    return 0;
}