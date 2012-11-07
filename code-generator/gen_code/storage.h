#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <stdint.h> // for uint64_t

#include <vector>
#include <map>
#include <tuple>

#include "schema.h"


using namespace std;
extern vector<warehouse> warehouse_vect;
typedef map<tuple<int>, uint64_t> warehouse_map_t;
extern warehouse_map_t warehouse_map;
extern vector<uint64_t> warehouse_deleted_vect;


extern vector<district> district_vect;
typedef map<tuple<int,int>, uint64_t> district_map_t;
extern district_map_t district_map;
extern vector<uint64_t> district_deleted_vect;


extern vector<customer> customer_vect;
typedef map<tuple<int,int,int>, uint64_t> customer_map_t;
extern customer_map_t customer_map;
extern vector<uint64_t> customer_deleted_vect;


extern vector<history> history_vect;
extern vector<uint64_t> history_deleted_vect;


extern vector<neworder> neworder_vect;
typedef map<tuple<int,int,int>, uint64_t> neworder_map_t;
extern neworder_map_t neworder_map;
extern vector<uint64_t> neworder_deleted_vect;


extern vector<order> order_vect;
typedef map<tuple<int,int,int>, uint64_t> order_map_t;
extern order_map_t order_map;
extern vector<uint64_t> order_deleted_vect;


extern vector<orderline> orderline_vect;
typedef map<tuple<int,int,int,int>, uint64_t> orderline_map_t;
extern orderline_map_t orderline_map;
extern vector<uint64_t> orderline_deleted_vect;


extern vector<item> item_vect;
typedef map<tuple<int>, uint64_t> item_map_t;
extern item_map_t item_map;
extern vector<uint64_t> item_deleted_vect;


extern vector<stock> stock_vect;
typedef map<tuple<int,int>, uint64_t> stock_map_t;
extern stock_map_t stock_map;
extern vector<uint64_t> stock_deleted_vect;


#endif // _STORAGE_H_