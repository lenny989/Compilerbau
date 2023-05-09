#include <stdio.h>
#include <stdlib.h>
#include "syntree.h"
//1
void handle_error(Syntree *self){
    fprintf(stderr, "An error occurred. NULL in args\n");
    if (self == NULL) exit(-2);
    syntreeRelease(self);
    exit(-1);
}

int syntreeInit(Syntree *self) {
    if (self == NULL) return -1;
    self->data = 0;
    self->children = NULL;
    self->numChildren = 0;
    return 0;
}

void syntreeRelease(Syntree *self) {
    if (self == NULL) return;
    for (int i = 0; i < self->numChildren; i++) {
        syntreeRelease(self->children[i]);
        free(self->children[i]);
    }
    free(self->children);
    free(self);
}

SyntreeNodeID syntreeNodeNumber(Syntree *self, int number) {
    if (self == NULL) handle_error(self);

    Syntree *newNode = malloc(sizeof(Syntree));
    newNode->data = number;
    newNode->children = NULL;
    newNode->numChildren = 0;
    return newNode;
}

SyntreeNodeID syntreeNodeTag(Syntree *self, SyntreeNodeID id) {
    if (self == NULL || id == NULL) handle_error(self);

    Syntree *newNode = malloc(sizeof(Syntree));
    newNode->children = malloc(sizeof(Syntree*));
    newNode->children[0] = id;
    newNode->numChildren = 1;
    return newNode;
}

SyntreeNodeID syntreeNodePair(Syntree *self, SyntreeNodeID id1, SyntreeNodeID id2) {
    if (self == NULL || id1 == NULL || id2 == NULL) handle_error(self);

    Syntree *newNode = malloc(sizeof(Syntree));
    newNode->children = malloc(2 * sizeof(Syntree*));
    newNode->children[0] = id1;
    newNode->children[1] = id2;
    newNode->numChildren = 2;
    return newNode;
}

SyntreeNodeID syntreeNodeAppend(Syntree *self, SyntreeNodeID list, SyntreeNodeID elem) {
    if (self == NULL || list == NULL || elem == NULL) handle_error(self);

    Syntree *listNode = list;
    listNode->children = realloc(listNode->children, (listNode->numChildren + 1) * sizeof(Syntree*));
    listNode->children[listNode->numChildren] = elem;
    listNode->numChildren++;
    return listNode;
}

SyntreeNodeID syntreeNodePrepend(Syntree *self, SyntreeNodeID elem, SyntreeNodeID list) {
    if (self == NULL || elem == NULL || list == NULL) handle_error(self);
    Syntree *listNode = list;
    int numChildren = listNode->numChildren;
    listNode->children = realloc(listNode->children, (numChildren + 1) * sizeof(Syntree*));
    for (int i = numChildren; i > 0; i--) {
        listNode->children[i] = listNode->children[i - 1];
    }
    listNode->children[0] = elem;
    listNode->numChildren++;
    return listNode;
}

void syntreePrint(const Syntree *self, SyntreeNodeID root) {
    if (self == NULL || root == NULL) return;
    Syntree *node = (Syntree*) root;
    if (node->numChildren == 0) {
        printf("%d ", node->data);
        return;
    }
    if (node->numChildren > 0) {
        printf("{ ");
        for (int i = 0; i < node->numChildren; i++) {
            syntreePrint(self, node->children[i]);
        }
        printf("} ");
    }
}
