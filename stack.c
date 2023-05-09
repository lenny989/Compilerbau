#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


int stackInit(IntStack *self) {
    if (self == NULL) return -1;
    self->val = 0;
    self->next = NULL;
    return 0;
}

void stackRelease(IntStack *self) {
    IntStack *current = self;
    while (current != NULL) {
        IntStack *t = current->next;
        free(current);
        current = t;
    }
}
void stackPush(IntStack *self, int i) {
    IntStack *newNode = (IntStack *)malloc(sizeof(IntStack));
    newNode->val = i;
    newNode->next = self->next;
    self->next = newNode;
}

int stackTop(const IntStack *self) {
    if (self->next != NULL) {
        return self->val;
    }
    fprintf(stderr, "An error occurred. Empty\n");
    exit(-1);
}

int stackPop(IntStack *self) {
    if (self->next != NULL) {
        IntStack *t = self->next;
        int value = t->val;
        self->next = t->next;
        free(t);
        return value;
    }
    fprintf(stderr, "An error occurred. Empty\n");
    exit(-1);
}

int stackIsEmpty(const IntStack *self) {
    return (self->next == NULL) ? 1 : 0;
}

void stackPrint(const IntStack *self) {
    const IntStack *current = self->next;
    printf("Stack:");
    while (current != NULL) {
        printf(" %d;", current->val);
        current = current->next;
    }
    printf("\n");
}