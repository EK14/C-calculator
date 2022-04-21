#ifndef CALCULATOR_MATHS_H
#define CALCULATOR_MATHS_H
#include <math.h>
#include "stack.h"
#include <string.h>
typedef enum type{
    ADD, SUB, MULT, DIV, POW, BRACK, VAR, NUMB, FUNC2, FUNC1
} TYPE;

double complex Abs(double complex x);

double complex real(double complex x);

double complex imag(double complex x);

double complex mag(double complex x);

double complex phase(double complex x);

double complex LN(double complex x);

double complex Log(double complex x, double complex y);

double complex Add(double complex x, double complex y);

double complex Sub(double complex x, double complex y);

double complex Mult(double complex x, double complex y);

double complex Div(double complex x, double complex y);

void Maths(LEKSEMA *var,const int *varSize, LEKSEMA *postfix, int sizeOfStr);
#endif //CALCULATOR_MATHS_H
