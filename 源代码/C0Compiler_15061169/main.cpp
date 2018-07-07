#include "compiler.h"
#include "error.h"

int main()
{
    //fp = fopen("15061169_test.txt","r");
    fwp = fopen("15061169_result.txt","w");

    char path[100];
    printf("please input file's path(max length:100):");
    scanf("%s",path);
    if((fp=fopen(path,"r"))==NULL){
        printf("open file %s failed\n",path);
        return 0;
    }

    ch =' ';
    eofflag = 0;
    mainflag= 0;
    record_field = -1;
    record_offset = 0;
    legal_func_dec = true;
    finish_var_dec = false;


//    while(ch!=-1){
//        getsym();
//        if(eofflag!=1)
//            output();
//    }

    getsym();
    if(sym==CONSTSYM)
        dec_constant();
    if(sym==INTSYM||sym==CHARSYM)
        dec_variableTofunction();
    if(sym==VOIDSYM){
        getsym();
        if(sym==MAINSYM){
            getsym();
            mainfunc();
        }
        else if(sym==IDENTIFIER){
            record_quadruple(op_jal,"","","main");
            if(search_table(token,0,0)>0){error(DUPLICATE_DEF);}
            else{
                enter_table(token,FUNCTION,VOIDTYP);
                record_field = (record_field==-1)?Ttable_index-1:record_field;
            }
            getsym();
            retflag=-1;dec_function();
        }
    }
    if(mainflag!=1){
        error(MISSING_MAIN);
    }
    print_table();
    print_Qlist();
    print_display();
    generate_mips();
    print_mips();

    fclose(fp);
    fclose(fwp);
    return 0;
}
