/*
 * Hardcoded Parse Tree
 *
 */

#include <iostream>
#include <list>
#include <string>

#include "include/parse_tree.h"

using namespace std;

Operator *expr_root;

void generate_parse_tree() {

	//PRINT Operation
	print_Operator *print1;
	print1 = new print_Operator;
	expr_root = print1;
	table_field_vect_t *table=new table_field_vect_t;
	//tables and fields
	table->table_name = "district";
	table->field_vect.push_back((field_t)"d_name");
	print1->table_vect.push_back(*table);
	delete table;
	table = new table_field_vect_t;
	table->table_name = "customer";
	table->field_vect.push_back((field_t)"c_first");
	table->field_vect.push_back((field_t)"c_last");
	table->field_vect.push_back((field_t)"c_id");
	print1->table_vect.push_back(*table);
	delete table;
	print1->l_input = new select_Operator;

	//SELECT Operator
	Operator *select1;
	select1 = print1->l_input;
	select1->consumer = print1;
	//tables and fields
	table = new table_field_vect_t;
	table->table_name = "district";
	table->field_vect.push_back((field_t)"d_name");
	select1->table_vect.push_back(*table);
	delete table;
	table = new table_field_vect_t;
	table->table_name = "customer";
	table->field_vect.push_back((field_t)"c_first");
	table->field_vect.push_back((field_t)"c_last");
	table->field_vect.push_back((field_t)"c_id");
	select1->table_vect.push_back(*table);
	delete table;
	select1->l_input = new join_Operator;

	//JOIN Operator
	Operator *join1;
	join1 = select1->l_input;
	join1->consumer = select1;
	join1->l_input = new tableScan_Operator;
	join1->r_input = new tableScan_Operator;
	predicate_t pred;
	pred.pred_l_operand = "c_w_id";
	pred.pred_operator = "==";
	pred.pred_r_operand = "1";
	join1->primary_pred_vect.push_back(pred);
	join1->hashed_pred.pred_l_operand = "c_d_id";
	join1->hashed_pred.pred_operator = "==";
	join1->hashed_pred.pred_r_operand = "d_id";
	join_Operator* _join1 = dynamic_cast<join_Operator*>(join1);
	_join1->hash_key_type="uint64_t";
	_join1->hash_key_field="d_id";

	//left TABLESCAN Operator
	Operator *tableScan1;
	tableScan1 = join1->l_input;
	tableScan1->consumer = join1;
	tableScan1->table_name = "district";
	//OVERKILL : table_name is enough for tableScan_Operator
	/*
	table = new table_field_vect_t;
	table->table_name = "warehouse";
	table->field_vect.push_back((field_t)"w_id");
	table->field_vect.push_back((field_t)"w_name");
	tableScan1->table_vect.push_back(*table);
	delete table;
	*/
	//tableScan1->l_input = new table_Operator;

	//right TABLESCAN Operator
	Operator *tableScan2;
	tableScan2 = join1->r_input;
	tableScan2->consumer = join1;
	tableScan2->table_name = "customer";
	//OVERKILL : table_name is enough for tableScan_Operator
	/*
	table = new table_field_vect_t;
	table->table_name = "district";
	table->field_vect.push_back((field_t)"d_w_id");
	table->field_vect.push_back((field_t)"d_name");
	table->field_vect.push_back((field_t)"d_tax");
	tableScan2->table_vect.push_back(*table);
	delete table;
	*/
	//tableScan2->l_input = new table_Operator;
}