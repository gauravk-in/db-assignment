#include <stdio.h>
#include <iostream>
#include <string.h>

#include "include/exp_tree.h"

operation_t exp_root;

/*
 * This function hard codes the creation of the tree for 
 * the given query
 * 
 * select w_name, d_name, d_tax
 * from warehouse, district
 * where w_id = d_w_id
 * and w_id = 1
 */

void build_exp_tree() {

	//PRINT Operator
	exp_root.oper_type = PRINT;
	exp_root.l_op = new operand_t();
	exp_root.l_op->operand_type = OPERATION;
	exp_root.field_list.push_back((field_t)"w_name");
	exp_root.field_list.push_back((field_t)"d_name");
	exp_root.field_list.push_back((field_t)"d_tax");
	exp_root.l_op->oper = new operation_t();

	printf("%s:%d\n", __func__,__LINE__);

	//HASH Join Operator
	operation_t *hash1 = exp_root.l_op->oper;
	hash1->oper_type = HASH_JOIN;
	predicate_t pred;
	pred.pred_oper_type = EQUALS;
	strcpy(pred.pred_l_op, "w_id");
	strcpy(pred.pred_r_op, "d_w_id");
	hash1->predicate_list.push_back(pred);
	//delete l_op;
	predicate_t pred2;
	pred2.pred_oper_type = EQUALS;
	strcpy(pred2.pred_l_op, "w_id");
	strcpy(pred2.pred_r_op, "1");
	hash1->predicate_list.push_back(pred2);
	//delete r_op;

	//TABLE_SCAN Operator
	exp_root.l_op->oper->l_op = new operand_t();
	exp_root.l_op->oper->l_op->operand_type = OPERATION;
	exp_root.l_op->oper->l_op->oper = new operation_t();

	operation_t* tscan1 = exp_root.l_op->oper->l_op->oper;
	tscan1->oper_type = TABLE_SCAN;
	tscan1->field_list.push_back((field_t)"w_name");
	tscan1->field_list.push_back((field_t)"w_id");
	
	tscan1->l_op = new operand_t();
	tscan1->l_op->operand_type = TABLE;
	strcpy(tscan1->l_op->table_name,"warehouse");

	exp_root.l_op->oper->r_op = new operand_t();
	exp_root.l_op->oper->r_op->operand_type = OPERATION;
	exp_root.l_op->oper->r_op->oper = new operation_t();
	
	operation_t* tscan2 = exp_root.l_op->oper->r_op->oper;
	tscan2->oper_type = TABLE_SCAN;
	tscan2->field_list.push_back((field_t)"d_name");
	tscan2->field_list.push_back((field_t)"d_w_id");
	tscan2->field_list.push_back((field_t)"d_tax");
	
	tscan2->l_op = new operand_t();
	tscan2->l_op->operand_type = TABLE;
	strcpy(tscan2->l_op->table_name,"district");
}