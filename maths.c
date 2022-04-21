#include <stdio.h>
#include "maths.h"
#define SIZE_OF_FUNCS_2 2
#define SIZE_OF_FUNCS_1 12

double complex Abs(double complex x){
    return cabs(x) + 0 * I;
}

double complex real(double complex x){
    return creal(x) + 0 * I;
}

double complex imag(double complex x){
    return cimag(x) + 0 * I;
}

double complex mag(double complex x){
    return cabs(x) + 0 * I;
}

double complex phase(double complex x){
    return carg(x) + 0 * I;
}

double complex LN(double complex x){
    if(x==0){
        printf("Error: logarithm of 0");
        exit(1);
    }
    return clog(x);
}

double complex Log(double complex x, double complex y){
    return LN(y)/LN(x);
}

double complex Add(double complex x, double complex y){
    return x + y;
}

double complex Sub(double complex x, double complex y){
    return x - y;
}

double complex Mult(double complex x, double complex y){
    return x * y;
}

double complex Div(double complex x, double complex y){
    if(y==0){
        printf("Divide-by-zero error");
        exit(1);
    }
    return x / y;
}

void Maths(LEKSEMA *var,const int *varSize, LEKSEMA *postfix, int sizeOfStr){
    NODE *stack = NULL;
    LEKSEMA x, tmp;
    double complex (*funcs1[])(double complex) = {ccos, csin, ctan, LN, csqrt, Abs, cexp, real, imag,
                mag, phase};
    double complex (*funcs2[])(double complex, double complex) = {cpow, Log};
    double complex (*funcsOp[])(double complex, double complex) = {Add, Sub, Mult, Div, cpow};
    char *nfuncs2[] = {"pow", "log"};
    char *nfuncs1[] = {"cos", "sin", "tg", "ln", "sqrt", "abs", "exp", "real", "imag", "mag", "phase"};
    for(int i=0; i<sizeOfStr; ++i){
        if(postfix[i].type == NUMB){
            Push(&stack, postfix[i]);
            continue;
        }
        if(postfix[i].type == VAR){
            if(!strcmp(postfix[i].name, "PI")){
                tmp.cmp = M_PI + 0 * I;
                Push(&stack, tmp);
                continue;
            }
            if(!strcmp(postfix[i].name, "e")){
                tmp.cmp = M_E + 0 * I;
                Push(&stack, tmp);
                continue;
            }
            int flag = 0;
            for(int j=0; j < *varSize; ++j){

                if(!strcmp(postfix[i].name, var[j].name)){
                    Push(&stack, var[j]);
                    ++flag;
                    break;
                }
            }
            if (flag == 0){
                printf("The variable '%s' was not found", postfix[i].name);
                exit(-3);
            }
            continue;
        }
        if(postfix[i].type == FUNC1){
            int flag = 0;
            for(int j=0; j < SIZE_OF_FUNCS_1; ++j){
                if (!strcmp(postfix[i].name, nfuncs1[j])){
                    ++flag;
                    tmp.cmp = funcs1[j]((*Top(stack)).cmp);
                    Pop(&stack);
                    Push(&stack, tmp);
                }
            }
            if (flag == 0){
                printf("The function '%s' was not found", postfix[i].name);
                exit(-4);
            }
            continue;
        }
        if(postfix[i].type == FUNC2){
            for(int j=0; j < SIZE_OF_FUNCS_2; ++j){
                if(!strcmp(postfix[i].name, nfuncs2[j])){
                    x.cmp = (*Top(stack)).cmp;
                    Pop(&stack);
                    tmp.cmp = funcs2[j]((*Top(stack)).cmp, x.cmp);
                    Pop(&stack);
                    Push(&stack, tmp);
                }
            }
            continue;
        }
        tmp = *Top(stack);
        Pop(&stack);
        x.cmp = funcsOp[postfix[i].type]((*Top(stack)).cmp, tmp.cmp);
        Pop(&stack);
        Push(&stack, x);
    }
    var[*varSize].cmp = (*Top(stack)).cmp;
    Pop(&stack);
}