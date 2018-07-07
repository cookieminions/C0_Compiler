#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "compiler.h"
#include "error.h"

int retflag;
int mainflag;

bool legal_func_dec;
bool finish_var_dec;
bool tmp_record_dec;

symbol record_sym;
types  record_type;
int    record_field;
int    record_offset;
int    record_typechange;
int    record_arrnum;

int label_num = 0;
int tempvar_num = 0;

int upload_var;
char temp_var_t[NAME_L]="#t";

table tables[MAX_T];
char str_tables[MAX_T][MAX_L];
int display[MAX_T];
quadruple quadruple_list[MAX_Q];

int Ttable_index = 0;//���ű�
int Stable_index = 0;
int Qlist_index = 0;
int display_index = 0;


//�������
void enter_table(char name[NAME_L],object o,types typ){
    if(Ttable_index>=MAX_T-1){
        error(OUT_OF_RANGE_TABLE);
    }
    strcpy(tables[++Ttable_index].name,name);
    tables[Ttable_index].obj = o;
    tables[Ttable_index].type = typ;

    tables[Ttable_index].para_num = 0;
    tables[Ttable_index].val = 0;
    tables[Ttable_index].arr_size = 0;

    tables[Ttable_index].link = Ttable_index-1;
    tables[Ttable_index].offset = record_offset;
}

int search_table(char name[NAME_L],int field_flag,int def_flag){//field_flag��ʾ��������ʱ��� def_flag��ʾ�����ͱ�������ʱ���
    if(Ttable_index>=MAX_T-1){
        error(OUT_OF_RANGE_TABLE);
        return -1;
    }
    int i = Ttable_index;
    if(field_flag==1) i=record_field;//����������ȫ�ֶ���
    while(stricmp(tables[i].name,name)!=0){
        i = tables[i].link;
        if(def_flag==1&&record_field!=-1){//�������������ʱ����ű�//record_field==-1��ʾ��ȫ�ֱ�������
            if(i==tables[record_field].link){//��ʾi�Ѿ��ں�������������
                i=-1;//�ж�
                break;
            }
        }else{//����ʱ�̲��//������������ʱ���
            if(i==0) break;
        }
    }
    if(i>0){
        return i;
    }return -1;
}

int search_strtables(char str[MAX_L]){
    for(int i=1;i<=Stable_index;i++){
        if(strcmp(str_tables[i],str)==0){
            return i;
        }
    }
    return -1;
}

void record_quadruple(operator_quadruple op,char operand1[OPERAND_L],char operand2[OPERAND_L],char result[OPERAND_L]){//��Ҫ���˸�ֵ������ĳЩ����������ת��
    if(Qlist_index>=MAX_Q-1){
        error(OUT_OF_RANGE_TABLE);
        return;
    }
    quadruple_list[++Qlist_index].op = op;
    strcpy(quadruple_list[Qlist_index].operand1,operand1);
    strcpy(quadruple_list[Qlist_index].operand2,operand2);
    strcpy(quadruple_list[Qlist_index].result,result);
}

void generate_label(char templab[NAME_L]){
    char label_num_str[NUM_L];
    sprintf(label_num_str,"%d",++label_num);
    templab[3]='\0'; strcat(templab,label_num_str);
}
void generate_tempvar(char tempvar[NAME_L],int upload_flag){
    char var_num_str[NUM_L];
    //upload_var = tempvar_num;
    if(upload_flag==0){
        sprintf(var_num_str,"%d",++tempvar_num);
    }else{
        sprintf(var_num_str,"%d",upload_var);
    }
    tempvar[2]='\0'; strcat(tempvar,var_num_str);
}

