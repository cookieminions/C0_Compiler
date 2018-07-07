#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "compiler.h"
#include "error.h"

char mips_code[3*MAX_Q][MIPS_L];
int Mips_index = 0;

char* regs_temp[] = {"$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$t8","$t9"};
//char* regs_para[] = {"$a0","$a1","$a2","$a3"};
//char* regs_para[] = {"$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7"};
int   regs_used[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

int para_index = 0;
int func_index = 0;
int fp_offset = 0;
int gp_offset = 0;

int para_num = 0;
int para_ctr = 0;

FILE* mipsfp;

char* get_reg(int tempvar){
    for(int i=0;i<REGS_N;i++){
        if(regs_used[i]==tempvar){
            regs_used[i]=-1;
            return regs_temp[i];
        }
    }
    for(int i=0;i<REGS_N;i++){
        if(regs_used[i]==-1){
            regs_used[i]=tempvar;
            return regs_temp[i];
        }
    }
    return "";
}

int search_ifGlobal(char name[NAME_L]){
    //局部作用域
    int index = display[func_index];
    //printf("func_index %d index %d\n",func_index,index);
    for(int i=index+1;i<=Ttable_index&&tables[i].obj!=FUNCTION;i++){
        if(stricmp(name,tables[i].name)==0){
            fp_offset = tables[i].offset;
            //printf("fp_offset %d i %d",tables[i].offset,i);
            return 0;
        }
    }
    //全局作用域
    for(int i=1;i<=Ttable_index&&tables[i].obj!=FUNCTION;i++){
        if(stricmp(name,tables[i].name)==0){
            gp_offset = tables[i].offset;
            //printf("gp_offset %d i %d",tables[i].offset,i);
            return 1;
        }
    }
    return -1;
}

int search_table2(char name[NAME_L]){
    //局部作用域
    int index = display[func_index];
    for(int i=index+1;i<=Ttable_index&&tables[i].obj!=FUNCTION;i++){
        if(stricmp(name,tables[i].name)==0){
            return i;
        }
    }
    //全局作用域
    for(int i=1;i<=Ttable_index&&tables[i].obj!=FUNCTION;i++){
        if(stricmp(name,tables[i].name)==0){
            return i;
        }
    }
    return -1;

}

//生成mips
void generate_code(quadruple q_i){
    switch(q_i.op){
        case dec_const:{
            push_stack(q_i,1);break;
        }
        case dec_var:{
            push_stack(q_i,1);break;
        }
        case dec_para:{
            push_stack(q_i,1);break;
        }
        case dec_Arr:{
            int len = atoi(q_i.result);
            push_stack(q_i,len);break;
        }
        case dec_label:{
            sprintf(mips_code[++Mips_index],"%s:",q_i.result);
            break;
        }
        case dec_func:{
            //函数计数加1
            ++func_index;
            //参数计数
            para_num = tables[display[func_index]].para_num; para_ctr = para_num;
            sprintf(mips_code[++Mips_index],"");
            sprintf(mips_code[++Mips_index],"%s:",q_i.result);
            //保存上一个$fp
            sprintf(mips_code[++Mips_index],"sw $fp, ($sp)");
            sprintf(mips_code[++Mips_index],"subi $sp, $sp, 4");
            //保存$ra
            sprintf(mips_code[++Mips_index],"sw $ra, ($sp)");
            sprintf(mips_code[++Mips_index],"subi $sp, $sp, 4");
            //加载新的$fp
            sprintf(mips_code[++Mips_index],"move $fp, $sp");
            //第一个变量(参数) 0($fp)
            //保存现场
            for(int i=0;i<10;i++){
                sprintf(mips_code[++Mips_index],"sw %s, %d($k0)",regs_temp[i],-(i*4));
            }
            sprintf(mips_code[++Mips_index],"subi $k0, $k0, 40");
            break;
        }
        case op_add:{
            char* reg1; char* reg2;
            reg1= get_reg(atoi(q_i.operand1+2)); reg2= get_reg(atoi(q_i.operand2+2));
            sprintf(mips_code[++Mips_index],"add %s, %s, %s",get_reg(atoi(q_i.result+2)),reg1,reg2);
            break;
        }
        case op_sub:{
            char* reg1; char* reg2;
            reg1= get_reg(atoi(q_i.operand1+2)); reg2= get_reg(atoi(q_i.operand2+2));
            sprintf(mips_code[++Mips_index],"sub %s, %s, %s",get_reg(atoi(q_i.result+2)),reg1,reg2);
            break;
        }
        case op_mult:{
            if(strcmp(q_i.operand2,"-1")==0){
                char* reg1 = get_reg(atoi(q_i.operand1+2));
                sprintf(mips_code[++Mips_index],"sub %s, $0, %s",get_reg(atoi(q_i.result+2)),reg1);
            }else{
                char* reg1; char* reg2;
                reg1= get_reg(atoi(q_i.operand1+2)); reg2= get_reg(atoi(q_i.operand2+2));
                sprintf(mips_code[++Mips_index],"mul %s, %s, %s",get_reg(atoi(q_i.result+2)),reg1,reg2);
            }
            break;
        }
        case op_div:{
            char* reg1; char* reg2;
            reg1= get_reg(atoi(q_i.operand1+2)); reg2= get_reg(atoi(q_i.operand2+2));
            sprintf(mips_code[++Mips_index],"div %s, %s",reg1,reg2);
            sprintf(mips_code[++Mips_index],"mflo %s",get_reg(atoi(q_i.result+2)));
            break;
        }
        case op_j:{
            sprintf(mips_code[++Mips_index],"j %s",q_i.result);
            sprintf(mips_code[++Mips_index],"nop");
            break;
        }
        case op_jal:{
            sprintf(mips_code[++Mips_index],"jal %s",q_i.result);
            sprintf(mips_code[++Mips_index],"nop");
            break;
        }
        case op_beq:{
            if(strcmp(q_i.operand2,"0")==0){
                sprintf(mips_code[++Mips_index],"beq %s, $0, %s",get_reg(atoi(q_i.operand1+2)),q_i.result);
                sprintf(mips_code[++Mips_index],"nop");
            }else{
                sprintf(mips_code[++Mips_index],"beq %s, %s, %s",get_reg(atoi(q_i.operand1+2)),get_reg(atoi(q_i.operand2+2)),q_i.result);
                sprintf(mips_code[++Mips_index],"nop");
            }
            break;
        }
        case op_bne:{
            if(strcmp(q_i.operand2,"0")==0){
                sprintf(mips_code[++Mips_index],"bne %s, $0, %s",get_reg(atoi(q_i.operand1+2)),q_i.result);
                sprintf(mips_code[++Mips_index],"nop");
            }else if(q_i.operand2[0]=='#'){
                sprintf(mips_code[++Mips_index],"bne %s, %s, %s",get_reg(atoi(q_i.operand1+2)),get_reg(atoi(q_i.operand2+2)),q_i.result);
                sprintf(mips_code[++Mips_index],"nop");
            }else{
                sprintf(mips_code[++Mips_index],"bne %s, %s, %s",get_reg(atoi(q_i.operand1+2)),q_i.operand2,q_i.result);
                sprintf(mips_code[++Mips_index],"nop");
            }
            break;
        }
        case op_blt:{
            sprintf(mips_code[++Mips_index],"blt %s, %s, %s",get_reg(atoi(q_i.operand1+2)),get_reg(atoi(q_i.operand2+2)),q_i.result);
            sprintf(mips_code[++Mips_index],"nop");
            break;
        }
        case op_ble:{
            sprintf(mips_code[++Mips_index],"ble %s, %s, %s",get_reg(atoi(q_i.operand1+2)),get_reg(atoi(q_i.operand2+2)),q_i.result);
            sprintf(mips_code[++Mips_index],"nop");
            break;
        }
        case op_bgt:{
            sprintf(mips_code[++Mips_index],"bgt %s, %s, %s",get_reg(atoi(q_i.operand1+2)),get_reg(atoi(q_i.operand2+2)),q_i.result);
            sprintf(mips_code[++Mips_index],"nop");
            break;
        }
        case op_bge:{
            sprintf(mips_code[++Mips_index],"bge %s, %s, %s",get_reg(atoi(q_i.operand1+2)),get_reg(atoi(q_i.operand2+2)),q_i.result);
            sprintf(mips_code[++Mips_index],"nop");
            break;
        }
        case op_assignNum:{
            sprintf(mips_code[++Mips_index],"li %s, %s",get_reg(atoi(q_i.operand2+2)),q_i.result);
            break;
        }
        case op_assignVal:{
            int index = (strcmp(q_i.operand1,"")==0)?0:atoi(q_i.operand1);
            if(search_ifGlobal(q_i.operand2)==0){
                if(q_i.operand1[0]=='#'){//其实我这儿只可能有临时变量 不可能有数字
                    index = 0;char* reg1 = get_reg(atoi(q_i.operand1+2));
                    sprintf(mips_code[++Mips_index],"sll %s, %s, 2",reg1,reg1);
                    sprintf(mips_code[++Mips_index],"sub %s, $fp, %s",reg1,reg1);
                    sprintf(mips_code[++Mips_index],"sw %s, %d(%s)",get_reg(atoi(q_i.result+2)),-(fp_offset+index*4),reg1);
                }else{//不是数字 是空啦
                    sprintf(mips_code[++Mips_index],"sw %s, %d($fp)",get_reg(atoi(q_i.result+2)),-(fp_offset+index*4));
                }

            }else if(search_ifGlobal(q_i.operand2)==1){
                if(q_i.operand1[0]=='#'){
                    index = 0;char* reg1 = get_reg(atoi(q_i.operand1+2));
                    sprintf(mips_code[++Mips_index],"sll %s, %s, 2",reg1,reg1);
                    sprintf(mips_code[++Mips_index],"sub %s, $gp, %s",reg1,reg1);
                    sprintf(mips_code[++Mips_index],"sw %s, %d(%s)",get_reg(atoi(q_i.result+2)),-(gp_offset+index*4),reg1);
                }else{
                    sprintf(mips_code[++Mips_index],"sw %s, %d($gp)",get_reg(atoi(q_i.result+2)),-(gp_offset+index*4));
                }
            }else{printf("%s err1",q_i.result);error(0);}
            break;
        }
        case op_getVal:{
            int index = (strcmp(q_i.operand1,"")==0)?0:atoi(q_i.operand1);
            if(search_ifGlobal(q_i.operand2)==0){
                if(q_i.operand1[0]=='#'){
                    index = 0;char* reg1 = get_reg(atoi(q_i.operand1+2));
                    sprintf(mips_code[++Mips_index],"sll %s, %s, 2",reg1,reg1);
                    sprintf(mips_code[++Mips_index],"sub %s, $fp, %s",reg1,reg1);
                    sprintf(mips_code[++Mips_index],"lw %s, %d(%s)",get_reg(atoi(q_i.result+2)),-(fp_offset+index*4),reg1);
                }else{
                    sprintf(mips_code[++Mips_index],"lw %s, %d($fp)",get_reg(atoi(q_i.result+2)),-(fp_offset+index*4));
                }
            }else if(search_ifGlobal(q_i.operand2)==1){
                if(q_i.operand1[0]=='#'){
                    index = 0;char* reg1 = get_reg(atoi(q_i.operand1+2));
                    sprintf(mips_code[++Mips_index],"sll %s, %s, 2",reg1,reg1);
                    sprintf(mips_code[++Mips_index],"sub %s, $gp, %s",reg1,reg1);
                    sprintf(mips_code[++Mips_index],"lw %s, %d(%s)",get_reg(atoi(q_i.result+2)),-(gp_offset+index*4),reg1);
                }else{
                    sprintf(mips_code[++Mips_index],"lw %s, %d($gp)",get_reg(atoi(q_i.result+2)),-(gp_offset+index*4));
                }
            }else{printf("%s err2",q_i.result);error(0);}
            break;
        }
        case op_getFuncVal:{
            sprintf(mips_code[++Mips_index],"move %s, $v1",get_reg(atoi(q_i.result+2)));
            break;
        }
        case op_para:{
            sprintf(mips_code[++Mips_index],"sw %s, ($k0)",get_reg(atoi(q_i.result+2)));
            sprintf(mips_code[++Mips_index],"subi $k0, $k0, 4");
            break;
        }
        case sys_read:{
            int index = search_table2(q_i.result);
            if(tables[index].type==CHARTYP){
                sprintf(mips_code[++Mips_index],"li $v0, 12");
            }else if(tables[index].type==INTTYP){
                sprintf(mips_code[++Mips_index],"li $v0, 5");
            }
            sprintf(mips_code[++Mips_index],"syscall");
            if(search_ifGlobal(q_i.result)==0){
                sprintf(mips_code[++Mips_index],"sw $v0, %d($fp)",-fp_offset);
            }else if(search_ifGlobal(q_i.result)==1){
                sprintf(mips_code[++Mips_index],"sw $v0, %d($gp)",-gp_offset);
            }
            break;
        }
        case sys_write:{
            if(q_i.result[0]=='#'){
                if(q_i.operand1[0]=='0'){//char
                    sprintf(mips_code[++Mips_index],"move $a0, %s",get_reg(atoi(q_i.result+2)));
                    sprintf(mips_code[++Mips_index],"li $v0, 11");
                    sprintf(mips_code[++Mips_index],"syscall");
                }else if(q_i.operand1[0]=='1'){//int
                    sprintf(mips_code[++Mips_index],"move $a0, %s",get_reg(atoi(q_i.result+2)));
                    sprintf(mips_code[++Mips_index],"li $v0, 1");
                    sprintf(mips_code[++Mips_index],"syscall");
                }
            }else{
                sprintf(mips_code[++Mips_index],"la $a0, %s",q_i.result);
                sprintf(mips_code[++Mips_index],"li $v0, 4");
                sprintf(mips_code[++Mips_index],"syscall");
            }
            break;
        }
        case sys_return:{
            if(strcmp(q_i.result,"")!=0){
                sprintf(mips_code[++Mips_index],"move $v1, %s",get_reg(atoi(q_i.result+2)));
            }
            for(int i=9;i>=0;i--){
                sprintf(mips_code[++Mips_index],"lw %s, %d($k0)",regs_temp[i],40-i*4);
            }sprintf(mips_code[++Mips_index],"addi $k0, $k0, 40");
            sprintf(mips_code[++Mips_index],"addi $k0, $k0, %d",para_num*4);

            sprintf(mips_code[++Mips_index],"move $sp, $fp");
            sprintf(mips_code[++Mips_index],"lw $ra, 4($sp)");
            sprintf(mips_code[++Mips_index],"lw $fp, 8($sp)");
            sprintf(mips_code[++Mips_index],"addi $sp, $sp, 8");
            sprintf(mips_code[++Mips_index],"jr $ra");
            sprintf(mips_code[++Mips_index],"nop");
            break;
        }
        case sys_exit:{
            sprintf(mips_code[++Mips_index],"li $v0, 10");
            sprintf(mips_code[++Mips_index],"syscall");
            break;
        }
    }
}

void push_stack(quadruple q_i,int len){
    if(q_i.op==dec_const){
        sprintf(mips_code[++Mips_index],"li $t0, %s",q_i.result);
        sprintf(mips_code[++Mips_index],"sw $t0, ($sp)");
    }else if(q_i.op==dec_para){
        sprintf(mips_code[++Mips_index],"lw $t0, %d($k0)",para_ctr*4+40);
        sprintf(mips_code[++Mips_index],"sw $t0, ($sp)");
        para_ctr--;
    }
    sprintf(mips_code[++Mips_index],"subi $sp, $sp, %d",len*4);
}

void generate_mips(){
    sprintf(mips_code[++Mips_index],".data");
    for(int i=1;i<=Stable_index;i++){
        sprintf(mips_code[++Mips_index],"\tSTR%d: .asciiz %s",i,str_tables[i]);
    }

    sprintf(mips_code[++Mips_index],".text");

    sprintf(mips_code[++Mips_index],"li $k0, 0x10020000");
    sprintf(mips_code[++Mips_index],"move $gp, $sp");
    sprintf(mips_code[++Mips_index],"move $fp, $sp");
    for(int i=1;i<=Qlist_index;i++){
        generate_code(quadruple_list[i]);
    }

}

