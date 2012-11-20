#include <stdio.h>

#include "include/exp_tree.h"
#include "include/query_code.h"
#include <iostream>

FILE *qcode_fp;

static int hashJoin_consumption = 0;
static int open_braces = 0;

void indent() {
	for(int i=0; i<open_braces; i++)
		fprintf(qcode_fp, "\t");
}

void print_operation::produce() {
	switch(oper->l_op->oper->oper_type)
	{
		case HASH_JOIN:
			input = new hashJoin_operation();
			input->oper = oper->l_op->oper;
			input->consumer = this;
			input->produce();
			break;
		default:
			printf("ERR: %s: %s: %d\n",__FILE__,__func__,__LINE__);
	}
}

void print_operation::consume() {
	vector<field_t>::iterator field_iter;
	for(field_iter=oper->field_list.begin(); field_iter<oper->field_list.end(); field_iter++)
	{
		indent();
		fprintf(qcode_fp, "printf(\"%%s\\t\", %s.str);\n", (char *)(field_iter->c_str()));
	}
	indent();
	fprintf(qcode_fp, "printf(\"\\n\");\n");
}

void hashJoin_operation::produce() {
	switch(oper->l_op->oper->oper_type)
	{
		case TABLE_SCAN:
			l_input = new tableScan_operation();
			l_input->oper = oper->l_op->oper;
			l_input->consumer = this;
			l_input->produce();
			break;
		default:
			printf("ERR: %s: %s: %d\n",__FILE__,__func__,__LINE__);		
	}

}

void hashJoin_operation::consume() {
	if(hashJoin_consumption % 2 ==0) {
		hashJoin_consumption++;
		switch(oper->r_op->oper->oper_type)
		{
			case TABLE_SCAN:
				r_input = new tableScan_operation();
				r_input->oper = oper->r_op->oper;
				r_input->consumer = this;
				r_input->produce();
				break;
			default:
				printf("ERR: %s: %s: %d\n",__FILE__,__func__,__LINE__);
		}
	}
	else {
		hashJoin_consumption++;	
		if(!oper->predicate_list.empty())
		{
			vector<predicate_t>::iterator pred_iter;
			for(pred_iter=oper->predicate_list.begin();pred_iter < oper->predicate_list.end();pred_iter++)
			{	
				if(pred_iter != oper->predicate_list.begin())
				{
					fprintf(qcode_fp, " && ");
				}
				else
				{
					indent();
					fprintf(qcode_fp, "if(");
				}
				fprintf(qcode_fp, "%s", pred_iter->pred_l_op);
				switch(pred_iter->pred_oper_type)
				{
					case EQUALS:
						fprintf(qcode_fp, " == ");
						break;
					default:
						printf("ERR: %s: %s: %d\n",__FILE__,__func__,__LINE__);
				}						
				fprintf(qcode_fp, "%s", pred_iter->pred_r_op);
			}
			fprintf(qcode_fp, ")\n");
			indent();
			fprintf(qcode_fp, "{\n");
			open_braces++;
		}
		consumer->consume();
		open_braces--;
		indent();
		fprintf(qcode_fp, "}\n");
	}
}

void tableScan_operation::produce() {
	switch(oper->l_op->operand_type) {
		case TABLE:
			indent();
			fprintf(qcode_fp, "for(vector<%s>::iterator hJ_%d_iter=%s_vect.begin(); hJ_%d_iter<%s_vect.end(); hJ_%d_iter++)\n", oper->l_op->table_name, hashJoin_consumption, oper->l_op->table_name, hashJoin_consumption, oper->l_op->table_name, hashJoin_consumption);
			indent();
			fprintf(qcode_fp, "{\n");
			open_braces++;
			for(vector<field_t>::iterator field_iter=oper->field_list.begin(); field_iter < oper->field_list.end(); field_iter++)
			{
				indent();
				fprintf(qcode_fp, "mystring %s;\n", (char*)(field_iter->c_str()));
				indent();
				fprintf(qcode_fp, "%s = hJ_%d_iter->%s;\n", (char*)(field_iter->c_str()), hashJoin_consumption, (char*)(field_iter->c_str()));
			}
			consumer->consume();
			open_braces--;
			indent();
			fprintf(qcode_fp, "}\n");
			break;
		default:
			printf("ERR: %s: %s: %d\n",__FILE__,__func__,__LINE__);		
	}
}

void generate_query_code() {

	operation_t *root = &exp_root;

	qcode_fp = fopen("gen_query_code.cpp", "w");

	fprintf(qcode_fp, "#include <stdio.h>\n");
	fprintf(qcode_fp, "#include <string.h>\n");
	fprintf(qcode_fp, "#include <stdint.h>\n");
	fprintf(qcode_fp, "#include <stdlib.h>\n\n");
	fprintf(qcode_fp, "#include \"include/schema.h\"\n");
	fprintf(qcode_fp, "#include \"include/storage.h\"\n\n");
	fprintf(qcode_fp, "");
	fprintf(qcode_fp, "");
	fprintf(qcode_fp, "class mystring {\n");
	fprintf(qcode_fp, "public:\n");
	fprintf(qcode_fp, "\tchar* str;\n\n");
	fprintf(qcode_fp, "\tmystring operator=(char *_str);\n");
	fprintf(qcode_fp, "\tmystring operator=(uint64_t val);\n");
	fprintf(qcode_fp, "\tint operator==(uint64_t val);\n");
	fprintf(qcode_fp, "\tint operator==(const char* _str);\n");
	fprintf(qcode_fp, "\tint operator==(mystring _mystr);\n");
	fprintf(qcode_fp, "};\n\n");
	fprintf(qcode_fp, "mystring mystring::operator=(char *_str) {\n");
	fprintf(qcode_fp, "\tstr = (char*)malloc(sizeof(char)*strlen(_str));\n");
	fprintf(qcode_fp, "\tstrcpy(str, _str);\n");
	fprintf(qcode_fp, "\treturn *this;\n");
	fprintf(qcode_fp, "}\n\n");
	fprintf(qcode_fp, "mystring mystring::operator=(uint64_t val) {\n");
	fprintf(qcode_fp, "\tstr = (char*)malloc(sizeof(char)*20);\n");
	fprintf(qcode_fp, "\tsprintf(str, \"%%llu\", val);\n");
	fprintf(qcode_fp, "\treturn *this;\n");
	fprintf(qcode_fp, "}\n\n");
	fprintf(qcode_fp, "int mystring::operator==(uint64_t val) {\n");
	fprintf(qcode_fp, "\tchar temp_str[20];\n");
	fprintf(qcode_fp, "\tsprintf(temp_str, \"%%llu\", val);\n");
	fprintf(qcode_fp, "\treturn !strcmp(str, temp_str);\n");
	fprintf(qcode_fp, "}\n\n");	
	fprintf(qcode_fp, "int mystring::operator==(const char* _str) {\n");
	fprintf(qcode_fp, "\treturn !strcmp(str, _str);\n");
	fprintf(qcode_fp, "}\n\n");
	fprintf(qcode_fp, "int mystring::operator==(mystring _mystr) {\n");
	fprintf(qcode_fp, "\treturn !strcmp(str, _mystr.str);\n");
	fprintf(qcode_fp, "}\n\n");		
	fprintf(qcode_fp, "");
	fprintf(qcode_fp, "");

	indent();
	fprintf(qcode_fp, "void query2() {\n");
	open_braces++;

	print_operation *print = new print_operation();
	print->oper = root;
	print->produce();

	open_braces--;
	indent();
	fprintf(qcode_fp, "}\n");
	

	fclose(qcode_fp);
}