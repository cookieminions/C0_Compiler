#include "compiler.h"
#include "error.h"

char * op_quadruple[]={
    "dec_const","dec_var","dec_Arr","dec_func","dec_para","dec_label",
    "op_add","op_sub","op_mult","op_div","op_assignNum","op_assignVal","op_getVal","op_getFuncVal","op_para",
    "op_j","op_jal","op_beq","op_bne","op_blt","op_ble","op_bgt","op_bge",
    "sys_read","sys_write","sys_return","sys_exit"
};


void print_table(){
    printf("\n\n\t\t---------------------------------tables---------------------------------\n\n");
    printf("\tid\t\tname\t\tobject\t\ttype\t\tlink\t\tval\t\tsize\t\tpara\n");
    for(int i=0;i<=Ttable_index;i++){
        printf("\t%d\t\t%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i,tables[i].name,tables[i].obj,tables[i].type,tables[i].link,tables[i].val,tables[i].arr_size,tables[i].para_num);
    }
}

void print_Qlist(){
    printf("\n\n\t\t------------------------quadruple_list------------------------\n\n");
    fprintf(fwp,"\n\n\t\t------------------------quadruple_list------------------------\n\n");
    printf("\tid\t\top\t\top_quad\t\targ1\t\targ2\t\tresult\n");
    fprintf(fwp,"\tid\t\top\t\top_quad\t\targ1\t\targ2\t\tresult\n");
    for(int i=1;i<=Qlist_index;i++){
        printf("\t%d\t\t%d\t\t%s\t\t%s\t\t%s\t\t%s\n",i,quadruple_list[i].op,op_quadruple[quadruple_list[i].op],quadruple_list[i].operand1,quadruple_list[i].operand2,quadruple_list[i].result);
        fprintf(fwp,"\t%d\t\t%d\t\t%s\t\t%s\t\t%s\t\t%s\n",i,quadruple_list[i].op,op_quadruple[quadruple_list[i].op],quadruple_list[i].operand1,quadruple_list[i].operand2,quadruple_list[i].result);
    }
}

void print_display(){
    printf("\n\n\t\t------------display------------\n\n");
    printf("\t\tfunc\t\t\tindex\n");
    for(int i=1;i<=display_index;i++){
        printf("\t\t%s\t\t\t%d\n",tables[display[i]].name,display[i]);
    }
}

void print_mips(){
    mipsfp = fopen("15061169_mips.asm","w");
    for(int i=1;i<=Mips_index;i++){
        fprintf(mipsfp,"%s\n",mips_code[i]);
    }

}
