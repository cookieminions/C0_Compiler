#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "error.h"
#include "compiler.h"

char * errorouput[] = {
    "tmp error",
    "tmp error",
    "miss right apostrophe or out of character [']",
    "miss right quote or out of string [\"]",
    "miss assignment [=]",
    "miss semicolon [;]",
    "miss left paren [(]",
    "miss right paren [)]",
    "miss left brack [[]",
    "miss right brack []]",
    "miss left brace [{]",
    "miss right brace [}]",
    "miss colon [:]",
    "miss comma [,]",
    "miss main function [main]",
    "array out of range [out]",
    "table out of range [out]",
    "string's length out of range [out]",
    "integer's length out of range [out]",
    "invalid character [invalid]",
    "invalid character in string [invalid]",
    "invalid identifier name [invalid]",
    "case's next should be an integer or character constant ['a' or 1]",
    "cannot assign constants [no=]",
    "there should be symbol int or char [int]",
    "there should be an identifier [ident]",
    "there should be an integer or unsigned integer [+1]",
    "there should be a character ['a']",
    "there should be an assignment [=]",
    "cannot be void function [void]",
    "invalid function declaration [invalid]",
    "invalid variable declaration [invalid]",
    "invalid function declaration head(should be int or char or void) [invalid]",
    "there are extra characters after main function [extra]",
    "there should be symbol scanf [scanf]",
    "there should be symbol printf [printf]",
    "cannot read empty [ ]",
    "there should be symbol if [if]",
    "there should be symbol else [else]",
    "there should be symbol while [while]",
    "there should be symbol switch [switch]",
    "miss case [case]",
    "duplicate definition [dup,dup]",
    "function does not have return value [no return]",
    "in read statement the identifier need to be variable or parameter [var,par]",
    "duplicate case value [dup,case]",
    "invalid function parameter [invalid]",
    "there should be parameter [par]",
    "not define [no def]",
    "there should be array [arr[]]",
    "there cannot be array [!arr[]]"
};
int error_count = 0;
int skip_end[50] = {0};

void error(int errortype){
    error_count++; errorflag=1;
    line[record_ptr]='\0';
    //printf("%d\n",record_ptr);
    printf("Error[%d]: %s\n",errortype,errorouput[errortype]);
    fprintf(fwp,"Error[%d]: %s\n",errortype,errorouput[errortype]);
    if(record_ptr!=0){
        //printf("0");
        printf("line[%d]: %s\n",line_count,line);
        printf("          %*c\n",record_ptr,'^');
        fprintf(fwp,"line[%d]: %s\n",line_count,line);
        fprintf(fwp,"          %*c\n",record_ptr,'^');
    }
    else{
        //printf("1");
        printf("line[%d]: %s\n",line_count-1,last_line);
        printf("          %*c\n",last_ptr,'^');
        fprintf(fwp,"line[%d]: %s\n",line_count-1,last_line);
        fprintf(fwp,"          %*c\n",last_ptr,'^');
    }
    //fprintf(fwp,"error: %s\n",errorouput[errortype]);
}

void skip(){
    while(skip_end[sym]==0){
        //printf("skip\n");
        getsym();
    }
}
