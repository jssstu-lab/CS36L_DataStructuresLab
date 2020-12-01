#include <stdio.h>
#include <string.h>

#define MAX_STACKARR_SIZE 50
#define MAX_STRING_SIZE 200

typedef struct stack {
    int topIdx;
    char items[MAX_STACKARR_SIZE][MAX_STRING_SIZE];
} Stack;

void push(Stack* s, char op[]) {
    if (s->topIdx == MAX_STACKARR_SIZE -1) {
        printf("Stack full. Stack overflow. \n");
        return;
    }
    ++s->topIdx;
    strcpy(s->items[s->topIdx], op);
}

void pop(Stack* s, char out[]) {
    if (s->topIdx == -1) {
        printf("Stack empty. Stack underflow. \n");
        return;
    }
    if (out != NULL) strcpy(out, s->items[s->topIdx--]);
    else s->topIdx--;
}

char* peek(Stack *s) {
    if (s->topIdx == -1) {
        printf("Stack empty. Stack underflow. \n");
        return NULL;
    }
    return s->items[s->topIdx];
}

int isEmpty(Stack *s) {
    return s->topIdx == -1;
}

int initStack(Stack* s) {
    s->topIdx = -1;
}

int isOperator(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '$' || op == '('; 
}

int inputPrecedence(char op) {
    switch(op) {
        case '(':
            return 7;
        case '^':
        case '$':
            return 6;
        case '*':
        case '/':
            return 3;
        case '+':
        case '-':
            return 1;
    }
}

int stackPrecedence(char op) {
    switch(op) {
        case '^':
        case '$':
            return 5;
        case '*':
        case '/':
            return 4;
        case '+':
        case '-':
            return 2;
        case '(':
            return 0;
    }
}

void combineAndPush(Stack* operandStack, Stack* operatorStack) {
    char oprand1[MAX_STRING_SIZE], oprand2[MAX_STRING_SIZE], op[MAX_STRING_SIZE];
    pop(operandStack, oprand2);
    pop(operatorStack, op);
    pop(operandStack, oprand1);
    strcat(oprand1, oprand2);
    strcat(op, oprand1);
    push(operandStack, op);
}

void infixToPrefix(char infix[], char prefix[]) {
    Stack operatorStack, operandStack;
    initStack(&operatorStack);
    initStack(&operandStack);

    int infixIdx = 0;
    char inputChar;
    while ((inputChar = infix[infixIdx]) != '\0') {
        if (isOperator(inputChar)) {
            if (isEmpty(&operatorStack) || (inputPrecedence(inputChar) > stackPrecedence(peek(&operatorStack)[0]))) {
                char opStr[] = " ";
                opStr[0] = inputChar;
                push(&operatorStack, opStr);
            } else {
                while (!isEmpty(&operatorStack) && (inputPrecedence(inputChar) < stackPrecedence(peek(&operatorStack)[0]))) {
                    combineAndPush(&operandStack, &operatorStack);
                }
                char opStr[] = " ";
                opStr[0] = inputChar;
                push(&operatorStack, opStr);
            }
        } else if (inputChar == ')') {
            while (peek(&operatorStack)[0] != '(') {
                combineAndPush(&operandStack, &operatorStack);
            }
            pop(&operatorStack, NULL); // discard (
        } else {
            char oprndStr[] = " ";
            oprndStr[0] = inputChar;
            push(&operandStack, oprndStr);
        }
        infixIdx++;
    }
    while (!isEmpty(&operatorStack) && !isEmpty(&operandStack)) {
        combineAndPush(&operandStack, &operatorStack);
    }

    pop(&operandStack, prefix);
}

int main() {
    while (1) {
        char infix[MAX_STRING_SIZE], prefix[MAX_STRING_SIZE];
        printf("Enter infix expression (or 0 to exit) : ");
        scanf("%s", infix);
        if (strcmp(infix, "0") == 0)
            break;
        infixToPrefix(infix, prefix);
        printf("%s\n", prefix);
    }
    return 0;
}