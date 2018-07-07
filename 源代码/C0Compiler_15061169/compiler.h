#ifndef _COMPILER_H_
#define _COMPILER_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int NAME_L = 50;
const int NUM_L = 10;
const int OPERAND_L = 20;
const int MIPS_L = 120;
const int LINE_L = 1000;

const int MAX_L = 100;
const int MAX_T = 1000;
const int MAX_Q = 2000;

const int REGS_N = 10;
const int PARA_N = 8;

typedef enum {
    PLUS,MINUS,TIMES,DIV,//+,-,*,/
    LESSYM,LEQSYM,GRTSYM,GEQSYM,NEQSYM,EQLSYM,//<,<=,>,>=,!=,==
    LPAREN,RPAREN,LBRACK,RBRACK,LBRACE,RBRACE,COMMA,COLON,SEMICOLON,//(,),[,],{,}, , ,:,;
    INTEGER,USINT,CHARACTER,IDENTIFIER,//number,unsigned number
    CONSTSYM,INTSYM,CHARSYM,VOIDSYM,MAINSYM,IFSYM,ELSESYM,WHILESYM,SWITCHSYM,CASESYM,DEFAULTSYM,ASSIGNSYM,//const,int,char,void,main,if,while,switch,case,default,=
    SCANFSYM,PRINTFSYM,RETURNSYM,STRSYM//scanf,printf,return,string
} symbol;

typedef enum{
    INTTYP,CHARTYP,VOIDTYP
}types;
typedef enum{
    CONSTANT,VARIABLE,FUNCTION,PARAMETER,ARRAY
}object;

///dec_const int/char, name, val;
///dec_val int/char, name, ;
///dec_Arr int/char name, arr_size;
///dec_func , , name;
///dec_para int/char, name, ;
///dec_label , , name;
///op_assignNum , tempvar, val;
///op_assignVal (tempvar), name, tempvar;
///op_getVal (tempvar), name, tempvar;
///op_getFuncVal , name, tempvar;
///sys_read , , name;
///sys_return , , (tempvar);
typedef enum{
    dec_const,dec_var,dec_Arr,dec_func,dec_para,dec_label,
    op_add,op_sub,op_mult,op_div,op_assignNum,op_assignVal,op_getVal,op_getFuncVal,op_para,
    op_j,op_jal,op_beq,op_bne,op_blt,op_ble,op_bgt,op_bge,
    sys_read,sys_write,sys_return,sys_exit
}operator_quadruple;
//(op,operand1,operand2,result)

typedef struct{
    operator_quadruple op;
    char operand1[OPERAND_L];
    char operand2[OPERAND_L];
    char result[OPERAND_L];
}quadruple;

typedef struct {
    int parents[MAX_L];
    int left_child;
    int right_child;

    int index;
    int parents_index;
    operator_quadruple op;
    int used;
}node;
typedef struct{
    char var_name[NAME_L];
    int var_node;
    int used_node[MAX_L];
}table_node;

//���ű����
//���ű�
typedef struct{
    char name[NAME_L]; //����
    object obj; //����
    types type; //����
    int val;//������ֵ
	int arr_size;//�����С
	int para_num;//������������

    int link; //��һ����¼�ڷ��ű��е�λ��
    int offset;//mips��Ҫ �������ƫ�Ƶ�ַ���ڼ���������
}table;

extern node nodes[MAX_Q];
extern char ch;
extern char token[MAX_L];
extern char line[LINE_L];
extern char last_line[LINE_L];
extern char* symbolset[];

extern int ctr;
extern int line_count;

extern int eofflag;
extern int retflag;
extern int mainflag;

extern int record_num;
extern symbol record_sym;
extern types record_type;
extern int record_field;
extern int record_offset;
extern int record_ptr;
extern int last_ptr;

extern bool legal_func_dec;
extern bool finish_var_dec;

extern symbol sym;

extern table tables[MAX_T];
extern int display[MAX_T];
extern char str_tables[MAX_T][MAX_L];
extern quadruple quadruple_list[MAX_Q];
extern char mips_code[3*MAX_Q][MIPS_L];

extern int Ttable_index;
extern int Stable_index;
extern int Qlist_index;
extern int display_index;
extern int Mips_index;

extern FILE* fp;
extern FILE* fwp;
extern FILE* mipsfp;

//�ʷ�����
void getch();
void searchSym();
void output();
void getsym();

//�﷨����
void dec_constant();//����˵��
void dec_variableTofunction();//����˵��
void dec_function();//��������
void parameterlist();//�����б�
void mainfunc();//������
void compound_statement();//�������
void statement_list();//�����
void statement();//���

void expression();//���ʽ
void term();//��
void factor();//����

void statement_ifelse();//�������
void statement_while();//ѭ�����
void functioncall();//��������
void statement_assign();//��ֵ���
void statement_read();//�����
void statement_write();//д���
void statement_switch();//������
void statement_return();//�������

//�������
int  search_table(char name[NAME_L],int field_flag,int def_flag); //loc
void enter_table(char name[NAME_L],object o,types typ);

//��ӡ��Ϣ
void print_table();
void print_Qlist();
void print_display();
void print_mips();

//�����м����
void record_quadruple(operator_quadruple op,char operand1[OPERAND_L],char operand2[OPERAND_L],char result[OPERAND_L]);

//����mips
void generate_code(quadruple q_i);
void generate_mips();

char* get_reg(int tempvar);
void push_stack(quadruple q_i, int len);

//�����Ż�

#endif // _COMPILER_H


