#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node* link;
};

typedef struct node* Node;

int NE = 0;

void display(Node first) {
    if (first == NULL) {
        printf("List is empty. \n");
        return;
    }

    while (first != NULL) {
        printf("%d ", first->info);
        first = first->link;
    }
    printf("\n");
}

Node insertFront(Node first) {
    NE++;
    Node newNode = (Node) malloc(sizeof(struct node));
    printf("Enter element to be inserted: ");
    scanf("%d", &newNode->info);
    newNode->link = first;
    return newNode;
}

Node insertRear(Node first) {
    NE++;
    Node newNode = (Node) malloc(sizeof(struct node));
    printf("Enter element to be inserted: ");
    scanf("%d", &newNode->info);
    newNode->link = NULL;
    
    // Empty list case
    if (first == NULL)
        return newNode;

    Node tempNode = first;
    while (tempNode->link != NULL) tempNode = tempNode->link;
    tempNode->link = newNode;
    return first;
}

Node deleteFront(Node first) {
    if (first == NULL) {
        printf("List is empty. \n");
        return NULL;
    }

    NE--;
    Node deleteNode = first;
    first = first->link;
    printf("Deleting %d\n", deleteNode->info);
    free(deleteNode);
    return first;
}

Node deleteRear(Node first) {
    if (first == NULL) {
        printf("List is empty. \n");
        return NULL;
    }

    NE--;
    // Single element case
    if (first->link == NULL) {
        printf("Deleting %d\n", first->info);
        free(first);
        return NULL;
    }

    Node prevNode = NULL, curNode = first;
    while (curNode->link != NULL) {
        prevNode = curNode;
        curNode = curNode->link;
    }
    printf("Deleting %d\n", curNode->info);
    free(curNode);
    prevNode->link = NULL;
    return first;
}

Node insertAtPos(Node first) {
    int pos;
    printf("Enter the position at which the element is to be inserted: ");
    scanf("%d", &pos);
    if (pos >= 1 && pos <= NE + 1) {
        NE++;
        Node newNode = (Node) malloc(sizeof(struct node));
        printf("Enter element to be inserted: ");
        scanf("%d", &newNode->info);

        if (pos == 1) { 
            newNode->link = first;
            return newNode;
        }

        Node prevNode = NULL, tempNode = first;
        int cnt;
        for (cnt = 1; cnt < pos; cnt++) {
            prevNode = tempNode;
            tempNode = tempNode->link;
        }
        prevNode->link = newNode;
        newNode->link = tempNode;
        return first;
    } else {
        printf("Invalid position. \n");
        return first;
    }
}

Node deleteAtPos(Node first) {
    if (first == NULL) {
        printf("List is empty. \n");
        return NULL;
    }
    
    int pos;
    printf("Enter position of the element to be deleted: ");
    scanf("%d", &pos);

    if (pos >= 1 && pos <= NE) {
        NE--;

        if (pos == 1) {
            Node deleteNode = first;
            first = first->link;
            free(deleteNode);
            return first;
        }

        Node deleteNode = first, prevNode = NULL;
        int cnt;
        for (cnt = 1; cnt < pos; cnt++) {
            prevNode = deleteNode;
            deleteNode = deleteNode->link;
        }
        prevNode->link = deleteNode->link;
        free(deleteNode);
        return first;
    } else {
        printf("Invalid position. \n");
        return first;
    }
}

Node insertByOrder(Node first) {
    NE++;
    Node newNode = (Node) malloc(sizeof(struct node));
    printf("Enter element to be inserted: ");
    scanf("%d", &newNode->info);

    // Empty list case
    if (first == NULL) {
        newNode->link = NULL;
        return newNode;
    }

    // Front insert case
    if (first->info > newNode->info) {
        newNode->link = first;
        return newNode;
    }


    Node tempNode = first, prevNode = NULL;
    while (tempNode != NULL && tempNode->info <= newNode->info) {
        prevNode = tempNode;
        tempNode = tempNode->link;
    }
    newNode->link = tempNode;
    prevNode->link = newNode;
    return first;
}

