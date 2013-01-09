/*
 * author: Gaurav Kukreja
 *
 */

#include <string>
#include <list>
#include <vector>

using namespace std;

typedef string field_t;
//typedef string predicate_t;

enum operator_type_t {DEFAULT = 0,
						PRINT,
						SELECT,
						JOIN,
						TABLESCAN
					};

class predicate_t {
public:
	string pred_l_operand;
	string pred_operator;
	string pred_r_operand;
};

class table_field_vect_t{
public:
	string table_name;
	vector<field_t> field_vect;
};

class Operator {
public:
	enum operator_type_t oper_type = DEFAULT;
	Operator *consumer;
	Operator *l_input;
	Operator *r_input;

	//Operator Specific Fields
	//We will not be able to reference to fields declared inside
	//	the derived classes. Try to find an alternative to do this.
	vector<table_field_vect_t> table_vect;
	//vector<field_t> field_list;						//for PRINT, TABLE_SCAN and SELECT
	vector<predicate_t> primary_pred_vect;
	predicate_t hashed_pred;						//for HASH_JOIN
	string table_name;								//for TABLE_SCAN


	//Virtual Functions which will be implemented by each derived class.
	virtual void produce() = 0;
	virtual void consume() = 0;
};

class print_Operator : virtual public Operator {
public:
	//Operator *input;

	void produce();
	void consume();

};

class tableScan_Operator : virtual public Operator {
public:
	//Operator *input;

	void produce();
	void consume() {}			//This needs to be defined for new to work it seems.
};

class select_Operator : virtual public Operator {
public:
	//Operator *input;

	void produce();
	void consume();
};

class join_Operator : virtual public Operator {
public:
	//Operator *l_input;
	//Operator *r_input;

	bool l_input_consumed;					//for HASH_JOIN
	string hash_key_field;					//for HASH_JOIN
	string hash_key_type;
	int joinOp_num;							//used for indexing the hash_maps created for each has operation.					

	void produce();
	void consume();
};

/*
class table_Operator : virtual Operator {
public:	
	char tableName[MAX_TABNAME];

	void produce();
	void consume();
};
*/


