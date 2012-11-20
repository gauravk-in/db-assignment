#ifndef _EXP_TREE_H_
#define _EXP_TREE_H_

#include <vector>
#include <string>

using namespace std;

class operand_t;
class operation_t;
class predicate_t;

extern void build_exp_tree();

enum oper_enum {
	OPER_NONE=0,
	PRINT,
	SELECT,
	TABLE_SCAN,
	HASH_JOIN
};

enum operand_enum {
	OPERAND_NONE=0,
	OPERATION,
	TABLE
};

enum pred_oper_enum {
	PRED_OPER_NONE = 0,
	EQUALS
};

//typedef string pred_operand_t;

class predicate_t {
public:
	pred_oper_enum pred_oper_type;
	//pred_operand_t pred_l_op;
	//pred_operand_t pred_r_op;
	char pred_l_op[20];
	char pred_r_op[20];
};


typedef string field_t;

class operation_t {
public:
	oper_enum oper_type;
	operand_t *l_op;
	operand_t *r_op;

	vector<field_t> field_list;				//for PRINT, TABLE_SCAN and SELECT
	vector<predicate_t> predicate_list;		//for HASH_JOIN

	operation_t() {
		oper_type = OPER_NONE;
	}
};

class operand_t {
public:
	operand_enum operand_type;
	char table_name[50];						//for TABLE_SCAN
	operation_t *oper;						//for all other operators

	operand_t() {
		operand_type = OPERAND_NONE;
	}
};

extern operation_t exp_root;

#endif //_EXP_TREE_H_