/*
 * Implementation of functions declared in parse_tree.h
 */

#include <stdio.h>
#include "include/parse_tree.h"

using namespace std;

static int num_hashOp;					//Num of Hash Operators used. This is

extern FILE *qcode_fp;

int open_braces = 0;

void indent() {
	for(int i=0; i<open_braces; i++)
		fprintf(qcode_fp, "\t");
}

//Just calls produce to the input
void print_Operator::produce() {
	l_input->produce();
}

//prints the table
void print_Operator::consume() {
	vector<field_t>::iterator field_iter;
	for(vector<table_field_vect_t>::iterator table_iter=table_vect.begin(); table_iter != table_vect.end(); table_iter++)
	{
		for(vector<field_t>::iterator field_iter=table_iter->field_vect.begin(); field_iter != table_iter->field_vect.end(); field_iter++)
		{
			indent();
			fprintf(qcode_fp, "printf(\"%%s\\t\", %s.str);\n", (char *)(field_iter->c_str()));
		}
	}
	indent();
	fprintf(qcode_fp, "printf(\"\\n\");\n");
}

//calls produce on the input for now. Can do something important if column store is used.
void select_Operator::produce() {
	l_input->produce();
}

//calls consume for the consumer.
void select_Operator::consume() {
	for(vector<table_field_vect_t>::iterator table_iter=table_vect.begin(); table_iter != table_vect.end(); table_iter++)
	{
		for(vector<field_t>::iterator field_iter=table_iter->field_vect.begin(); field_iter != table_iter->field_vect.end(); field_iter++)
		{
			indent();
			fprintf(qcode_fp, "mystring %s;\n", field_iter->c_str());
			indent();
			fprintf(qcode_fp, "%s = %s_iter->%s;\n", field_iter->c_str(), table_iter->table_name.c_str(), field_iter->c_str());
		}
	}
	consumer->consume();
}

//this implementation is using Hash Join
//This function calls produce for the left input. The left input only produces the for statement.
//The input for joins only produce the for loops, the join operator is responsible for hashing.
//when l_input->produce() returns, first table hashing code is generated already by join_Operator->consume().
void join_Operator::produce() {
	join_Operator* _join1 = dynamic_cast<join_Operator*>(this);

	_join1->joinOp_num = num_hashOp++;
	indent();
	fprintf(qcode_fp,"unordered_map<%s, uint64_t> hash_map_%d;\n",_join1->hash_key_type.c_str(), _join1->joinOp_num); 
	l_input->produce();
	r_input->produce();
}

//For the left input, this function writes the code, that will generate a hash tree
//   by iterating on the whole table.
//   Returns to produce of the consumer, which then closes the paranthesis for "for" block.   
//
void join_Operator::consume() {
	join_Operator* _join1 = dynamic_cast<join_Operator*>(this);

	if(!_join1->l_input_consumed) {
		//perform hashing on hash_key
		indent();
		fprintf(qcode_fp, "//hash_map_%d should be declared just above\n", _join1->joinOp_num);
		indent();
		fprintf(qcode_fp, "//generate hash table here\n");
		indent();
		fprintf(qcode_fp, "hash_map_%d.insert(make_pair(%s_iter->%s, %s_iter->tuple_id));\n", _join1->joinOp_num, l_input->table_name.c_str(), _join1->hash_key_field.c_str(), l_input->table_name.c_str());
		_join1->l_input_consumed = true;
	}
	else {
		//check for predicates using Hash Table
		indent();
		fprintf(qcode_fp, "//Match with Hash Table here\n");
		if(!primary_pred_vect.empty())
		{
			vector<predicate_t>::iterator pred_iter;
			for(pred_iter=primary_pred_vect.begin();pred_iter < primary_pred_vect.end();pred_iter++)
			{	
				if(pred_iter == primary_pred_vect.begin())
				{
					indent();
					fprintf(qcode_fp, "if(");
				} 
				else {
					fprintf(qcode_fp, " && ");
				}

				fprintf(qcode_fp, "%s_iter->%s", r_input->table_name.c_str(), pred_iter->pred_l_operand.c_str());
				fprintf(qcode_fp, "%s", pred_iter->pred_operator.c_str())						;
				fprintf(qcode_fp, "%s", pred_iter->pred_r_operand.c_str());
			}
			fprintf(qcode_fp, ")\n");
			indent();
			fprintf(qcode_fp, "{\n");
			open_braces++;
			indent();
			fprintf(qcode_fp, "%s* %s_iter=&%s_vect.at(hash_map_%d.at(%s_iter->%s));\n", l_input->table_name.c_str(), l_input->table_name.c_str(), l_input->table_name.c_str(), _join1->joinOp_num, r_input->table_name.c_str(), hashed_pred.pred_l_operand.c_str());
			/*
			indent();
			fprintf(qcode_fp, "if(%s_iter == %s_vect.end()) {\n", l_input->table_name.c_str(), l_input->table_name.c_str());
			open_braces++;
			indent();
			fprintf(qcode_fp, "continue;\n");
			open_braces--;
			indent();
			fprintf(qcode_fp, "}\n");
			*/
			consumer->consume();
			open_braces--;
			indent();
			fprintf(qcode_fp, "}\n");
		}
		else {
			indent();
			fprintf(qcode_fp, "vector<%s>::iterator %s_iter=%s_vect.at(hash_map_%d.at(%s));\n", l_input->table_name.c_str(), l_input->table_name.c_str(), l_input->table_name.c_str(), _join1->joinOp_num, hashed_pred.pred_l_operand.c_str());
			/*
			indent();
			fprintf(qcode_fp, "if(%s_iter == %s_vect.end()) {\n", l_input->table_name.c_str(), l_input->table_name.c_str());
			open_braces++;
			indent();
			fprintf(qcode_fp, "continue;\n");
			open_braces--;
			indent();
			fprintf(qcode_fp, "}\n");
			*/
			consumer->consume();
		}
	}
}

//
void tableScan_Operator::produce() {
	indent();
	//For loop to trace the entire table to be produced here.
	fprintf(qcode_fp, "for(vector<%s>::iterator %s_iter=%s_vect.begin(); %s_iter!=%s_vect.end(); %s_iter++)\n",table_name.c_str(),table_name.c_str(),table_name.c_str(),table_name.c_str(),table_name.c_str(),table_name.c_str());
	indent();
	fprintf(qcode_fp, "{\n");
	open_braces++;
	consumer->consume();
	open_braces--;
	indent();
	fprintf(qcode_fp, "}\n");
}

