#ifndef CALCULATOR_STACK_H
#define CALCULATOR_STACK_H
#include "leksema.h"
#include <stdlib.h>
typedef struct node{
    LEKSEMA val;
    struct node* next;
} NODE;

void Push(NODE **head, LEKSEMA val);

void Pop(NODE **head);

LEKSEMA* Top(NODE *head);
#endif //CALCULATOR_STACK_H
