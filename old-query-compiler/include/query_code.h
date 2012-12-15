#ifndef _QUERY_CODE_H_
#define _QUERY_CODE_H_

#include <vector>
#include <string>

#include "exp_tree.h"

using namespace std;

void generate_query_code();

class print_operation;
class select_operation;
class hashJoin_operation;
class tableScan_operation;

class print_operation {
public:
	operation_t *oper;
	hashJoin_operation *input;
	void *consumer;

	void consume();
	void produce();
};

class select_operation {
public:
	operation_t *oper;
	void *input;
	void *consumer;

	void consume();
	void produce();
};

class hashJoin_operation {
public:
	operation_t *oper;
	tableScan_operation *l_input;
	tableScan_operation *r_input;

	print_operation *consumer;

	void consume();
	void produce();
};

class tableScan_operation {
public:
	operation_t *oper;
	void *input;
	hashJoin_operation *consumer;

	void produce();
};
#endif //_QUERY_CODE_H_