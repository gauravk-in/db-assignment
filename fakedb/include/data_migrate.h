#ifndef _DATA_MIGRATE_H_
#define _DATA_MIGRATE_H_

#include <vector>
#include <map>
#include <tuple>
#include "schema.h"

using namespace std;

int load_customer_from_file();
int load_district_from_file();
int load_history_from_file();
int load_item_from_file();
int load_neworder_from_file();
int load_order_from_file();
int load_orderline_from_file();
int load_stock_from_file();
int load_warehouse_from_file();

extern vector<customer> customer_vect;
extern map<tuple<int,int,int>, uint64_t> customer_map;				//primary key (c_w_id,c_d_id,c_id)
extern vector<district> district_vect;
extern map<tuple<int,int>,uint64_t> district_map;					//primary key (d_w_id,d_id)
extern vector<history> history_vect;
extern map<tuple<int>,uint64_t> history_map;						//primary_key ()
extern vector<item> item_vect;
extern map<tuple<int>,uint64_t> item_map;							// primary key (i_id)
extern vector<neworder> neworder_vect;
extern map<tuple<int,int,int>,uint64_t> neworder_map;				//primary key (no_w_id,no_d_id,no_o_id)
extern vector<orderline> orderline_vect;
extern map<tuple<int,int,int,int>,uint64_t> orderline_map;			//primary key (ol_w_id,ol_d_id,ol_o_id,ol_number)
extern vector<order> order_vect;
extern map<tuple<int,int,int>,uint64_t> order_map;					//primary key (o_w_id,o_d_id,o_id)
extern vector<stock> stock_vect;
extern map<tuple<int,int>,uint64_t> stock_map;						// primary key (s_w_id,s_i_id)
extern vector<warehouse> warehouse_vect;
extern map<tuple<int>,uint64_t> warehouse_map;						//primary key (w_id)

#endif //_DATA_MIGRATE_H_