Node deleteByKey(Node first) {
    if (first == NULL) {
        printf("List is empty. \n");
        return NULL;
    }

    int key;
    printf("Enter key to delete: ");
    scanf("%d", &key);

    // Front deletion case
    if (first->info == key) {
        NE--;
        Node deleteNode = first;
        first = first->link;
        free(deleteNode);
        return first;
    }

    Node tempNode = first, prevNode = NULL;
    while (tempNode != NULL && tempNode->info != key) {
        prevNode = tempNode;
        tempNode = tempNode->link;
    }

    if (tempNode == NULL) {
        printf("Key does not exist in the List. \n");
        return first;
    }
    NE--;
    Node deleteNode = tempNode;
    prevNode->link = tempNode->link;
    free(deleteNode);
    return first;
}

Node search(Node first) {
    if (first == NULL) {
        printf("List is empty. \n");
        return NULL;
    }

    int key;
    printf("Enter the key to be searched: ");
    scanf("%d", &key);

    Node tempNode = first;
    while (tempNode != NULL && tempNode->info != key) {
        tempNode = tempNode->link;
    }

    if (tempNode == NULL) {
        printf("Key not found. \n");
    } else {
        printf("Key (%d) found. \n", tempNode->info);
    }

    return tempNode;
}

Node createCopy(Node first) {
    if (first == NULL) {
        printf("Copying empty list\n");
        return NULL;
    }
    Node copy = NULL, tempNode;
    while (first != NULL) {
        Node newNode = (Node) malloc(sizeof(struct node));
        newNode->info = first->info;
        newNode->link = NULL;
        if (copy == NULL) {
            copy = newNode;
            tempNode = copy;
        } else {
            tempNode->link = newNode;
            tempNode = newNode;
        }
        first = first->link;
    }
    return copy;
}

Node reverse(Node first) {
    Node prevNode = NULL, curNode = NULL, nextNode = first;
    while (nextNode != NULL) {
        curNode = nextNode;
        nextNode = nextNode->link;
        curNode->link = prevNode;
        prevNode = curNode;
    }
    return curNode;
}

void printMenu() {
    printf("\n\n\n\n\n\n");
    printf("1.  Display \n");
    printf("2.  Insert Front \n");
    printf("3.  Insert Rear \n");
    printf("4.  Delete Front \n");
    printf("5.  Delete Rear \n");
    printf("6.  Insert at position \n");
    printf("7.  Delete at position \n");
    printf("8.  Insert by order \n");
    printf("9.  Delete by key \n");
    printf("10. Search for key \n");
    printf("11. Create a copy \n");
    printf("12. Reverse the linked list \n");
    printf("13. Exit \n");
}

int main() {
    Node first = NULL, copy = NULL;
    int isRunning = 1;
    while (isRunning) {
        printMenu();
        printf("Enter your choice: ");
        int ch;
        scanf("%d", &ch);
        switch(ch) {
        case 1:
            display(first);
            break;
        case 2:
            first = insertFront(first);
            display(first);
            break;
        case 3:
            first = insertRear(first);
            display(first);
            break;
        case 4:
            first = deleteFront(first);
            display(first);
            break;
        case 5:
            first = deleteRear(first);
            display(first);
            break;
        case 6:
            first = insertAtPos(first);
            display(first);
            break;
        case 7:
            first = deleteAtPos(first);
            display(first);
            break;
        case 8:
            first = insertByOrder(first);
            display(first);
            break;
        case 9:
            first = deleteByKey(first);
            display(first);
            break;
        case 10:
            search(first);
            break;
        case 11:
            copy = createCopy(first);
            printf("Copy : ");
            display(copy);
            break;
        case 12:
            first = reverse(first);
            break;
        case 13:
            isRunning = 0;
            break;
        default:
            printf("Invalid option. \n");
            break;
        }
    }

    return 0;
}