//�﷨����
//����int����
void deal_int_constant(){
    getsym();
    if(sym==IDENTIFIER){
        int index = search_table(token,0,1);//��� �������������Ѿ�������򱨴�
        if(index>0){
            error(DUPLICATE_DEF);
        }else{
            enter_table(token,CONSTANT,INTTYP);
            record_offset = record_offset+4;
        }
        getsym();
        if(sym==ASSIGNSYM){
            getsym();
            int sign = (sym==MINUS)?-1:1;
            if(sym==MINUS||sym==PLUS)   getsym();
            if(sym==INTEGER||sym==USINT){
                tables[Ttable_index].val = (sign*record_num); char val_int[NUM_L];sprintf(val_int,"%d",sign*record_num);
                record_quadruple(dec_const,"int",tables[Ttable_index].name,val_int);
                getsym();   //printf("this is an int constant.\n");
            }else{error(SHOULD_BE_INTEGER_USINT);skip();}

        }else{error(SHOULD_BE_ASSIGNSYM);skip();}
    }else{error(SHOULD_BE_IDENTIFIER);}
}
//����char����
void deal_char_constant(){
    getsym();
    if(sym==IDENTIFIER){
        int index = search_table(token,0,1);
        if(index>0){
            error(DUPLICATE_DEF);
        }else{
            enter_table(token,CONSTANT,CHARTYP);
            record_offset = record_offset+4;
        }
        getsym();
        if(sym==ASSIGNSYM){
            getsym();
            if(sym==CHARACTER){
                tables[Ttable_index].val = record_num;  char val_char[] = "' '";val_char[1]=record_num;
                record_quadruple(dec_const,"char",tables[Ttable_index].name,val_char);
                getsym();   //printf("this is a char constant.\n");
            }else{error(SHOULD_BE_CHARACTER);skip();}
        }else{error(SHOULD_BE_ASSIGNSYM);skip();}
    }else{error(SHOULD_BE_IDENTIFIER);}
}
//������
void dec_constant(){
    skip_end[CONSTSYM]+=1;
    while(sym==CONSTSYM){
        skip_end[INTSYM]+=1;skip_end[CHARSYM]+=1;skip_end[SEMICOLON]+=1;
        getsym();
        if(sym!=INTSYM&&sym!=CHARSYM){
            error(SHOULD_BE_INT_OR_CHAR);
            skip();
        }
        if(sym==INTSYM){
            do{
                deal_int_constant();
            }while(sym==COMMA);
        }
        else if(sym==CHARSYM){
            do{
                deal_char_constant();
            }while(sym==COMMA);
        }skip_end[INTSYM]-=1;skip_end[CHARSYM]-=1;skip_end[SEMICOLON]-=1;
        if(sym!=SEMICOLON){
            error(MISSING_SEMICOLON);skip_end[SEMICOLON]+=1;
            skip();skip_end[SEMICOLON]-=1;
        }
        else {getsym();}
    }skip_end[CONSTSYM]-=1;
}
//����int����
void deal_int_variable(){
    getsym();
    if(sym==IDENTIFIER){
        int index = search_table(token,0,1);
        if(index>0){error(DUPLICATE_DEF);}
        else{
            enter_table(token,VARIABLE,INTTYP);
            record_offset = record_offset+4;
        }
        getsym();
        if(sym==LBRACK){//����
            tables[Ttable_index].obj = ARRAY;
            getsym();   //printf("this is an int variable.\n");
            if(sym==USINT){
                getsym();
                tables[Ttable_index].arr_size = record_num; char val_int[NUM_L];sprintf(val_int,"%d",record_num);
                record_offset = record_offset+record_num*4-4;
                record_quadruple(dec_Arr,"int",tables[Ttable_index].name,val_int);
                if(sym==RBRACK){getsym();}
                else{
                    error(MISSING_RBRACK);
                    skip();
                }
            }else{
                error(SHOULD_BE_INTEGER_USINT);//skip_end[USINT]+=1;
                skip();//skip_end[USINT]-=1;
            }
        }
        else if(sym==LBRACE||sym==LPAREN){//����
            finish_var_dec = true;
            if(legal_func_dec&&tmp_record_dec){//��ֹ���ֱ����ͺ���һ������ int a,func(){};
                record_field = (record_field==-1)?Ttable_index-1:record_field;
                record_quadruple(op_jal,"","","main");
                skip_end[INTSYM]-=1;skip_end[CHARSYM]-=1;skip_end[SEMICOLON]-=1;skip_end[COMMA]-=1;skip_end[VOIDSYM]-=1;
                retflag=1; dec_function();
            }else{error(INVALID_FUNCTION_DEC);}
            return;
        }
        else if(sym==COMMA||sym==SEMICOLON){
            record_quadruple(dec_var,"int",tables[Ttable_index].name,"");
            //printf("this is an int variable.\n");
            return;
        }
        else{error(INVALID_VARIABLE_DEC);skip();}
    }else{
        error(SHOULD_BE_IDENTIFIER);skip_end[IDENTIFIER]+=1;
        skip();skip_end[IDENTIFIER]-=1;
    }
}
//����char����
void deal_char_variable(){
    getsym();
    if(sym==IDENTIFIER){
        int index = search_table(token,0,1);
        if(index>0){error(DUPLICATE_DEF);}
        else{
            enter_table(token,VARIABLE,CHARTYP);
            record_offset = record_offset+4;
        }
        getsym();
        if(sym==LBRACK){//����
            tables[Ttable_index].obj = ARRAY;
            getsym();   //printf("this is a char variable.\n");
            if(sym==USINT){
                getsym();
                tables[Ttable_index].arr_size = record_num; char val_int[NUM_L];sprintf(val_int,"%d",record_num);
                record_offset = record_offset+record_num*4-4;
                record_quadruple(dec_Arr,"char",tables[Ttable_index].name,val_int);
                if(sym==RBRACK){getsym();}
                else{
                    error(MISSING_RBRACK);//skip_end[VOIDSYM]+=1;
                    skip();//skip_end[VOIDSYM]-=1;
                }
            }else{
                error(SHOULD_BE_INTEGER_USINT);//skip_end[USINT]+=1;
                skip();//skip_end[USINT]-=1;
            }
        }
        else if(sym==LBRACE||sym==LPAREN){//����
            finish_var_dec = true;
            if(legal_func_dec&&tmp_record_dec){//��ֹ���ֱ����ͺ���һ������ int a,func(){};��������statement������������
                record_field = (record_field==-1)?Ttable_index-1:record_field;//��¼������ ��������������ȫ���������
                record_quadruple(op_jal,"","","main");
                skip_end[INTSYM]-=1;skip_end[CHARSYM]-=1;skip_end[SEMICOLON]-=1;skip_end[COMMA]-=1;skip_end[VOIDSYM]-=1;
                retflag=2; dec_function();
            }else{error(INVALID_FUNCTION_DEC);}
            return;
        }
        else if(sym==COMMA||sym==SEMICOLON){
            record_quadruple(dec_var,"char",tables[Ttable_index].name,"");
            //printf("this is a char variable.\n");
            return;
        }
        else{error(INVALID_VARIABLE_DEC);skip();}
    }else{
        error(SHOULD_BE_IDENTIFIER);skip_end[IDENTIFIER]+=1;
        skip();skip_end[IDENTIFIER]-=1;
    }
}
//���������������������
void dec_variableTofunction(){
    skip_end[INTSYM]+=1;skip_end[CHARSYM]+=1;
    finish_var_dec = false;
    while(!finish_var_dec&&(sym==INTSYM||sym==CHARSYM)){//�ڳ������ȶ�������ٶ��庯�� �ڸ�������в��ܶ��庯��
        skip_end[SEMICOLON]+=1;skip_end[COMMA]+=1;skip_end[VOIDSYM]+=1;
        if(sym==INTSYM){
            do{
                tmp_record_dec = true;
                deal_int_variable();
                tmp_record_dec = false;
            }while(!finish_var_dec&&sym==COMMA);
        }
        else if(sym==CHARSYM){
            do{
                tmp_record_dec = true;
                deal_char_variable();
                tmp_record_dec = false;
            }while(!finish_var_dec&&sym==COMMA);
        }
        else{
            error(SHOULD_BE_INT_OR_CHAR);
        }skip_end[SEMICOLON]-=1;skip_end[COMMA]-=1;skip_end[VOIDSYM]-=1;
        if(!finish_var_dec){
            if(sym!=SEMICOLON){
                error(MISSING_SEMICOLON);skip_end[SEMICOLON]+=1;
                skip();skip_end[SEMICOLON]-=1;
            }
            else{getsym();}
        }
    }skip_end[INTSYM]-=1;skip_end[CHARSYM]-=1;
}
//����������
void dec_function(){
    //printf("this is a function.\n");
    legal_func_dec = false; record_offset = 0;
    tables[Ttable_index].obj=FUNCTION;//������������ת�ƹ���ʱ��¼���ű�����͸Ĺ���
    tables[Ttable_index].link=record_field;  record_field=Ttable_index;//���������;ֲ����������ں����ڲ��������
    display[++display_index] = Ttable_index;
    record_quadruple(dec_func,"","",tables[Ttable_index].name);
    //record_quadruple(dec_label,"","",tables[Ttable_index].name);
    //skip_end[INTSYM]+=1;skip_end[CHARSYM]+=1;skip_end[SEMICOLON]+=1;
    skip_end[RBRACE]+=1;
    if(sym==LPAREN){
        parameterlist();
        if(sym==LBRACE){
            compound_statement();
            if(sym!=RBRACE){
                error(MISSING_RBRACE);//skip();
            }
            else{getsym();}
            if(retflag==1||retflag==2)  error(RETURN_ERROR);
            else{retflag=0; record_quadruple(sys_return,"","","");}
        }else{
            error(MISSING_LBRACE);//skip();
        }//������LBRACE �᲻�ᵽĳЩ��ֵĵط� ����ifelse ������һ������...
    }
    else if(sym==LBRACE){
        compound_statement();
        if(sym!=RBRACE){
            error(MISSING_RBRACE);
            skip();
        }
        else{getsym();}
        if(retflag==1||retflag==2)  error(RETURN_ERROR);
        else{retflag=0; record_quadruple(sys_return,"","","");}
    }

    if(sym==INTSYM||sym==CHARSYM){
        record_type = (sym==INTSYM)?INTTYP:CHARTYP;
        getsym();
        if(sym==IDENTIFIER){
            if(search_table(token,1,0)>0){error(DUPLICATE_DEF);}
            else{
                enter_table(token,FUNCTION,record_type);
                record_field = (record_field==-1)?Ttable_index-1:record_field;
            }getsym();
            retflag=(record_type==INTTYP)?1:2; dec_function();
        }else{
            error(SHOULD_BE_IDENTIFIER);//skip_end[IDENTIFIER]+=1;
            //skip();skip_end[IDENTIFIER]-=1;
        }
    }
    else if(sym==VOIDSYM){
        getsym();
        if(sym==IDENTIFIER){
            if(search_table(token,1,0)>0){error(DUPLICATE_DEF);}
            else{
                enter_table(token,FUNCTION,VOIDTYP);
                record_field = (record_field==-1)?Ttable_index-1:record_field;
            }getsym();
            retflag=-1; dec_function();
        }
        else if(sym==MAINSYM){
            getsym();
            mainfunc();
            return;
        }
        else{
            error(SHOULD_BE_IDENTIFIER);//skip_end[IDENTIFIER]+=1;
            //skip();skip_end[IDENTIFIER]-=1;
        }
    }
    else{error(INVALID_FUNCTION_HEAD);skip();}
    skip_end[RBRACE]-=1;
    //skip_end[INTSYM]-=1;skip_end[CHARSYM]-=1;skip_end[SEMICOLON]-=1;
}
//����������
void mainfunc(){
    legal_func_dec = false; skip_end[RBRACE]+=1;
    retflag = 3;  record_offset = 0;  mainflag = 1;
    if(search_table("main",1,0)>0){error(DUPLICATE_DEF);}
    else{
        enter_table("main",FUNCTION,VOIDTYP);
        tables[Ttable_index].link=(record_field==-1)?Ttable_index-1:record_field;  record_field=Ttable_index;
        display[++display_index] = Ttable_index;
    }printf("this is main function.\n");
    record_quadruple(dec_func,"","","main");
    if(sym==LPAREN){
        getsym();
        if(sym==RPAREN){
            getsym();
            if(sym==LBRACE){
                compound_statement();
                if(sym==RBRACE){
                    //if(!retflag){}
                    //retflag=0;record_quadruple(sys_return,"","","");
                    do{getch();}while(ch==' '||ch=='\t'||ch=='\n');
                    if(ch!=-1){error(EXTRA_CHARACTER_AFTER_MAIN);}
                    return;
                }else{error(MISSING_RBRACE);skip();}
            }else{error(MISSING_LBRACE);skip();}
        }else{error(MISSING_RPAREN);skip();}
    }else{error(MISSING_LPAREN);skip();}
    skip_end[RBRACE]-=1;
}
//�����������б�
void parameterlist(){
    int para_num = 0;
    skip_end[INTSYM]+=1;skip_end[CHARSYM]+=1;
    if(sym==LPAREN){
        do{
            getsym();   //printf("this is a parameter.\n");
            if(sym==INTSYM||sym==CHARSYM){
                record_type = (sym==INTSYM)?INTTYP:CHARTYP;
                getsym();
                if(sym==IDENTIFIER){
                    if(search_table(token,0,1)>0){error(DUPLICATE_DEF);}
                    else{
                        enter_table(token,PARAMETER,record_type);//��¼��������
                        record_offset = record_offset+4;
                        char val_inttype[]="int";char val_chartype[]="char";
                        record_quadruple(dec_para,(record_type==INTTYP)?val_inttype:val_chartype,tables[Ttable_index].name,"");
                        para_num++;//ͳ�Ʋ�������
                    }   getsym();
                }else{
                    error(SHOULD_BE_IDENTIFIER);skip_end[COMMA]+=1;
                    skip();skip_end[COMMA]-=1;
                }
            }else{
                error(SHOULD_BE_INT_OR_CHAR);//skip_end[COMMA]+=1;
                //skip();skip_end[COMMA]-=1;
            }
        }while(sym==COMMA);
        tables[Ttable_index-para_num].para_num = para_num;//��¼������������
        if(sym==RPAREN){
            getsym();
        }else{
            error(MISSING_RPAREN);//skip_end[LBRACE]+=1;
            skip();//skip_end[LBRACE]-=1;
        }//
    }else{error(MISSING_LPAREN);}
    skip_end[INTSYM]-=1;skip_end[CHARSYM]-=1;
}
//���������
void compound_statement(){
    getsym();
    if(sym==CONSTSYM){
        dec_constant();
    }
    if(sym==INTSYM||sym==CHARSYM){
        dec_variableTofunction();
        finish_var_dec = true;
    }
    statement_list();
}
//���������
void statement_list(){
    skip_end[IFSYM]+=1;skip_end[WHILESYM]+=1;skip_end[SWITCHSYM]+=1;skip_end[SCANFSYM]+=1;skip_end[PRINTFSYM]+=1;
    skip_end[IDENTIFIER]+=1;skip_end[RETURNSYM]+=1;skip_end[SEMICOLON]+=1;skip_end[LBRACE]+=1;
    while(sym==IFSYM||sym==WHILESYM||sym==SWITCHSYM||sym==SCANFSYM||sym==PRINTFSYM||sym==IDENTIFIER||sym==RETURNSYM||sym==SEMICOLON||sym==LBRACE){
        statement();
    }
    skip_end[IFSYM]-=1;skip_end[WHILESYM]-=1;skip_end[SWITCHSYM]-=1;skip_end[SCANFSYM]-=1;skip_end[PRINTFSYM]-=1;
    skip_end[IDENTIFIER]-=1;skip_end[RETURNSYM]-=1;skip_end[SEMICOLON]-=1;skip_end[LBRACE]-=1;
}
//�������
void statement(){
    if(sym==IFSYM){
        statement_ifelse();
    }
    else if(sym==WHILESYM){
        statement_while();
    }
    else if(sym==SWITCHSYM){
        statement_switch();
    }
    else if(sym==SCANFSYM){
        statement_read();
    }
    else if(sym==PRINTFSYM){
        statement_write();
    }
    else if(sym==IDENTIFIER){
        int index = search_table(token,0,0);
        //printf("%s %d\n",token,index);
        if(index<=0){error(NOT_DEFINE);}
        if(tables[index].obj==FUNCTION){
            functioncall();
            if(sym==SEMICOLON){getsym();}
            else{error(MISSING_SEMICOLON);skip();}
        }else{
            statement_assign();
        }
    }
    else if(sym==RETURNSYM){
        statement_return();
    }
    else if(sym==SEMICOLON){
        //printf("this is empty statement.\n");
        getsym();
    }
    else if(sym==LBRACE){
        getsym();
        statement_list();
        if(sym==RBRACE){getsym();}
        else{error(MISSING_RBRACE);}
    }
    else{
        return;
    }
}
//�����������
void statement_ifelse(){
    if(sym!=IFSYM){
        error(SHOULD_BE_IFSYM);
    }
    getsym();   //printf("this is if statement.\n");
    operator_quadruple record_op;
    char temp_lab1[NAME_L]="lab",temp_lab2[NAME_L]="lab";
    char temp_var1[NAME_L]="#t", temp_var2[NAME_L]="#t";
    if(sym==LPAREN){
        getsym();
        expression();//temp_var1
        generate_tempvar(temp_var1,1);
        if(sym!=RPAREN){
            switch(sym){
                case LESSYM:record_op=op_bge;break;
                case LEQSYM:record_op=op_bgt;break;
                case GRTSYM:record_op=op_ble;break;
                case GEQSYM:record_op=op_blt;break;
                case EQLSYM:record_op=op_bne;break;
                case NEQSYM:record_op=op_beq;break;
                default:error(0);
            }//printf("this is a relational operator.\n");
            getsym(); expression();//temp_var2
            generate_tempvar(temp_var2,1);
            generate_label(temp_lab1);
            record_quadruple(record_op,temp_var1,temp_var2,temp_lab1);//2,3����������ʱ������
            if(sym!=RPAREN){error(MISSING_RPAREN);}
            else{getsym();}
        }else{//sym==RPAREN
            generate_label(temp_lab1);
            record_quadruple(op_beq,temp_var1,"0",temp_lab1);
            getsym();
        }
        statement();//�Դ�getsym()
        generate_label(temp_lab2);
        record_quadruple(op_j,"","",temp_lab2);
        record_quadruple(dec_label,"","",temp_lab1);
        if(sym==ELSESYM){
            getsym();   //printf("this is else statement.\n");
            statement();
            record_quadruple(dec_label,"","",temp_lab2);
        }else{error(SHOULD_BE_ELSESYM);}
    }else{
        error(MISSING_LPAREN);
    }
}
//����while���
void statement_while(){
    if(sym!=WHILESYM){
        error(SHOULD_BE_WHILESYM);
    }
    getsym();   //printf("this is while statement.\n");
    operator_quadruple record_op;
    char temp_lab1[NAME_L]="lab",temp_lab2[NAME_L]="lab";
    char temp_var1[NAME_L]="#t", temp_var2[NAME_L]="#t";
    generate_label(temp_lab1); generate_label(temp_lab2);
    record_quadruple(dec_label,"","",temp_lab1);
    if(sym==LPAREN){
        getsym(); expression();//temp_var1
        generate_tempvar(temp_var1,1);
        if(sym!=RPAREN){
            switch(sym){
                case LESSYM:record_op=op_bge;break;
                case LEQSYM:record_op=op_bgt;break;
                case GRTSYM:record_op=op_ble;break;
                case GEQSYM:record_op=op_blt;break;
                case EQLSYM:record_op=op_bne;break;
                case NEQSYM:record_op=op_beq;break;
                default:error(0);
            }//printf("this is a relational operator.\n");
            getsym(); expression();//temp_var2
            generate_tempvar(temp_var2,1);
            record_quadruple(record_op,temp_var1,temp_var2,temp_lab2);
            if(sym!=RPAREN){error(MISSING_RPAREN);}
            else{getsym();}
        }else{
            generate_label(temp_lab2);
            record_quadruple(op_beq,temp_var1,"0",temp_lab2);
            getsym();
        }
        statement();
        record_quadruple(op_j,"","",temp_lab1);
        record_quadruple(dec_label,"","",temp_lab2);
    }else{
        error(MISSING_LPAREN);
    }
}
//����case�������
void deal_case(char end_label[NAME_L],int case_table[64]){
    int case_count=0;
    int case_type = record_typechange;
    while(sym==CASESYM){
        getsym();   //printf("this is case.\n");
        int sign = (sym==MINUS)?-1:1;
        if(sym==MINUS||sym==PLUS){
            getsym();
            if(sym!=INTEGER&&sym!=USINT){error(SHOULD_BE_INTEGER_USINT);}//���������mark������
        }
        if(sym==INTEGER||sym==USINT){//�����и����� ����+-֮�󲻽����ֽ��ַ����û�б��� =.= markһ��
            if(case_type==0){error(SHOULD_BE_CHARACTER);}//case �������ÿ������������Ҫ��switch�ı��ʽ����ͳһ
            record_num=sign*record_num;
            getsym();
        }
        else if(sym==CHARACTER){
            if(case_type!=0){error(SHOULD_BE_INTEGER_USINT);}
            getsym();
        }
        else{error(INVALID_CASE);}

        for(int i=0;i<case_count;i++){//����ظ���case����
            if(case_table[i]==record_num){error(DUPLICATE_CASE);}
        }case_table[case_count++]=record_num;

        char temp_record_var[NAME_L]; char temp_lab[NAME_L]="lab";
        sprintf(temp_record_var,"%d",record_num);//Ҫ��Ҫ��¼һ����char����int ��Ҫ,��mips��ȡ����������ascii���������� ֻ�������ʱ����Ҫ��עһ�°���char���
        generate_label(temp_lab);
        record_quadruple(op_bne,temp_var_t,temp_record_var,temp_lab);

        if(sym!=COLON){error(MISSING_COLON);}
        else{getsym();}
        char record_var_t[NAME_L];strcpy(record_var_t,temp_var_t);
        statement();
        strcpy(temp_var_t,record_var_t);

        record_quadruple(op_j,"","",end_label);
        record_quadruple(dec_label,"","",temp_lab);
    }
}
//����default
void deal_default(){
    if(sym==DEFAULTSYM){
        getsym();   //printf("this is default.\n");
        if(sym==COLON){
            getsym();
            statement();//������Ϊ�� ���ǿ����������зֺŵ�
            if(sym==RBRACE) {getsym();}
            else{error(MISSING_RBRACE);}
        }else{error(MISSING_COLON);}
    }
    else if(sym==RBRACE){getsym();}
    else{error(MISSING_RBRACE);}
}
//����switch���
void statement_switch(){
    if(sym!=SWITCHSYM){
        error(SHOULD_BE_SWITCHSYM);
    }
    getsym();   //printf("this is switch statement.\n");
    char end_label[NAME_L]="lab";
    generate_label(end_label);
    int case_table[64]={0};//�ж�case��û���ظ�����
    if(sym==LPAREN){
        getsym();
        record_typechange=0; expression();
        generate_tempvar(temp_var_t,1);
        if(sym!=RPAREN){
            error(MISSING_RPAREN);
        }
        getsym();
        if(sym==LBRACE){
            getsym();
            if(sym==CASESYM){
                deal_case(end_label,case_table);
            }
            else{
                error(MISSING_CASE);
            }
            deal_default();
            record_quadruple(dec_label,"","",end_label);
        }else{error(MISSING_LBRACE);}
    }
    else{
        error(MISSING_LPAREN);//skip();
    }
}
//����ֵ���
void statement_assign(){
    if(sym!=IDENTIFIER){
        error(SHOULD_BE_IDENTIFIER);
    }
    int index = search_table(token,0,0);
    if(index<=0){error(NOT_DEFINE);}
    if(tables[index].obj==CONSTANT){
        error(INVALID_ASSIGN);
    }
    getsym();   //printf("this is assign statement.\n");
    char temp_var1[NAME_L]="#t", temp_var2[NAME_L]="#t";
    if(sym==ASSIGNSYM){
        getsym();
        record_typechange=0; expression();
        if(tables[index].type==CHARTYP&&record_typechange!=0){error(SHOULD_BE_CHARACTER);}//int��ֵ��char�����ǲ������
        generate_tempvar(temp_var1,1);
        record_quadruple(op_assignVal,"",tables[index].name,temp_var1);
        if(sym==SEMICOLON){getsym();}
        else{error(MISSING_SEMICOLON);}
    }
    else if(sym==LBRACK){
        getsym(); record_arrnum = -1;
        record_typechange=0; expression();
        if(record_arrnum>tables[index].arr_size){error(OUT_OF_RANGE_ARRAY);}//��ʱû�п���[]�м���С��0�����
        //if(record_typechange==0){error(SHOULD_BE_INTEGER_USINT);}//�����м�ı��ʽ������int
        generate_tempvar(temp_var1,1);
        if(sym!=RBRACK){
            error(MISSING_RBRACK);
        }
        getsym();
        if(sym==ASSIGNSYM){
            getsym();
            record_typechange=0; expression();
            if(tables[index].type==CHARTYP&&record_typechange!=0){error(SHOULD_BE_CHARACTER);}//int��ֵ��char�����ǲ������
            generate_tempvar(temp_var2,1);
            record_quadruple(op_assignVal,temp_var1,tables[index].name,temp_var2);
            if(sym==SEMICOLON){getsym();}
            else{error(MISSING_SEMICOLON);}
        }else{error(SHOULD_BE_ASSIGNSYM);}
    }
    else{
        error(SHOULD_BE_ASSIGNSYM);
    }
}
//����return���
void statement_return(){
    getsym();   //printf("this is return statement.\n");
    char temp_var1[NAME_L]="#t";
    if(sym==SEMICOLON){
        if(retflag!=3){
            if(retflag!=-1){error(RETURN_ERROR);}
            retflag=0;//��ʾreturn���
            record_quadruple(sys_return,"","","");
        }//main������Ҫreturn
        else{record_quadruple(sys_exit,"","","");}
        getsym();
    }
    else if(sym==LPAREN){
        getsym();
        record_typechange = 0;
        expression();
        generate_tempvar(temp_var1,1);
        if(sym==RPAREN){
            if(retflag!=3){
                if(retflag==1&&record_typechange!=1){error(RETURN_ERROR);}//int ���뷵��int
                if(retflag==2&&record_typechange!=0){error(RETURN_ERROR);}//char ���뷵��char
                if(retflag==-1){error(RETURN_ERROR);}//void ������return;
                retflag = 0;//��ʾreturn���
                record_quadruple(sys_return,"","",temp_var1);
            }else{record_quadruple(sys_exit,"","","");}
            getsym();
            if(sym==SEMICOLON){getsym();}
            else{error(MISSING_SEMICOLON);}
        }else{error(MISSING_RPAREN);}
    }
    else{error(MISSING_SEMICOLON);}
}
//����scanf���
void statement_read(){
    if(sym!=SCANFSYM){
        error(SHOULD_BE_SCANF);
    }
    getsym();   //printf("this is scanf statement.\n");
    if(sym==LPAREN){
        getsym();
        if(sym==IDENTIFIER){
            do{
                if(sym==COMMA)  {getsym();}
                if(sym==IDENTIFIER){
                    int index = search_table(token,0,0);
                    if(index<=0){error(NOT_DEFINE);}
                    if(tables[index].obj!=VARIABLE&&tables[Ttable_index].obj!=PARAMETER){
                        //printf("%d %s %d\n",index,tables[index].name,tables[index].obj);
                        error(INVALID_READ);
                    }
                    record_quadruple(sys_read,"","",tables[index].name);
                    getsym();
                }else{error(SHOULD_BE_IDENTIFIER);}
            }while(sym==COMMA);
        }else{error(SHOULD_BE_IDENTIFIER);}
        if(sym==RPAREN){
            getsym();
            if(sym!=SEMICOLON){error(MISSING_SEMICOLON);}
            else{getsym();}
        }else{error(MISSING_RPAREN);}
    }else{error(MISSING_LPAREN);}
}
//����printf���
void statement_write(){
    if(sym!=PRINTFSYM){
        error(SHOULD_BE_PRINTF);
    }
    char temp_var1[NAME_L]="#t";
    getsym();   //printf("this is printf statement.\n");
    if(sym==LPAREN){
        getsym();
        if(sym==STRSYM){
            int index = search_strtables(token);
            if(index==-1){
                strcpy(str_tables[++Stable_index],token);
                index = Stable_index;
            }
            char val_str[NAME_L] = "STR";sprintf(val_str,"%s%d",val_str,index);
            record_quadruple(sys_write,"","",val_str);
            getsym();   //printf("this is a string.\n");
            if(sym==COMMA){
                getsym();
                record_typechange = 0;
                expression();
                generate_tempvar(temp_var1,1);
                if(record_typechange == 0) record_quadruple(sys_write,"0","",temp_var1);
                else record_quadruple(sys_write,"1","",temp_var1);
            }
            if(sym==RPAREN){
                getsym();
                if(sym!=SEMICOLON){error(MISSING_SEMICOLON);}
                else{getsym();}
            }else{error(MISSING_RPAREN);}
        }else if(sym==RPAREN){
            error(EMPTY_READ);
        }else{
            record_typechange = 0;
            expression();
            generate_tempvar(temp_var1,1);
            if(sym==RPAREN){
                getsym();
                if(record_typechange == 0) record_quadruple(sys_write,"0","",temp_var1);
                else record_quadruple(sys_write,"1","",temp_var1);
                if(sym!=SEMICOLON){error(MISSING_SEMICOLON);}
                else{getsym();}
            }else{error(MISSING_RPAREN);}
        }
    }else{error(MISSING_LPAREN);}
}
//������ʽ
void expression(){
    //printf("this is expression.\n");
    operator_quadruple record_op;
    char temp_var1[NAME_L]="#t",temp_var2[NAME_L]="#t";
    int sign = (sym==MINUS)?-1:1;
    if(sym==MINUS||sym==PLUS)   {getsym();}
    term();
    generate_tempvar(temp_var1,1);
    if(sign==-1){
        record_typechange=1;// -term ��ʾint
        generate_tempvar(temp_var2,0);
        record_quadruple(op_mult,temp_var1,"-1",temp_var2);
        upload_var = tempvar_num;
        strcpy(temp_var1,temp_var2);
    }
    while(sym==MINUS||sym==PLUS){
        record_arrnum = -2;
        char temp_var3[NAME_L]="#t", temp_var4[NAME_L]="#t";
        record_op = (sym==MINUS)?op_sub:op_add; record_typechange=1;
        getsym();
        term();
        generate_tempvar(temp_var3,1);
        generate_tempvar(temp_var4,0);
        record_quadruple(record_op,temp_var1,temp_var3,temp_var4);
        upload_var = tempvar_num;
        strcpy(temp_var1,temp_var4);
    }
}
//������
void term(){
    //printf("this is term.\n");
    operator_quadruple record_op;
    char temp_var1[NAME_L]="#t";
    factor();
    generate_tempvar(temp_var1,1);
    upload_var = tempvar_num;
    while(sym==TIMES||sym==DIV){
        record_arrnum = -2;
        char temp_var2[NAME_L]="#t", temp_var3[NAME_L]="#t";
        record_op = (sym==TIMES)?op_mult:op_div; record_typechange=1;
        getsym();
        factor();
        generate_tempvar(temp_var2,1);
        generate_tempvar(temp_var3,0);
        record_quadruple(record_op,temp_var1,temp_var2,temp_var3);
        upload_var = tempvar_num;
        strcpy(temp_var1,temp_var3);//�ü���Ľ������һ��
    }
}
//��������
void factor(){
    int index;  //printf("this is factor.\n");
    char temp_var1[NAME_L]="#t", temp_var2[NAME_L]="#t";
    if(sym==IDENTIFIER){
        record_arrnum = -2;
        index = search_table(token,0,0);
        if(index<=0){error(NOT_DEFINE);}
        if(tables[index].type==INTTYP)  {record_typechange = 1;}
        if(tables[index].obj==FUNCTION){
            if(tables[index].type==VOIDTYP){error(CANNOT_BE_VOID_FUNCTION);}
            else{
                int tmp_typechange = record_typechange;
                functioncall();
                record_typechange = tmp_typechange;
                generate_tempvar(temp_var1,0);//temp variable
                record_quadruple(op_getFuncVal,"",tables[index].name,temp_var1);
                //record_quadruple(op_assign,"",temp_var1,tables[index].name);
                upload_var = tempvar_num;
            }
        }
        else{
            getsym();
            if(sym==LBRACK){
                if(tables[index].obj!=ARRAY){error(SHOULD_BE_ARRAY);}
                getsym();

                int tmp_typechange = record_typechange;
                int tmp_arrnum = record_arrnum; record_arrnum=-1;
                expression();//�������Խ��
                if(record_arrnum>tables[index].arr_size){error(OUT_OF_RANGE_ARRAY);}//��ʱû�п���[]�м���С��0�����
                record_typechange = tmp_typechange;
                record_arrnum = tmp_arrnum;

                generate_tempvar(temp_var1,1);//array index
                generate_tempvar(temp_var2,0);//temp variable
                record_quadruple(op_getVal,temp_var1,tables[index].name,temp_var2);
                upload_var = tempvar_num;
                if(sym!=RBRACK){error(MISSING_RBRACK);}
                getsym();
            }
            else{
                if(tables[index].obj==ARRAY){error(CANNOT_BE_ARRAY);}
                generate_tempvar(temp_var1,0);//temp variable
                record_quadruple(op_getVal,"",tables[index].name,temp_var1);
                upload_var = tempvar_num;
                //next of identifier
            }
        }
    }
    else if(sym==MINUS||sym==PLUS){
        int sign = (sym==MINUS)?-1:1;
        getsym();
        if(sym==INTEGER||sym==USINT){
            record_arrnum = sign*record_num;
            record_typechange = 1;
            generate_tempvar(temp_var1,0);
            char val_int[NUM_L];sprintf(val_int,"%d",sign*record_num);
            record_quadruple(op_assignNum,"",temp_var1,val_int);
            upload_var = tempvar_num;
            getsym();
        }else{error(SHOULD_BE_INTEGER_USINT);}
    }
    else if(sym==INTEGER||sym==USINT){
        record_arrnum = record_num;
        record_typechange = 1;
        generate_tempvar(temp_var1,0);
        char val_int[NUM_L];sprintf(val_int,"%d",record_num);
        record_quadruple(op_assignNum,"",temp_var1,val_int);
        upload_var = tempvar_num;
        getsym();
    }
    else if(sym==CHARACTER){
        record_arrnum = -2;
        generate_tempvar(temp_var1,0);
        char val_char[] = "' '";val_char[1]=record_num;
        record_quadruple(op_assignNum,"",temp_var1,val_char);
        upload_var = tempvar_num;
        getsym();
    }
    else if(sym==LPAREN){
        getsym();
        expression();
        if(sym!=RPAREN){error(MISSING_RPAREN);}
        getsym();
    }
}

