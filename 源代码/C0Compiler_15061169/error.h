#ifndef __ERROR_H_
#define __ERROR_H_

#include<stdio.h>
#include<stdlib.h>

const int MISSING_CHAR = 2;
const int MISSING_STR = 3;
const int MISSING_EQL = 4;
const int MISSING_SEMICOLON = 5;
const int MISSING_LPAREN = 6;
const int MISSING_RPAREN = 7;
const int MISSING_LBRACK = 8;
const int MISSING_RBRACK = 9;
const int MISSING_LBRACE = 10;
const int MISSING_RBRACE = 11;
const int MISSING_COLON = 12;
const int MISSING_COMMA = 13;
const int MISSING_MAIN = 14;
const int OUT_OF_RANGE_ARRAY = 15;
const int OUT_OF_RANGE_TABLE = 16;
const int OUT_OF_RANGE_STR = 17;
const int OUT_OF_RANGE_INT = 18;
const int INVALID_CHAR = 19;
const int INVALID_STR = 20;
const int INVALID_NAME = 21;
const int INVALID_CASE = 22;
const int INVALID_ASSIGN = 23;
const int SHOULD_BE_INT_OR_CHAR = 24;
const int SHOULD_BE_IDENTIFIER = 25;
const int SHOULD_BE_INTEGER_USINT = 26;
const int SHOULD_BE_CHARACTER = 27;
const int SHOULD_BE_ASSIGNSYM = 28;
const int CANNOT_BE_VOID_FUNCTION = 29;
const int INVALID_FUNCTION_DEC = 30;
const int INVALID_VARIABLE_DEC = 31;
const int INVALID_FUNCTION_HEAD = 32;
const int EXTRA_CHARACTER_AFTER_MAIN = 33;
const int SHOULD_BE_SCANF = 34;
const int SHOULD_BE_PRINTF = 35;
const int EMPTY_READ = 36;
const int SHOULD_BE_IFSYM = 37;
const int SHOULD_BE_ELSESYM = 38;
const int SHOULD_BE_WHILESYM = 39;
const int SHOULD_BE_SWITCHSYM = 40;
const int MISSING_CASE = 41;
const int DUPLICATE_DEF = 42;
const int RETURN_ERROR = 43;
const int INVALID_READ = 44;
const int DUPLICATE_CASE = 45;
const int INVALID_PARAMETER = 46;
const int SHOULD_BE_PARAMETER = 47;
const int NOT_DEFINE = 48;
const int SHOULD_BE_ARRAY = 49;
const int CANNOT_BE_ARRAY = 50;

extern int errorflag;
extern int error_count;
extern int skip_end[50];

void error(int errortype);
void skip();


#endif // _ERROR_H_
