#include <stdio.h>
#include "polishnotation.h"
#define MAX_SIZE_OF_STR 300
#define MAX_SIZE_OF_VAR 20

void NewVar(LEKSEMA *var, int *varSize, char *str){
    int i;
    for(i = 0; *str!='=' && *str!=' '; str++, i++){
        var[*varSize].name[i] = *str;
    }
    var[*varSize].name[i] = '\0';
    while(*str==' ' || *str=='=')
        str++;
    ReversePolishNotation(var, varSize, &*str);
}

void ReadingFile(LEKSEMA *var, int *varSize){
    FILE* fr = fopen("input.txt", "rt");
    char buf[10][MAX_SIZE_OF_STR];
    if(!fr){
        printf("Error opening file for reading");
        exit(1);
    }
    int count=0;
    while(fgets(buf[count], MAX_SIZE_OF_STR, fr)){
        count++;
    }
    for(int i=count-1; i>=0; --i) {
        if(i!=0) {
            NewVar(var, varSize, buf[i]);
            (*varSize)++;
        }
        else {
            ReversePolishNotation(var, varSize, buf[i]);
            (*varSize)++;
        }
    }
    fclose(fr);
}

void PrintResult(LEKSEMA * var, int varSize){
    FILE * fw = fopen("output.txt", "wt");
    if(!fw){
        printf("Error opening file for writing");
        exit(1);
    }
    if(cimag(var[varSize-1].cmp) < 0)
        fprintf(fw, "Result: %.6f%.6fi\n", creal(var[varSize-1].cmp), cimag(var[varSize-1].cmp));
    else
        fprintf(fw, "Result: %.6f + %.6fi\n", creal(var[varSize-1].cmp), cimag(var[varSize-1].cmp));
    fclose(fw);
}

int main() {
    LEKSEMA var[MAX_SIZE_OF_VAR];
    int varSize = 0;
    ReadingFile(var, &varSize);
    PrintResult(var, varSize);
    return 0;
}