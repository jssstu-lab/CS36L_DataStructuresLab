#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node* link;
};

typedef struct node* Node;

int NE = 0;

void display(Node last) {
    if (last == NULL) {
        printf("List is empty. \n");
        return;
    }

    Node tempNode = last->link;
    do {
        printf("%d ", tempNode->info);
        tempNode = tempNode->link;
    } while (tempNode != last->link);
    printf("\n");
}

Node insertFront(Node last) {
    NE++;
    Node newNode = (Node) malloc(sizeof(struct node));
    printf("Enter element to be inserted: ");
    scanf("%d", &newNode->info);
    
    // Empty case
    if (last == NULL) {
        newNode->link = newNode;
        return newNode;
    }

    newNode->link = last->link;
    last->link = newNode;
    return last;
}

Node insertRear(Node last) {
    NE++;
    Node newNode = (Node) malloc(sizeof(struct node));
    printf("Enter element to be inserted: ");
    scanf("%d", &newNode->info);

    // Empty case
    if (last == NULL) {
        newNode->link = newNode;
        return newNode;
    }

    newNode->link = last->link;
    last->link = newNode;
    return newNode;
}

Node deleteFront(Node last) {
    if (last == NULL) {
        printf("List is empty. \n");
        return NULL;
    }
    
    NE--;
    Node deleteNode = last->link;

    // Single element case
    if (deleteNode->link == deleteNode)
        last = NULL;
    else
        last->link = deleteNode->link;
    
    free(deleteNode);
    return last;
}

Node deleteRear(Node last) {
    if (last == NULL) {
        printf("List is empty. \n");
        return NULL;
    }

    NE--;
    if (last->link == last) {
        free(last);
        return NULL;
    }

    Node prevNode = last->link;
    while (prevNode->link != last) 
        prevNode = prevNode->link;
    prevNode->link = last->link;
    free(last);
    return prevNode;
}

Node insertAtPos(Node last) {
    int pos;
    printf("Enter the position at which the element is to be inserted: ");
    scanf("%d", &pos);
    if (pos >= 1 && pos <= NE+1) {
        NE++;
        Node newNode = (Node) malloc(sizeof(struct node));
        printf("Enter the element to be inserted: ");
        scanf("%d", &newNode->info);
        newNode->link = newNode;

        if (pos == 1) {
            if (last == NULL) return newNode;
            newNode->link = last->link;
            last->link = newNode;
            return last;
        }

        if (pos == NE) {
            newNode->link = last->link;
            last->link = newNode;
            return newNode;
        }

        Node tempNode = last->link, prevNode = NULL;
        int cnt;
        for (cnt = 1; cnt < pos; cnt++) {
            prevNode = tempNode;
            tempNode = tempNode->link;
        }
        prevNode->link = newNode;
        newNode->link = tempNode;
        return last;
    } else {
        printf("Invalid position. \n");
        return last;
    }
}

Node deleteAtPos(Node last) {
    if (last == NULL) {
        printf("List is empty. \n");
        return NULL;
    }

    int pos;
    printf("Enter the position of the element to be deleted: ");
    scanf("%d", &pos);

    if (pos >= 1 && pos <= NE) {
        NE--;

        if (pos == 1 && last->link == last) {
            free(last);
            return NULL;
        }

        Node deleteNode = last->link, prevNode = last;
        int cnt;
        for (cnt = 1; cnt < pos; cnt++) {
            prevNode = deleteNode;
            deleteNode = deleteNode->link;
        }
        prevNode->link = deleteNode->link;
        free(deleteNode);
        if (pos == NE + 1)
            return prevNode;
        else
            return last;
    } else {
        printf("Invalid position. \n");
        return last;
    }
}

