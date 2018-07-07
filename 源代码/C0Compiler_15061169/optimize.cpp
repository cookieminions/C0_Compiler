//#include "compiler.h"
//#include "error.h"
//
//node nodes[MAX_Q];
//quadruple export_qualist[MAX_Q];
//
//int block_index= 0;
//int node_index = 0;
//int var_index = 0;
//int eQlist_index = 0;
//
//char var_name[MAX_T][NAME_L];
//int var_node[MAX_T];
//
//
//void clear_nodes(){
//    for(int i=0;i<MAX_Q;i++){
//        nodes[i].used = -1;
//        nodes[i].parents_index = 0;
//        nodes[i].left_child = -1;
//        nodes[i].right_child = -1;
//    }
//    node_index=0;
//}
//
//int search_node(char name[NAME_L]){
//    for(int i=0;i<MAX_T;i++){
//        if(stricmp(name,var_name[i])==0){
//            return var_node[i];
//        }
//    }
//    return -1;
//}
//
//void generate_DAG(int op_type, quadruple q){
//    if(op_type==5){//��Ŀ�����
//        nodes[++node_index].used = 1;nodes[node_index].parents_index=0;
//        strcpy(var_name[++var_index],q.result); var_node[var_index] = node_index;
//        nodes[node_index].op = q.op;
//
//        //Ŀǰ��Ŀ���������Ԫʽ��һ�������ӽڵ�� ���Բ����ж��Ƿ�Ϊ-1
//        int left = search_node(q.operand1); nodes[node_index].left_child = left;//�������ӽڵ�
//        nodes[left].parents[nodes[left].parents_index++]=node_index;//���ӽڵ����ø��ڵ�
//        int right = search_node(q.operand2); nodes[node_index].right_child = right;
//        nodes[right].parents[nodes[right].parents_index++]=node_index;
//    }else{//��ֵ�����
//        if(q.op==op_assignNum){
//            int index = search_node(q.result);
//            if(index==-1){
//                nodes[++node_index].used = 1; nodes[node_index].parents_index=0;
//                strcpy(var_name[++var_index],q.result); var_node[var_index] = node_index;
//                strcpy(var_name[++var_index],q.operand2); var_node[var_index] = node_index;
//            }else{
//                strcpy(var_name[++var_index],q.operand2); var_node[var_index] = index;
//            }
//        }
//        else if(q.op==op_assignVal){
//            int index = search_node(q.result);
//            if(index==-1){
//                nodes[++node_index].used = 1; nodes[node_index].parents_index=0;
//                strcpy(var_name[++var_index],q.result); var_node[var_index] = node_index;
//                strcpy(var_name[++var_index],q.operand2); var_node[var_index] = node_index;
//            }else{
//                strcpy(var_name[++var_index],q.operand2); var_node[var_index] = index;
//            }
//
//        }
//        else if(q.op==op_getVal){
//            int index = search_node(q.result);
//            if(index==-1){
//                nodes[++node_index].used = 1; nodes[node_index].parents_index=0;
//                strcpy(var_name[++var_index],q.result); var_node[var_index] = node_index;
//                strcpy(var_name[++var_index],q.operand2); var_node[var_index] = node_index;
//            }else{
//                strcpy(var_name[++var_index],q.operand2); var_node[var_index] = index;
//            }
//
//
//        }
//        else if(q.op==op_getFuncVal){
//            int index = search_node(q.operand2);
//            if(index==-1){
//                nodes[++node_index].used = 1; nodes[node_index].parents_index=0;
//                strcpy(var_name[++var_index],q.operand2); var_node[var_index] = node_index;
//                strcpy(var_name[++var_index],q.result); var_node[var_index] = node_index;
//            }else{
//                strcpy(var_name[++var_index],q.result); var_node[var_index] = index;
//            }
//
//        }
//
//    }
//
//
//}
//
//void export_qua(){
//
//}
//
//int judge_op(quadruple q_i){
//    if(q_i.op==op_j||q_i.op==op_beq||q_i.op==op_bne||q_i.op==op_blt||q_i.op==op_ble||q_i.op==op_bgt||q_i.op==op_bge||
//       q_i.op==dec_label||q_i.op==dec_func){//��ת ��һ��������
//        return 1;
//    }else if(q_i.op==dec_const||q_i.op==dec_var||q_i.op==dec_Arr||q_i.op==dec_para){//ֱ�Ӽӵ���Ԫʽ������
//        return 2;
//    }else if(q_i.op==op_para||q_i.op==sys_read||q_i.op==sys_write||q_i.op==sys_return||q_i.op==sys_exit||q_i.op==op_jal){//��Ҫ����ʱ����DAGͼ�ٰ��Լ��ӽ�ȥ
//        return 3;
//    }else if(q_i.op==op_assignNum||q_i.op==op_assignVal||q_i.op==op_getVal||q_i.op==op_getFuncVal){//��ֵ ��ʱ����������
//        return 4;
//    }else{//��Ŀ�����
//        return 5;
//    }
//}
//
//void divide_block(){
//    for(int i=1;i<=Qlist_index;i++){
//        int op_type = judge_op(quadruple_list[i]);
//        if(op_type==1){
//            export_qua();
//            clear_nodes();
//            export_qualist[++eQlist_index] = quadruple_list[i];
//        }else if(op_type==2){
//            export_qualist[++eQlist_index] = quadruple_list[i];
//        }else if(op_type==3){
//            export_qua();
//            //����ʱ�õ�����ʱ�������ܻ�ı�
//            //export_qualist++[eQlist_index] = quadruple_list[i];
//        }else{
//            generate_DAG(op_type,quadruple_list[i]);
//        }
//    }
//
//
//}
