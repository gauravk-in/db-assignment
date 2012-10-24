#ifndef _DATA_MIGRATE_H_
#define _DATA_MIGRATE_H_

#include <list>
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

extern list<customer> customer_list;
extern list<district> district_list;
extern list<history> history_list;
extern list<item> item_list;
extern list<neworder> neworder_list;
extern list<orderline> orderline_list;
extern list<order> order_list;
extern list<stock> stock_list;
extern list<warehouse> warehouse_list;

#endif //_DATA_MIGRATE_H_