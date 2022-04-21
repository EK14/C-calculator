#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101
#include "stack.h"
void Push(NODE **head, LEKSEMA val){
    NODE *tmp = NULL;
    tmp = (NODE*) malloc(sizeof(NODE));
    if(tmp == NULL)
        exit(STACK_OVERFLOW);
    tmp->next = *head;
    tmp->val = val;
    *head = tmp;
}

void Pop(NODE **head){
    NODE* tmp = NULL;
    if (head == NULL) {
        exit(STACK_UNDERFLOW);
    }
    tmp = (*head);
    (*head) = (*head)->next;
    free(tmp);
}

LEKSEMA* Top(NODE *head){
    if(head == NULL)
        return NULL;
    return &(head->val);
}
