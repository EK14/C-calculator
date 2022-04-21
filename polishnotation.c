#include "polishnotation.h"
#define SIZE_OF_OPER 5
int priority(char  operation){
    switch(operation){
        case '+':
        case '-':
            return 0;
        case '*':
        case '/':
            return 1;
        case '^':
            return 2;
        default: return -1;
    }
}

void ItIsComma(char ** str, NODE ** stack, LEKSEMA *postfix, int *sizeOfStr){
    while((*Top(*stack)).type != BRACK){
        postfix[*sizeOfStr] = *Top(*stack);
        (*sizeOfStr)++;
        Pop(&*stack);
    }
    (*str)++;
}

void ItIsDigit(char ** str, LEKSEMA *postfix, int *sizeOfStr){
    char tmp[10] = {'\0'};
    int j = 0;
    while(**str >= '0' && **str <= '9' || **str=='.' || **str=='j'){
        tmp[j] = **str;
        j++;
        (*str)++;
    }
    tmp[j] = '\0';
    if(tmp[strlen(tmp)-1] == 'j') {
        tmp[strlen(tmp)-1] = '\0';
        if(strlen(tmp) == 0)
            postfix[*sizeOfStr].cmp = 0 + 1 * I;
        else
            postfix[*sizeOfStr].cmp = 0 + strtod(tmp, NULL) * I;
        postfix[*sizeOfStr].type = NUMB;
        (*sizeOfStr)++;
    }
    else{
        postfix[*sizeOfStr].cmp = strtod(tmp, NULL) + 0 * I;
        postfix[*sizeOfStr].type = NUMB;
        (*sizeOfStr)++;
    }
}

void ItIsFuncOrVar(char ** str, NODE ** stack, LEKSEMA * postfix, int * sizeOfStr){
    char tmp[10] = {'\0'};
    int j = 0;
    LEKSEMA toStack;
    while(**str >= 'a' && **str <= 'z' || **str >= 'A' && **str <= 'Z' || **str >= '0' && **str <= '9') {
        tmp[j] = **str;
        j++;
        (*str)++;
    }
    tmp[j] = '\0';
    if(**str == '('){
        if (!strcmp("pow", tmp) || !strcmp("log", tmp) || !strcmp("^", tmp)){
            toStack.type = FUNC2;
        }
        else
            toStack.type = FUNC1;
        strcpy(toStack.name, tmp);
        Push(&*stack, toStack);
        return;
    }
    strcpy(postfix[*sizeOfStr].name, tmp);
    postfix[*sizeOfStr].type = VAR;
    (*sizeOfStr)++;
}

void ItIsUnaryMinus(char ** str, LEKSEMA * postfix, int * sizeOfStr, int *flag, NODE ** stack){
    LEKSEMA toStack;
    char tmp[10] = {'\0'};
    postfix[*sizeOfStr].type = NUMB;;
    postfix[*sizeOfStr].cmp = 0 + 0 * I;
    (*sizeOfStr)++;
    (*flag) = 0;
    tmp[0] = **str;
    tmp[1] = '\0';
    toStack.type = SUB;
    strcpy(toStack.name, tmp);
    Push(&*stack, toStack);
    (*str)++;
}

void ItIsBinaryOperation(char ** str, NODE ** stack, LEKSEMA * postfix, int * sizeOfStr){
    char tmp[10] = {'\0'};
    LEKSEMA toStack;
    int j;
    char *operations[] = {"+", "-", "*", "/", "^"};
    while (Top(*stack) != NULL && ((*Top(*stack)).type == FUNC1 || (*Top(*stack)).type == FUNC2 ||
                                   priority((*Top(*stack)).name[0]) >= priority(**str))) {
        postfix[*sizeOfStr] = *Top(*stack);
        (*sizeOfStr)++;
        Pop(&*stack);
    }
    tmp[0] = **str;
    tmp[1] = '\0';
    for(j=0; j < SIZE_OF_OPER; ++j) {
        if (!strcmp(operations[j], tmp)) {
            toStack.type = j;
            break;
        }
    }
    strcpy(toStack.name, tmp);
    Push(&*stack, toStack);
    (*str)++;
}

void ItIsBracket(char ** str, NODE ** stack, LEKSEMA * postfix, int * sizeOfStr){
    char tmp[10] = {'\0'};
    LEKSEMA toStack;
    if(**str == '('){
        tmp[0] = **str;
        tmp[1] = '\0';
        toStack.type = BRACK;
        strcpy(toStack.name, tmp);
        Push(&*stack, toStack);
        (*str)++;
    }
    else if(**str == ')') {
        while ((*Top(*stack)).type != BRACK) {
            postfix[*sizeOfStr] = *Top(*stack);
            (*sizeOfStr)++;
            Pop(&*stack);
        }
        Pop(&*stack);
        (*str)++;
        if(Top(*stack) != NULL && ((*Top(*stack)).type == FUNC1 || (*Top(*stack)).type == FUNC2)){
            postfix[*sizeOfStr] = *Top(*stack);
            (*sizeOfStr)++;
            Pop(&*stack);
        }
    }
}

void ReversePolishNotation(LEKSEMA *var, int *varSize, char * str){
    NODE *stack = NULL;
    LEKSEMA postfix[100];
    int sizeOfStr = 0;
    int flag = 0;
    if(*str == '-')
        flag = 1;
    while(1){
        if(*str=='\n' || *str == '\0') break;
        if(*str == ' ') str++;
        if(*str == ','){
            ItIsComma(&str, &stack, postfix, &sizeOfStr);
        }
        if(*str >= '0' && *str <= '9' || *str=='.' || *str=='j' && !((*(str+1) >= 'a' && *(str+1) <= 'z')
                                                                     || (*(str+1) >= 'A' && *(str+1) <= 'Z'))){
            ItIsDigit(&str, postfix, &sizeOfStr);
        }
        if((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z')){
            ItIsFuncOrVar(&str, &stack, postfix, &sizeOfStr);
        }
        if(*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '^') {
            if(*str == '-' && (flag == 1 || *(str-1) == '(')){
                ItIsUnaryMinus(&str, postfix, &sizeOfStr, &flag, &stack);
                continue;
            }
            ItIsBinaryOperation(&str, &stack, postfix, &sizeOfStr);
        }
        if(*str == '(' || *str == ')'){
            ItIsBracket(&str, &stack, postfix, &sizeOfStr);
        }
    }
    while(Top(stack) != NULL){
        postfix[sizeOfStr++] = *Top(stack);
        Pop(&stack);
    }
    Maths(var, varSize, postfix, sizeOfStr);
}