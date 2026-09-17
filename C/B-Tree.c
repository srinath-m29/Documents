#include <stdlib.h>

#define T 3

struct Node {
    int key[5], n, leaf;
    struct Node *child[6];
};

struct Node *create(int leaf) {
    struct Node *p = malloc(sizeof(struct Node));
    p->n = 0;
    p->leaf = leaf;
    return p;
}

void display(struct Node *p) {
    int i;
    if (p == NULL) return;

    for (i = 0; i < p->n; i++) {
        if (!p->leaf) display(p->child[i]);
        printf("%d ", p->key[i]);
    }

    if (!p->leaf) display(p->child[i]);
}

void split(struct Node *parent, int pos) {
    struct Node *a = parent->child[pos];
    struct Node *b = create(a->leaf);
    int i;

    b->n = 2;

    for (i = 0; i < 2; i++)
        b->key[i] = a->key[i + 3];

    if (!a->leaf)
        for (i = 0; i < 3; i++)
            b->child[i] = a->child[i + 3];

    a->n = 2;

    for (i = parent->n; i >= pos + 1; i--)
        parent->child[i + 1] = parent->child[i];

    parent->child[pos + 1] = b;

    for (i = parent->n - 1; i >= pos; i--)
        parent->key[i + 1] = parent->key[i];

    parent->key[pos] = a->key[2];
    parent->n++;
}

void insertNode(struct Node *p, int x) {
    int i = p->n - 1;

    if (p->leaf) {
        while (i >= 0 && x < p->key[i]) {
            p->key[i + 1] = p->key[i];
            i--;
        }

        p->key[i + 1] = x;
        p->n++;
    }
    else {
        while (i >= 0 && x < p->key[i])
            i--;

        i++;

        if (p->child[i]->n == 5) {
            split(p, i);

            if (x > p->key[i])
                i++;
        }

        insertNode(p->child[i], x);
    }
}

void insert(struct Node **root, int x) {
    if (*root == NULL) {
        *root = create(1);
        (*root)->key[0] = x;
        (*root)->n = 1;
        return;
    }

    if ((*root)->n == 5) {
        struct Node *newRoot = create(0);

        newRoot->child[0] = *root;
        split(newRoot, 0);

        if (x > newRoot->key[0])
            insertNode(newRoot->child[1], x);
        else
            insertNode(newRoot->child[0], x);

        *root = newRoot;
    }
    else
        insertNode(*root, x);
}

int find(struct Node *p, int x) {
    int i = 0;

    while (i < p->n && p->key[i] < x)
        i++;

    return i;
}

int predecessor(struct Node *p) {
    while (!p->leaf)
        p = p->child[p->n];

    return p->key[p->n - 1];
}

int successor(struct Node *p) {
    while (!p->leaf)
        p = p->child[0];

    return p->key[0];
}

void merge(struct Node *p, int i) {
    struct Node *a = p->child[i];
    struct Node *b = p->child[i + 1];
    int j;

    a->key[2] = p->key[i];

    for (j = 0; j < b->n; j++)
        a->key[j + 3] = b->key[j];

    if (!a->leaf)
        for (j = 0; j <= b->n; j++)
            a->child[j + 3] = b->child[j];

    a->n += b->n + 1;

    for (j = i; j < p->n - 1; j++)
        p->key[j] = p->key[j + 1];

    for (j = i + 1; j < p->n; j++)
        p->child[j] = p->child[j + 1];

    p->n--;
    free(b);
}

void deleteNode(struct Node *p, int x) {
    int i = find(p, x);

    if (i < p->n && p->key[i] == x) {
        if (p->leaf) {
            for (; i < p->n - 1; i++)
                p->key[i] = p->key[i + 1];

            p->n--;
        }
        else if (p->child[i]->n >= T) {
            int y = predecessor(p->child[i]);
            p->key[i] = y;
            deleteNode(p->child[i], y);
        }
        else if (p->child[i + 1]->n >= T) {
            int y = successor(p->child[i + 1]);
            p->key[i] = y;
            deleteNode(p->child[i + 1], y);
        }
        else {
            merge(p, i);
            deleteNode(p->child[i], x);
        }
    }
    else {
        if (p->leaf)
            return;

        if (p->child[i]->n < T) {
            if (i > 0 && p->child[i - 1]->n >= T) {
                p->child[i]->key[0] = p->key[i - 1];
                p->key[i - 1] =
                    p->child[i - 1]->key[p->child[i - 1]->n - 1];

                p->child[i]->n++;
                p->child[i - 1]->n--;
            }
            else if (i < p->n && p->child[i + 1]->n >= T) {
                p->child[i]->key[p->child[i]->n] = p->key[i];
                p->key[i] = p->child[i + 1]->key[0];

                p->child[i]->n++;
                p->child[i + 1]->n--;
            }
            else {
                if (i < p->n)
                    merge(p, i);
                else
                    merge(p, i - 1);
            }
        }

        if (i > p->n)
            deleteNode(p->child[i - 1], x);
        else
            deleteNode(p->child[i], x);
    }
}

void deleteKey(struct Node **root, int x) {
    if (*root == NULL)
        return;

    deleteNode(*root, x);

    if ((*root)->n == 0) {
        struct Node *temp = *root;

        if ((*root)->leaf)
            *root = NULL;
        else
            *root = (*root)->child[0];

        free(temp);
    }
}

int main() {
    struct Node *root = NULL;
    int n, x, del;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");

    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        insert(&root, x);
    }

    printf("B-Tree before deletion: ");
    display(root);

    printf("\nEnter key to delete: ");
    scanf("%d", &del);

    deleteKey(&root, del);

    printf("B-Tree after deletion: ");
    display(root);

    return 0;
}