Node insertByOrder(Node last) {
    NE++;
    Node newNode = (Node) malloc(sizeof(struct node));
    printf("Enter the element to be inserted: ");
    scanf("%d", &newNode->info);
    newNode->link = newNode;

    // Empty case
    if (last == NULL)
        return newNode;

    // Insert Last case
    if (last->info < newNode->info) {
        newNode->link = last->link;
        last->link = newNode;
        return newNode;
    }
    
    Node tempNode = last->link, prevNode = last;
    while (tempNode->info < newNode->info) {
        prevNode = tempNode;
        tempNode = tempNode->link;
    }
    prevNode->link = newNode;
    newNode->link = tempNode;
    return last;
}

Node deleteByKey(Node last) {
    if (last == NULL) {
        printf("List is empty. \n");
        return NULL;
    }

    int key;
    printf("Enter the key of the element to be deleted: ");
    scanf("%d", &key);

    if (last->link->info == key) {
        NE--;
        if (last == last->link) {
            free(last);
            return NULL;
        }

        Node deleteNode = last->link;
        last->link = deleteNode->link;
        free(deleteNode);
        return last;
    }

    Node deleteNode = last->link, prevNode = NULL;
    do {
        prevNode = deleteNode;
        deleteNode = deleteNode->link;
    } while (deleteNode != last->link && deleteNode->info != key);

    if (deleteNode == last->link) {
        printf("No key match. Could not delete. \n");
        return last;
    }

    NE--;
    prevNode->link = deleteNode->link;
    free(deleteNode);
    if (deleteNode == last) return prevNode;
    return last;
}

void search(Node last) {
    if (last == NULL) {
        printf("List is empty. \n");
        return;
    }

    int pos = 1;
    int key, flag = 0;
    printf("Enter the key to be searched: ");
    scanf("%d", &key);

    Node tempNode = last->link;

    do {
        if (tempNode->info == key) {
            flag = 1;
            break;
        }
        tempNode = tempNode->link;
        pos++;
    } while (tempNode != last->link);

    if (flag) {
        printf("Element %d found at position %d. \n", key, pos);
    } else {
        printf("Element not found. \n");
    }
}

Node createCopy(Node last) {
    if (last == NULL) {
        printf("Copying empty list\n");
        return NULL;
    }

    Node firstNode = NULL, lastNode = NULL;
    Node tempNode = last->link;
    do {
        Node newNode = (Node) malloc(sizeof(struct node));
        newNode->info = tempNode->info;
        if (firstNode == NULL) {
            firstNode = newNode;
            lastNode = firstNode;
        } else {
            lastNode->link = newNode;
            lastNode = newNode;
        }
        tempNode = tempNode->link;
    } while (tempNode != last->link);
    lastNode->link = firstNode;
    return lastNode;
}

Node reverse(Node last) {
    if (last == NULL) {
        printf("List is empty. \n");
        return NULL;
    }
    Node prevNode = last, curNode = NULL, nextNode = last->link;

    do {
        curNode = nextNode;
        nextNode = nextNode->link;
        curNode->link = prevNode;
        prevNode = curNode;
    } while (curNode != last);

    return nextNode;
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
    Node last = NULL, copy = NULL;
    int isRunning = 1;
    while (isRunning) {
        printMenu();
        printf("Enter your choice: ");
        int ch;
        scanf("%d", &ch);
        switch(ch) {
        case 1:
            display(last);
            break;
        case 2:
            last = insertFront(last);
            display(last);
            break;
        case 3:
            last = insertRear(last);
            display(last);
            break;
        case 4:
            last = deleteFront(last);
            display(last);
            break;
        case 5:
            last = deleteRear(last);
            display(last);
            break;
        case 6:
            last = insertAtPos(last);
            display(last);
            break;
        case 7:
            last = deleteAtPos(last);
            display(last);
            break;
        case 8:
            last = insertByOrder(last);
            display(last);
            break;
        case 9:
            last = deleteByKey(last);
            display(last);
            break;
        case 10:
            search(last);
            break;
        case 11:
            copy = createCopy(last);
            printf("Copy : ");
            display(copy);
            break;
        case 12:
            last = reverse(last);
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