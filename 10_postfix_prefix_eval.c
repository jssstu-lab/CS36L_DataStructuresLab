#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_STACKARR_SIZE 50
#define MAX_STRING_SIZE 200

typedef struct stack {
    int topIdx;
    double items[MAX_STACKARR_SIZE];
} Stack;

void push(Stack* s, double op) {
    if (s->topIdx == MAX_STACKARR_SIZE -1) {
        printf("Stack full. Stack overflow. \n");
        return;
    }
    s->items[++s->topIdx] = op;
}

double pop(Stack* s) {
    if (s->topIdx == -1) {
        printf("Stack empty. Stack underflow. \n");
        return -1;
    }
    return s->items[s->topIdx--];
}

int isEmpty(Stack *s) {
    return s->topIdx == -1;
}

void initStack(Stack* s) {
    s->topIdx = -1;
}

int isOperator(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '$'; 
}

double compute(double operand1, double operand2, char op) {
    switch(op) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': 
                if (operand2 != 0) 
                    return operand1 / operand2;
                else {
                    printf("Division by zero. \n");
                    return 0;
                }
        case '^': 
        case '$': return pow(operand1, operand2);
    }
}

void postfixEvaluate(char postfix[]) {
    Stack operandStack;
    initStack(&operandStack);

    int postfixIdx = 0;
    char inputChar;
    while ((inputChar = postfix[postfixIdx]) != '\0') {
        if (isOperator(inputChar)) {
            double op2 = pop(&operandStack);
            double op1 = pop(&operandStack);
            push(&operandStack, compute(op1, op2, inputChar));
        } else {
            push(&operandStack, inputChar - '0');
        }
        postfixIdx++;
    }

    double result = pop(&operandStack);
    if (!isEmpty(&operandStack)) {
        printf("Invalid expression. \n");
        return;
    }
    printf("Result = %f\n", result);
}

void prefixEvaluate(char prefix[]) {
    Stack operandStack;
    initStack(&operandStack);

    int prefixIdx = strlen(prefix) - 1;
    char inputChar;
    while (prefixIdx >= 0) {
        inputChar = prefix[prefixIdx];
        if (isOperator(inputChar)) {
            double op1 = pop(&operandStack);
            double op2 = pop(&operandStack);
            push(&operandStack, compute(op1, op2, inputChar));
        } else {
            push(&operandStack, inputChar - '0');
        }
        prefixIdx--;
    }

    double result = pop(&operandStack);
    if (!isEmpty(&operandStack)) {
        printf("Invalid expression. \n");
        return;
    }
    printf("Result = %f\n", result);
}

void printMenu() {
    printf("1. Evaluate postfix expression. \n");
    printf("2. Evaluate prefix expression \n");
    printf("3. Exit \n");
}

int main() {
    char inputStr[MAX_STRING_SIZE];
    int isRunning = 1;
    while (isRunning) {
        int ch;
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &ch);
        
        switch(ch) {
            case 1:
                printf("Enter expression: ");
                scanf("%s", inputStr);
                postfixEvaluate(inputStr);
                break;
            case 2:
                printf("Enter expression: ");
                scanf("%s", inputStr);
                prefixEvaluate(inputStr);
                break;
            case 3:
                isRunning = 0;
                break;
        }
    }
}