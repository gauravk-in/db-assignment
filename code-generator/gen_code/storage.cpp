#include <stdint.h> // for uint64_t

#include <vector>
#include <map>
#include <tuple>

#include "include/schema.h"
#include "include/storage.h"


using namespace std;
vector<warehouse> warehouse_vect;
warehouse_map_t warehouse_map;
vector<uint64_t> warehouse_deleted_vect;


void warehouse::insert() {
	tuple_id = count;
	warehouse_vect.push_back(*this);
	warehouse_map.insert(make_pair(make_tuple(w_id), count));
	count++;
}


void warehouse::remove() {
	warehouse_map_t::iterator warehouse_map_iter;
	warehouse_map_iter=warehouse_map.find(make_tuple(w_id));
	warehouse_map.erase(warehouse_map_iter);
	warehouse_deleted_vect.push_back(tuple_id);
	//warehouse_vect.erase(tuple_id);
}


vector<district> district_vect;
district_map_t district_map;
vector<uint64_t> district_deleted_vect;


void district::insert() {
	tuple_id = count;
	district_vect.push_back(*this);
	district_map.insert(make_pair(make_tuple(d_w_id,d_id), count));
	count++;
}


void district::remove() {
	district_map_t::iterator district_map_iter;
	district_map_iter=district_map.find(make_tuple(d_w_id,d_id));
	district_map.erase(district_map_iter);
	district_deleted_vect.push_back(tuple_id);
	//district_vect.erase(tuple_id);
}


vector<customer> customer_vect;
customer_map_t customer_map;
vector<uint64_t> customer_deleted_vect;


void customer::insert() {
	tuple_id = count;
	customer_vect.push_back(*this);
	customer_map.insert(make_pair(make_tuple(c_w_id,c_d_id,c_id), count));
	count++;
}


void customer::remove() {
	customer_map_t::iterator customer_map_iter;
	customer_map_iter=customer_map.find(make_tuple(c_w_id,c_d_id,c_id));
	customer_map.erase(customer_map_iter);
	customer_deleted_vect.push_back(tuple_id);
	//customer_vect.erase(tuple_id);
}


vector<history> history_vect;
vector<uint64_t> history_deleted_vect;


void history::insert() {
	tuple_id = count;
	history_vect.push_back(*this);
	count++;
}


void history::remove() {
	history_deleted_vect.push_back(tuple_id);
	//history_vect.erase(tuple_id);
}


vector<neworder> neworder_vect;
neworder_map_t neworder_map;
vector<uint64_t> neworder_deleted_vect;


void neworder::insert() {
	tuple_id = count;
	neworder_vect.push_back(*this);
	neworder_map.insert(make_pair(make_tuple(no_w_id,no_d_id,no_o_id), count));
	count++;
}


void neworder::remove() {
	neworder_map_t::iterator neworder_map_iter;
	neworder_map_iter=neworder_map.find(make_tuple(no_w_id,no_d_id,no_o_id));
	neworder_map.erase(neworder_map_iter);
	neworder_deleted_vect.push_back(tuple_id);
	//neworder_vect.erase(tuple_id);
}


vector<order> order_vect;
order_map_t order_map;
vector<uint64_t> order_deleted_vect;


void order::insert() {
	tuple_id = count;
	order_vect.push_back(*this);
	order_map.insert(make_pair(make_tuple(o_w_id,o_d_id,o_id), count));
	count++;
}


void order::remove() {
	order_map_t::iterator order_map_iter;
	order_map_iter=order_map.find(make_tuple(o_w_id,o_d_id,o_id));
	order_map.erase(order_map_iter);
	order_deleted_vect.push_back(tuple_id);
	//order_vect.erase(tuple_id);
}


vector<orderline> orderline_vect;
orderline_map_t orderline_map;
vector<uint64_t> orderline_deleted_vect;


void orderline::insert() {
	tuple_id = count;
	orderline_vect.push_back(*this);
	orderline_map.insert(make_pair(make_tuple(ol_w_id,ol_d_id,ol_o_id,ol_number), count));
	count++;
}


void orderline::remove() {
	orderline_map_t::iterator orderline_map_iter;
	orderline_map_iter=orderline_map.find(make_tuple(ol_w_id,ol_d_id,ol_o_id,ol_number));
	orderline_map.erase(orderline_map_iter);
	orderline_deleted_vect.push_back(tuple_id);
	//orderline_vect.erase(tuple_id);
}


vector<item> item_vect;
item_map_t item_map;
vector<uint64_t> item_deleted_vect;


void item::insert() {
	tuple_id = count;
	item_vect.push_back(*this);
	item_map.insert(make_pair(make_tuple(i_id), count));
	count++;
}


void item::remove() {
	item_map_t::iterator item_map_iter;
	item_map_iter=item_map.find(make_tuple(i_id));
	item_map.erase(item_map_iter);
	item_deleted_vect.push_back(tuple_id);
	//item_vect.erase(tuple_id);
}


vector<stock> stock_vect;
stock_map_t stock_map;
vector<uint64_t> stock_deleted_vect;


void stock::insert() {
	tuple_id = count;
	stock_vect.push_back(*this);
	stock_map.insert(make_pair(make_tuple(s_w_id,s_i_id), count));
	count++;
}


void stock::remove() {
	stock_map_t::iterator stock_map_iter;
	stock_map_iter=stock_map.find(make_tuple(s_w_id,s_i_id));
	stock_map.erase(stock_map_iter);
	stock_deleted_vect.push_back(tuple_id);
	//stock_vect.erase(tuple_id);
}


