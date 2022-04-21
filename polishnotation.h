#ifndef CALCULATOR_POLISHNOTATION_H
#define CALCULATOR_POLISHNOTATION_H
#include "stack.h"
#include "maths.h"

void ItIsComma(char ** str, NODE ** stack, LEKSEMA *postfix, int *sizeOfStr);

void ItIsDigit(char ** str, LEKSEMA *postfix, int *sizeOfStr);

void ItIsFuncOrVar(char ** str, NODE ** stack, LEKSEMA * postfix, int * sizeOfStr);

void ItIsUnaryMinus(char ** str, LEKSEMA * postfix, int * sizeOfStr, int *flag, NODE ** stack);

void ItIsBinaryOperation(char ** str, NODE ** stack, LEKSEMA * postfix, int * sizeOfStr);

void ItIsBracket(char ** str, NODE ** stack, LEKSEMA * postfix, int * sizeOfStr);

void ReversePolishNotation(LEKSEMA *var, int *varSize, char * str);

int priority(char  operation);
#endif