void functioncall(){
    int index = search_table(token,0,0);
    int para_ctr = 1;
    char temp_var1[NAME_L]="#t";
    getsym(); //printf("this is function call statement.\n");
    if(sym!=LPAREN){
        record_quadruple(op_jal,"","",tables[index].name);
    }
    else if(sym==LPAREN){
        do{
            getsym();
            if(sym==IDENTIFIER||sym==LPAREN||sym==PLUS||sym==MINUS||sym==USINT||sym==INTEGER||sym==CHARACTER){
                record_typechange=0; expression();
                if(tables[index+para_ctr].obj!=PARAMETER){error(SHOULD_BE_PARAMETER);skip_end[RPAREN]+=1;skip();skip_end[RPAREN]-=1;}
                if(tables[index+para_ctr].type==INTTYP&&record_typechange!=1){error(SHOULD_BE_INTEGER_USINT);}//�������ͱ����ϸ�ƥ��
                if(tables[index+para_ctr].type==CHARTYP&&record_typechange!=0){error(SHOULD_BE_CHARACTER);}
                para_ctr++;
                generate_tempvar(temp_var1,1);
                record_quadruple(op_para,"","",temp_var1);
            }else{
                error(INVALID_PARAMETER);
            }
        }while(sym==COMMA);
        if(sym==RPAREN){
            getsym();
            if(tables[index+para_ctr].obj==PARAMETER){error(SHOULD_BE_PARAMETER);}//����ʱ�ٴ��˲���
            record_quadruple(op_jal,"","",tables[index].name);
        }
        else{error(MISSING_RPAREN);}
    }
}


