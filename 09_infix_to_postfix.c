#include <stdio.h>
#include <string.h>

#define MAX_STACKARR_SIZE 50
#define MAX_STRING_SIZE 200

typedef struct stack {
    int topIdx;
    char items[MAX_STACKARR_SIZE];
} Stack;

void push(Stack* s, char op) {
    if (s->topIdx == MAX_STACKARR_SIZE -1) {
        printf("Stack full. Stack overflow. \n");
        return;
    }
    s->items[++s->topIdx] = op;
}

char pop(Stack* s) {
    if (s->topIdx == -1) {
        printf("Stack empty. Stack underflow. \n");
        return -1;
    }
    return s->items[s->topIdx--];
}

char peek(Stack *s) {
    if (s->topIdx == -1) {
        printf("Stack empty. Stack underflow. \n");
        return -1;
    }
    return s->items[s->topIdx];
}

int isEmpty(Stack *s) {
    return s->topIdx == -1;
}

void initStack(Stack* s) {
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

void infixToPostfix(char infix[], char postfix[]) {
    Stack operatorStack;
    initStack(&operatorStack);

    int infixIdx = 0, postfixIdx = 0;
    char inputChar;
    while ((inputChar = infix[infixIdx]) != '\0') {
        if (isOperator(inputChar)) {
            if (isEmpty(&operatorStack) || (inputPrecedence(inputChar) > stackPrecedence(peek(&operatorStack)))) {
                push(&operatorStack, inputChar);
            } else {
                while (!isEmpty(&operatorStack) && (inputPrecedence(inputChar) < stackPrecedence(peek(&operatorStack))))
                    postfix[postfixIdx++] = pop(&operatorStack);
                push(&operatorStack, inputChar);
            }
        } else if (inputChar == ')') {
            while (peek(&operatorStack) != '(')
                postfix[postfixIdx++] = pop(&operatorStack);
            pop(&operatorStack); // discard (
        } else {
            postfix[postfixIdx++] = inputChar;
        }
        infixIdx++;
    }
    while (!isEmpty(&operatorStack))
        postfix[postfixIdx++] = pop(&operatorStack);

    postfix[postfixIdx] = '\0';
}

int main() {
    while (1) {
        char infix[MAX_STRING_SIZE], postfix[MAX_STRING_SIZE];
        printf("Enter infix expression (or 0 to exit) : ");
        scanf("%s", infix);
        if (strcmp(infix, "0") == 0)
            break;
        infixToPostfix(infix, postfix);
        printf("%s\n", postfix);
    }
    return 0;
}