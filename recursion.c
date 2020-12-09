#include <stdio.h>

int factorial(int n) {
    if (n == 0) return 1;
    return n*factorial(n-1);
}

int fibonacci(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;

    return fibonacci(n-1) + fibonacci(n-2);
}

int recursiveMin(int arr[], int n) {
    if (n == 1) return arr[0];

    int smallest = recursiveMin(arr, n-1);
    if (arr[n-1] < smallest)
        return arr[n-1];
    return smallest;
}

int recursieProduct(int arr[], int n) {
    if (n == 1) return arr[0];

    return arr[n-1] * recursieProduct(arr, n-1);
}

/*
 * Basis: when n = 1,
 * 		  Just move disc from start to end
 * Induction: 
 * 		  Assume toh(n-1, A, B, C) solves toh for n-1 discs
 * 		  Then we can solve n discs by:
 * 		  toh(n-1, A, C, B)
 * 		  move(A, C)
 * 		  toh(n-1, B, A, C)
 *
 */
void toh(int n, char source, char temp, char dest) {
    if (n == 1) {
        printf("Moving disc %d from %c to %c. \n", n, source, dest);
        return;
    }

    toh(n-1, source, dest, temp);
    printf("Moving disc %d from %c to %c. \n", n, source, dest);
    toh(n-1, temp, source, dest);
}

void printMenu() {
    printf("\n\n\n");
    printf("1. Factorial\n");
    printf("2. Fibonacci\n");
    printf("3. RecursiveMin\n");
    printf("4. RecursieProduct\n");
    printf("5. Tower of Hanoi\n");
    printf("6. Exit\n");
}

void inputArray(int arr[], int* n) {
    printf("Enter number of elements: ");
    scanf("%d", n);
    printf("Enter the elements: ");
    int i;
    for (i = 0; i < *n; i++) 
        scanf("%d", &arr[i]);
}

void main() {
    int n;
    int arr[10];
    int isRunning = 1;

    while (isRunning) {
        printMenu();
        int ch;
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch(ch) {
            case 1:
                printf("Enter n:");
                scanf("%d", &n);
                printf("factorial(%d) = %d\n", n, factorial(n));
                break;
            case 2:
                printf("Enter n:");
                scanf("%d", &n);
                printf("fibonacci(%d) = %d\n", n, fibonacci(n));
                break;
            case 3:
                inputArray(arr, &n);
                printf("recursiveMin = %d\n", recursiveMin(arr, n));
                break;
            case 4:
                inputArray(arr, &n);
                printf("recursieProduct = %d\n", recursieProduct(arr, n));
                break;
            case 5:
                printf("Enter n:");
                scanf("%d", &n);
                toh(n, 'A', 'B', 'C');
                break;
            case 6:
                isRunning = 0;
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
}