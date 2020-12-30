#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *llink, *rlink;
};

typedef struct node* Node;

Node insert(Node root) {
    Node newNode = (Node) malloc(sizeof(struct node));
    newNode->llink = newNode->rlink = NULL;

    printf("Enter element to insert into BST: ");
    scanf("%d", &newNode->info);

    if (root == NULL)
        return newNode;
    
    Node curNode = root, parentNode = NULL;
    while (curNode != NULL) {
        parentNode = curNode;
        if (newNode->info < curNode->info)
            curNode = curNode->llink;
        else
            curNode = curNode->rlink;
    }

    if (newNode->info < parentNode->info)
        parentNode->llink = newNode;
    else
        parentNode->rlink = newNode;
    
    return root;
}

// DFS: proorder, inorder, postorder

void preorder_traversal(Node root) {
    if (root == NULL)
        return;

    printf("%d ", root->info);
    preorder_traversal(root->llink);
    preorder_traversal(root->rlink);
}

void inorder_traversal(Node root) {
    if (root == NULL)
        return;

    inorder_traversal(root->llink);
    printf("%d ", root->info);
    inorder_traversal(root->rlink);
}

void postorder_traversal(Node root) {
    if (root == NULL)
        return;

    postorder_traversal(root->llink);
    postorder_traversal(root->rlink);
    printf("%d ", root->info);
}

// BFS

typedef struct {
    Node items[100];
    int fidx, ridx;
} Queue;

void initQueue(Queue* q) {
    q->fidx = 0;
    q->ridx = -1;
}

int isEmpty(Queue* q) {
    return q->fidx > q->ridx;
} 

void enqueue(Queue* q, Node n) {
    if (q->ridx == 99) {
        printf("Queue is full\n");
        return;
    }
    q->items[++q->ridx] = n;
}

Node dequeue(Queue* q) {
    if (isEmpty(q))
        return NULL;

    Node p = q->items[q->fidx++];
    if (isEmpty(q))
        initQueue(q);
    
    return p;
}

void levelorder_traversal(Node root) { 
    if (root == NULL) {
        printf("Tree is empty. \n");
        return;
    }

    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    
    Node curNode;
    do {
        curNode = dequeue(&q);

        printf("%d ", curNode->info);
        if (curNode->llink != NULL) enqueue(&q, curNode->llink);
        if (curNode->rlink != NULL) enqueue(&q, curNode->rlink);
    } while (!isEmpty(&q));
}

void display(Node root) {
    if (root == NULL) {
        printf("Tree is empty. \n");
        return;
    }

    printf("DFS: \n");
    printf("Pre-order traversal: ");
    preorder_traversal(root);
    printf("\nIn-order traversal: ");
    inorder_traversal(root);
    printf("\nPost-order traversal: ");
    postorder_traversal(root);

    printf("\n\nBFS (Level order traversal): ");
    levelorder_traversal(root);
    putchar('\n');
}

Node search(Node root, int key, Node* parentNode) {
    if (root == NULL)
        return NULL;

    if (key == root->info)
        return root;

    if (key < root->info) {
        *parentNode = root;
        return search(root->llink, key, parentNode);
    } else {
        *parentNode = root;
        return search(root->rlink, key, parentNode);
    }
}

void searchUtil(Node root) {
    int key;
    Node parentNode = NULL, searchNode;
    printf("Enter key to search: ");
    scanf("%d", &key);

    searchNode = search(root, key, &parentNode);
    
    if (searchNode) {
        if (parentNode)
            printf("Key %d was found with parent %d\n", searchNode->info, parentNode->info);
        else
            printf("Key %d was found at the root\n", searchNode->info);
    } else {
        printf("Key %d not found.\n", key);
    }
}

