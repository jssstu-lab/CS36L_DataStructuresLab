#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node* llink;
    int info;
    struct node* rlink;
};

typedef struct node* Node;

Node createCDLL() {
    Node newList = (Node) malloc(sizeof(struct node));
    newList->info = 0;
    newList->llink = newList->rlink = newList;
    return newList;
}

void insertFront(Node H) {
    H->info++;
    Node newNode = (Node) malloc(sizeof(struct node));
    printf("Enter element to be inserted: ");
    scanf("%d", &newNode->info);
    newNode->llink = H;
    newNode->rlink = H->rlink;
    newNode->rlink->llink = newNode;
    H->rlink = newNode;
}

void insertRear(Node H) {
    Node newNode = (Node) malloc(sizeof(struct node));
    printf("Enter element to be inserted: ");
    scanf("%d", &newNode->info);
    newNode->llink = H->llink;
    newNode->rlink = H;
    H->llink = newNode;
    newNode->llink->rlink = newNode;
    H->info++;
}

void display(Node H) {
    if (H->info == 0) {
        printf("Empty list. \n");
        return;
    }
    Node tempNode = H->rlink;
    while (tempNode != H) {
        printf("%d ", tempNode->info);
        tempNode = tempNode->rlink;
    }
    printf("\n");
}

void deleteFront(Node H) {
    if (H->info == 0) {
        printf("List is empty. \n");
        return;
    }
    H->info--;

    Node deleteNode = H->rlink;
    H->rlink = deleteNode->rlink;
    deleteNode->rlink->llink = H;
    free(deleteNode);
}

void deleteRear(Node H) {
    if (H->info == 0) {
        printf("List is empty. \n");
        return;
    }
    H->info--;

    Node deleteNode = H->llink;
    deleteNode->llink->rlink = H;
    H->llink = deleteNode->llink;
    free(deleteNode);
}

void insertAtPos(Node H) {
    int pos;
    printf("Enter the position at which the element is to be inserted: ");
    scanf("%d", &pos);

    if (pos >= 1 && pos <= H->info + 1) {
        H->info++;
        Node newNode = (Node) malloc(sizeof(struct node));
        printf("Enter the element to be inserted: ");
        scanf("%d", &newNode->info);

        int cnt = 1;
        Node tempNode = H;
        while (cnt < pos) {
            tempNode = tempNode->rlink;
            cnt++;
        }

        newNode->rlink = tempNode->rlink;
        newNode->llink = tempNode;
        newNode->rlink->llink = newNode;
        newNode->llink->rlink = newNode;
    } else {
        printf("Invalid position. \n");
        return;
    }
}

void deleteAtPos(Node H) {
    if (H->info == 0) {
        printf("List is empty. \n");
        return;
    }

    int pos;
    printf("Enter the position of the element to be deleted: ");
    scanf("%d", &pos);

    if (pos >= 1 && pos <= H->info) {
        H->info--;
        Node deleteNode = H->rlink;
        int cnt = 1;
        while (cnt != pos) {
            deleteNode = deleteNode->rlink;
            cnt++;
        }
        
        deleteNode->llink->rlink = deleteNode->rlink;
        deleteNode->rlink->llink = deleteNode->llink;
        free(deleteNode);
    } else {
        printf("Invalid position. \n");
        return;
    }
}

void insertByOrder(Node H) {
    H->info++;
    Node newNode = (Node) malloc(sizeof(struct node));
    printf("Enter element to be inserted: ");
    scanf("%d", &newNode->info);

    Node tempNode = H->rlink;
    while (tempNode != H && tempNode->info < newNode->info) {
        tempNode = tempNode->rlink;
    }

    newNode->rlink = tempNode;
    newNode->llink = tempNode->llink;
    newNode->rlink->llink = newNode;
    newNode->llink->rlink = newNode;
}

void deleteByKey(Node H) {
    if (H->info == 0) {
        printf("List is empty. \n");
        return;
    }

    int key;
    printf("Enter key of the element to be deleted: ");
    scanf("%d", &key);
    int pos = 1;
    Node deleteNode = H->rlink;
    while (deleteNode != H && deleteNode->info != key) {
        deleteNode = deleteNode->rlink;
        pos++;
    }

    if (deleteNode == H) {
        printf("Key %d not found in list. \n", key);
        return;
    }
    
    H->info--;
    printf("Node with into %d deleted from position %d \n", deleteNode->info, pos);
    deleteNode->llink->rlink = deleteNode->rlink;
    deleteNode->rlink->llink = deleteNode->llink;
    free(deleteNode);
}

void search(Node H) {
    if (H->info == 0) {
        printf("List is empty. \n");
        return;
    }

    int key;
    printf("Enter key of the element to be deleted: ");
    scanf("%d", &key);
    int pos = 1;
    Node tempNode = H->rlink;
    while (tempNode != H && tempNode->info != key) {
        tempNode = tempNode->rlink;
        pos++;
    }

    if (tempNode == H) {
        printf("Key %d not found in list. \n", key);
        return;
    }

    printf("Node with info %d found at position %d \n", tempNode->info, pos);
}

Node createCopy(Node H) {
    Node copyH = createCDLL();
    Node tempNode = H->llink;
    while (tempNode != H) {
        copyH->info++;
        Node newNode = (Node) malloc(sizeof(struct node));
        newNode->info = tempNode->info;
        newNode->llink = copyH;
        newNode->rlink = copyH->rlink;
        copyH->rlink = newNode;
        newNode->rlink->llink = newNode;
        tempNode = tempNode->llink;
    }
    return copyH;
}

void reverse(Node H) {
    Node curNode = H, nextNode = H->rlink;

    do {
        Node tempNode = curNode->llink;
        curNode->llink = curNode->rlink;
        curNode->rlink = tempNode;
        curNode = nextNode;
        nextNode = nextNode->rlink;
    } while (curNode != H);
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
    Node header = createCDLL(), copy = NULL;
    int isRunning = 1;
    while (isRunning) {
        printMenu();
        printf("Enter your choice: ");
        int ch;
        scanf("%d", &ch);
        switch(ch) {
        case 1:
            display(header);
            break;
        case 2:
            insertFront(header);
            display(header);
            break;
        case 3:
            insertRear(header);
            display(header);
            break;
        case 4:
            deleteFront(header);
            display(header);
            break;
        case 5:
            deleteRear(header);
            display(header);
            break;
        case 6:
            insertAtPos(header);
            display(header);
            break;
        case 7:
            deleteAtPos(header);
            display(header);
            break;
        case 8:
            insertByOrder(header);
            display(header);
            break;
        case 9:
            deleteByKey(header);
            display(header);
            break;
        case 10:
            search(header);
            break;
        case 11:
            copy = createCopy(header);
            printf("Copy : ");
            display(copy);
            break;
        case 12:
            reverse(header);
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