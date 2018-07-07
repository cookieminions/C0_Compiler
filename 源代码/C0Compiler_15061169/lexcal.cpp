#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "compiler.h"
#include "error.h"

char ch;
char token[MAX_L];
char* symbolset[] = {
    "PLUS","MINUS","TIMES","DIV","LESSYM","LEQSYM","GRTSYM","GEQSYM","NEQSYM","EQLSYM",
    "LPAREN","RPAREN","LBRACK","RBRACK","LBRACE","RBRACE","COMMA","COLON","SEMICOLON",
    "INTEGER","USINT","CHARACTER","IDENTIFIER",
    "CONSTSYM","INTSYM","CHARSYM","VOIDSYM","MAINSYM","IFSYM","ELSESYM","WHILESYM","SWITCHSYM","CASESYM","DEFAULTSYM","ASSIGNSYM",
    "SCANFSYM","PRINTFSYM","RETURNSYM","STRSYM"};

char last_line[LINE_L];
char line[LINE_L];

int ch_count = 0;
int line_count = 1;
int record_ptr = 0;
int last_ptr = 0;
int record_num;
int ctr;
int errorflag;
int eofflag;

symbol sym;

FILE* fp;
FILE* fwp;

void getch(){
    ch = fgetc(fp);
    if(ch=='\n'){
        line[record_ptr]='\0';strcpy(last_line,line);last_ptr=record_ptr;
        //printf("%d %d %s\n",line_count,record_ptr,line);
        line_count++;record_ptr = 0;
        return;
    }
    line[record_ptr++]=(ch=='\t')?' ':ch;
}

void output(){
    if(errorflag==0){
        ch_count++;
        printf("%d %s %s\n",ch_count,symbolset[sym],token);
        fprintf(fwp,"%d %s %s\n",ch_count,symbolset[sym],token);
    }
}

void searchSym(){
    if(stricmp(token,"const")==0){sym=CONSTSYM;}
    else if(stricmp(token,"int")==0){sym=INTSYM;}
    else if(stricmp(token,"char")==0){sym=CHARSYM;}
    else if(stricmp(token,"void")==0){sym=VOIDSYM;}
    else if(stricmp(token,"main")==0){sym=MAINSYM;}
    else if(stricmp(token,"if")==0){sym=IFSYM;}
    else if(stricmp(token,"else")==0){sym=ELSESYM;}
    else if(stricmp(token,"switch")==0){sym=SWITCHSYM;}
    else if(stricmp(token,"case")==0){sym=CASESYM;}
    else if(stricmp(token,"default")==0){sym=DEFAULTSYM;}
    else if(stricmp(token,"while")==0){sym=WHILESYM;}
    else if(stricmp(token,"scanf")==0){sym=SCANFSYM;}
    else if(stricmp(token,"printf")==0){sym=PRINTFSYM;}
    else if(stricmp(token,"return")==0){sym=RETURNSYM;}
    else{sym=IDENTIFIER;}
}

void getsym(){
    //errorflag=0;
    while(ch==' '||ch=='\t'||ch=='\n'){
        getch();
    }
    if(ch=='_'||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){
        ctr=0;
        while(ch=='_'||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')){
            if(ctr<NAME_L){
                token[ctr++]=ch;
            }getch();
        }token[ctr]='\0';
        searchSym();
    }
    else if(ch>='0'&&ch<='9'){
        record_num = 0;ctr=0;
        if(ch=='0'){
            token[0]=ch;token[1]='\0';
            sym = INTEGER;getch();
            return;
        }
        while(ch>='0'&&ch<='9'){
            token[ctr++]=ch;
            record_num = record_num*10+(ch-'0');
            getch();
        }
        token[ctr]='\0';
        sym = USINT;
    }
    else if(ch=='\''){
        ctr=0;getch();
        token[ctr++]='\'';
        if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='_'||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')){
            token[ctr++]=ch;
            record_num=ch;
        }else{errorflag=1;error(INVALID_CHAR);}
        getch();
        if(ch=='\''){
            sym=CHARACTER;
            token[ctr++]='\'';token[ctr]='\0';
            getch();
        }else{
            errorflag=1;error(MISSING_CHAR);
        }
    }
    else if(ch=='"'){
        ctr=0;getch();
        token[ctr++]='"';
        while(ch!='"'&&ctr<MAX_L){
            if(ch!=32&&ch!=33&&!(ch>=35&&ch<=126)){
                errorflag=1;error(INVALID_STR);
                getch();
            }
            token[ctr++]=ch;
            getch();
        }
        if(ch=='"'){
            getch();
        }else{errorflag=1;error(MISSING_STR);getch();}
        token[ctr++]='"';token[ctr]='\0';
        sym = STRSYM;
    }
    else if(ch=='<'){
        getch();
        if(ch=='='){
            sym = LEQSYM;token[0]='<';token[1]='=';token[2]='\0';
            getch();
        }else{
            sym = LESSYM;token[0]='<';token[1]='\0';
        }
    }
    else if(ch=='>'){
        getch();
        if(ch=='='){
            sym = GEQSYM;token[0]='>';token[1]='=';token[2]='\0';
            getch();
        }else{
            sym = GRTSYM;token[0]='>';token[1]='\0';
        }
    }
    else if(ch=='='){
        getch();
        if(ch=='='){
            sym = EQLSYM;token[0]='=';token[1]='=';token[2]='\0';
            getch();
        }else{
            sym = ASSIGNSYM;token[0]='=';token[1]='\0';
        }
    }
    else if(ch=='!'){
        getch();
        if(ch=='='){
            sym = NEQSYM;token[0]='!';token[1]='=';token[2]='\0';
            getch();
        }else{
            errorflag=1;error(MISSING_EQL);
        }
    }
    else if(ch=='+'){sym=PLUS;token[0]=ch;token[1]='\0';getch();}
    else if(ch=='-'){sym=MINUS;token[0]=ch;token[1]='\0';getch();}
    else if(ch=='*'){sym=TIMES;token[0]=ch;token[1]='\0';getch();}
    else if(ch=='/'){sym=DIV;token[0]=ch;token[1]='\0';getch();}
    else if(ch=='('){sym=LPAREN;token[0]=ch;token[1]='\0';getch();}
    else if(ch==')'){sym=RPAREN;token[0]=ch;token[1]='\0';getch();}
    else if(ch=='['){sym=LBRACK;token[0]=ch;token[1]='\0';getch();}
    else if(ch==']'){sym=RBRACK;token[0]=ch;token[1]='\0';getch();}
    else if(ch=='{'){sym=LBRACE;token[0]=ch;token[1]='\0';getch();}
    else if(ch=='}'){sym=RBRACE;token[0]=ch;token[1]='\0';getch();}
    else if(ch==','){sym=COMMA;token[0]=ch;token[1]='\0';getch();}
    else if(ch==':'){sym=COLON;token[0]=ch;token[1]='\0';getch();}
    else if(ch==';'){sym=SEMICOLON;token[0]=ch;token[1]='\0';getch();}
    else{
        if(ch==-1)  eofflag = 1;
        return;
    }
}