Node delete(Node root) {
    int key;
    printf("Enter key of the element to delete: ");
    scanf("%d", &key);

    if (root->info == key && root->llink == NULL && root->rlink == NULL) {
        free(root);
        return NULL;
    }

    Node parentNode = NULL, deleteNode;
    deleteNode = search(root, key, &parentNode);

    if (!deleteNode) {
        printf("Key not found!~\n");
        return root;
    }

    if (deleteNode->llink == NULL && deleteNode->rlink == NULL) {
        // leaf node case
        if(parentNode->llink == deleteNode)
            parentNode->llink = NULL;
        else
            parentNode->rlink = NULL;
        printf("Deleteing %d\n", deleteNode->info);
        free(deleteNode);
    } else if (deleteNode->llink == NULL || deleteNode->rlink == NULL) {
        // single child case
        if (parentNode->llink == deleteNode) {
            if (deleteNode->llink)
                parentNode->llink = deleteNode->llink;
            else
                parentNode->llink = deleteNode->rlink;
        } else {
            if (deleteNode->llink)
                parentNode->rlink = deleteNode->llink;
            else
                parentNode->rlink = deleteNode->rlink;
        }
        printf("Deleting %d\n", deleteNode->info);
        free(deleteNode);
    } else {
        // two child case
        Node is = deleteNode->rlink, isp = deleteNode;
        while (is->llink) {
            isp = is;
            is = is->llink;
        }

        printf("Deleting %d\n", deleteNode->info);
        deleteNode->info = is->info;

        if (is->llink == NULL && is->rlink == NULL) {
            // leaf node case
            if(isp->llink == is)
                isp->llink = NULL;
            else
                isp->rlink = NULL;
            free(is);
        } else {
            // single child case
            if (isp->llink == is) 
                isp->llink = is->rlink;
            else
                isp->rlink = is->rlink;

            free(is);
        }
    }

    return root;
}

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;    
}

int findHeight(Node root) {
    if (root == NULL)
        return -1;
    return max(1 + findHeight(root->llink), 1 + findHeight(root->rlink));
}

Node createCopy(Node src, Node* dest) {
    if (src == NULL)
        return NULL;
    
    *dest = (Node) malloc(sizeof(struct node));
    (*dest)->info = src->info;
    createCopy(src->llink, &((*dest)->llink)); 
    createCopy(src->rlink, &((*dest)->rlink)); 
}

void deleteTree(Node *root) {
    if (*root == NULL)
        return;

    deleteTree(&(*root)->llink);
    deleteTree(&(*root)->rlink);
    free(*root);
    *root = NULL;
}

int countNodes(Node root) {
    if (root == NULL)
        return 0;
    
    return 1 + countNodes(root->llink) + countNodes(root->rlink);
}

int countLeafNodes(Node root) {
    if (root == NULL)
        return 0;
    
    if (root->llink == NULL && root->rlink == NULL)
        return 1;
    else
        return countLeafNodes(root->llink) + countLeafNodes(root->rlink);
}

int countNonLeafNodes(Node root) {
    if (root == NULL)
        return 0;
    
    if (root->llink == NULL && root->rlink == NULL)
        return 0;
    else
        return 1 + countNonLeafNodes(root->llink) + countNonLeafNodes(root->rlink);
}

void printMenu() {
    printf("1. Insert element into tree\n");
    printf("2. Display all traversals of the tree\n");
    printf("3. Search key in tree\n");
    printf("4. Delete key from tree\n");
    printf("5. Find tree's height/depth\n");
    printf("6. Create copy of tree and display\n");
    printf("7. Count nodes\n");
    printf("8. Count leaf nodes\n");
    printf("9. Count non leaf nodes\n");
    printf("10. Exit\n");
}

int main() {
    Node root = NULL, copyRoot = NULL;

    int isRunning = 1;
    while (isRunning) {
        printMenu();
        printf("Enter your choice: ");
        int ch;
        scanf("%d", &ch);

        switch(ch) {
            case 1:
                root = insert(root);
                break;
            case 2:
                display(root);
                break;
            case 3:
                searchUtil(root);
                break;
            case 4:
                root = delete(root);
                break;
            case 5:
                printf("Height/Depth of the tree = %d\n", findHeight(root));
                break;
            case 6:
                createCopy(root, &copyRoot);
                printf("Original tree:\n");
                display(root);
                printf("\nCopied tree:\n");
                display(copyRoot);
                break;
            case 7:
                printf("Number of nodes: %d\n", countNodes(root));
                break;
            case 8:
                printf("Number of leaf nodes: %d\n", countLeafNodes(root));
                break;
            case 9:
                printf("Number of non-leaf nodes: %d\n", countNonLeafNodes(root));
                break;
            case 10:
                isRunning = 0;
                break;
            default:
                printf("Invalid choice\n");
        }
    }

    deleteTree(&root);
    deleteTree(&copyRoot);

    return 0;
}