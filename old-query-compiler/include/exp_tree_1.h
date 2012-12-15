#ifndef _EXP_TREE_H_
#define _EXP_TREE_H_

enum node_type_enum {
	OPN_PRINT,
	OPN_SELECT,
	OPN_HASHJOIN,
	OPN_TABLESCAN,
	OPD_TABLE
}

class node {
	node_type_enum type;
	node *l_opd;
	node *r_opd;
};


#endif //_EXP_TREE_H_