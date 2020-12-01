#include <stdio.h>

#define MAX_ARRAY_SIZE 10
int a[10];

// Funtion prototypes
void read(int[]);
void display(int[]);
void insert(int[]);
void delete(int[]);
void insert_by_order(int[]);
void delete_by_element(int[]);

// Global variables
int size = 0;

int main() {
    int isRunning = 1;

    int A[MAX_ARRAY_SIZE];

    while (isRunning) {
        printf("\n\n\nProgram to perform operations on an array: \n");
        printf("-------------------------------------------\n");
        printf("1. Read elements into array\n");
        printf("2. Display elements in array\n");
        printf("3. Insert element into array at some position\n");
        printf("4. Delete element from array at some position\n");
        printf("5. Insert element by order\n");
        printf("6. Delete element by value\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");       
        unsigned int choice;
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                read(A);
                break;
            case 2:
                display(A);
                break;
            case 3:
                insert(A);
                display(A);
                break;
            case 4:
                delete(A);
                display(A);
                break;
            case 5:
                insert_by_order(A);
                display(A);
                break;
            case 6:
                delete_by_element(A);
                display(A);
                break;
            case 7:
                printf("Goodbye!\n");
                isRunning = 0;
                break;
            default:
                printf("Invalid option.\n");
                isRunning = 0;
                break;
        }
    }
    return 0;
}

// Function to read integers into the array
void read(int A[]) {
    int n, i;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    if (n >= MAX_ARRAY_SIZE) {
        printf("Number of elements is greater than maximum array size. \n");
        printf("Cannot read elements\n");
        return;
    }

    size = n;

    printf("Enter the elements: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
}

// Function to display the elements of an array in a presentable form
void display(int A[]) {
    if (size == 0) {
        printf("The array is empty! \n");
    } else {
        int i;
        printf("A[] = [%d ", A[0]);
        for (i = 1; i < size; i++) {
            printf(",%d ", A[i]);
        }
        printf("]\n");
    }
}

// Function to insert elements to any position in an array.
void insert(int A[]) {
    if (size == MAX_ARRAY_SIZE) {
        printf("Array is full. \n");
        return;
    } else {
        int pos, ele;
        printf("Enter the position to insert array into: ");
        scanf("%d", &pos);
        printf("Enter the element to insert into array: ");
        scanf("%d", &ele);
        if (pos >= 1 && pos <= size+1) {
            int i;
            for (i = size; i >= pos; i--)
                A[i] = A[i-1];
            A[i] = ele;
            size++;
        } else {
            printf("Invalid position. Cannot insert. \n");
            return;
        }
    }
}

void delete(int A[]) {
    if (size == 0) {
        printf("Array is empty. Cannot delete.\n");
        return;
    } else {
        int pos;
        printf("Enter the position of the element to be deleted: ");
        scanf("%d", &pos);
        if (pos >= 1 && pos <= size) {
            int i;
            for (i = pos - 1; i < size - 1; i++) {
                A[i] = A[i+1];
            }
            size--;
        } else {
            printf("Invalid position. Cannot delete. \n");
            return;
        }
    }
}

void insert_by_order(int A[]) {
    if (size == MAX_ARRAY_SIZE) {
        printf("Array is full. \n");
        return;
    } else {
        int ele, i;
        printf("Enter the element to be inserted in order: ");
        scanf("%d", &ele);
        for (i = size - 1; i >= 0 && A[i] > ele; i--)
            A[i+1] = A[i];
        A[i+1] = ele;
        size++;
    }
}

void delete_by_element(int A[]) {
    if (size == 0) {
        printf("Array is empty. Cannot delete. \n");
        return;
    } else {
        int i, ele;
        printf("Enter the element to be delete: ");
        scanf("%d", &ele);
        for (i = 0; i < size && A[i] != ele; i++);
        if (i == size) {
            printf("Element not found in the list. Cannot delete \n");
            return;
        } else {
            printf("%d is deleted from position %d.\n", ele, i);
            for (; i < size - 1; i++) {
                A[i] = A[i+1];
            }
            size--;
        }
    }
}