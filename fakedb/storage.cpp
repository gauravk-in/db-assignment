#include <iostream>
#include <stdint.h> // for uint64_t

#include <vector>
#include <map>
#include <tuple>

#include "include/schema.h"
#include "include/storage.h"
#include <string.h>


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
	//Remove the entry in map that points to current tuple
	warehouse_map_t::iterator warehouse_map_iter;
	warehouse_map_iter=warehouse_map.find(make_tuple(w_id));
	warehouse_map.erase(warehouse_map_iter);
	//Move last tuple in vector in the place of the deleted tuple
	//If current tuple is not the last tuple,
	if(tuple_id != count - 1) {

		//Move content of last tuple to fields in this tuple
		warehouse warehouse_vect_last_iter;
		warehouse_vect_last_iter=warehouse_vect.at(count - 1);

		w_id = warehouse_vect_last_iter.w_id;
		strcpy(w_name, warehouse_vect_last_iter.w_name);
		strcpy(w_street_1, warehouse_vect_last_iter.w_street_1);
		strcpy(w_street_2, warehouse_vect_last_iter.w_street_2);
		strcpy(w_city, warehouse_vect_last_iter.w_city);
		strcpy(w_state, warehouse_vect_last_iter.w_state);
		strcpy(w_zip, warehouse_vect_last_iter.w_zip);
		w_tax = warehouse_vect_last_iter.w_tax;
		w_ytd = warehouse_vect_last_iter.w_ytd;
	
		//Remove the entry for the last tuple in map, and insert a new one with new tuple_id
		warehouse_map_t::iterator warehouse_map_iter;
		warehouse_map_iter=warehouse_map.find(make_tuple(w_id));
		if(warehouse_map_iter != warehouse_map.end())
			warehouse_map.erase(warehouse_map_iter);
		warehouse_map.insert(make_pair(make_tuple(w_id), tuple_id));;
	
		//Call remove on the last entry of the vector
		warehouse_vect_last_iter.remove();
	}
	else {		//if the tuple is the last tuple in the vector
		count--;
		warehouse_vect.pop_back();
	}
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
	//Remove the entry in map that points to current tuple
	district_map_t::iterator district_map_iter;
	district_map_iter=district_map.find(make_tuple(d_w_id,d_id));
	district_map.erase(district_map_iter);
	//Move last tuple in vector in the place of the deleted tuple
	//If current tuple is not the last tuple,
	if(tuple_id != count - 1) {

		//Move content of last tuple to fields in this tuple
		district district_vect_last_iter;
		district_vect_last_iter=district_vect.at(count - 1);

		d_id = district_vect_last_iter.d_id;
		d_w_id = district_vect_last_iter.d_w_id;
		strcpy(d_name, district_vect_last_iter.d_name);
		strcpy(d_street_1, district_vect_last_iter.d_street_1);
		strcpy(d_street_2, district_vect_last_iter.d_street_2);
		strcpy(d_city, district_vect_last_iter.d_city);
		strcpy(d_state, district_vect_last_iter.d_state);
		strcpy(d_zip, district_vect_last_iter.d_zip);
		d_tax = district_vect_last_iter.d_tax;
		d_ytd = district_vect_last_iter.d_ytd;
		d_next_o_id = district_vect_last_iter.d_next_o_id;
	
		//Remove the entry for the last tuple in map, and insert a new one with new tuple_id
		district_map_t::iterator district_map_iter;
		district_map_iter=district_map.find(make_tuple(d_w_id,d_id));
		if(district_map_iter != district_map.end())
			district_map.erase(district_map_iter);
		district_map.insert(make_pair(make_tuple(d_w_id,d_id), tuple_id));;
	
		//Call remove on the last entry of the vector
		district_vect_last_iter.remove();
	}
	else {		//if the tuple is the last tuple in the vector
		count--;
		district_vect.pop_back();
	}
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
	//Remove the entry in map that points to current tuple
	customer_map_t::iterator customer_map_iter;
	customer_map_iter=customer_map.find(make_tuple(c_w_id,c_d_id,c_id));
	customer_map.erase(customer_map_iter);
	//Move last tuple in vector in the place of the deleted tuple
	//If current tuple is not the last tuple,
	if(tuple_id != count - 1) {

		//Move content of last tuple to fields in this tuple
		customer customer_vect_last_iter;
		customer_vect_last_iter=customer_vect.at(count - 1);

		c_id = customer_vect_last_iter.c_id;
		c_d_id = customer_vect_last_iter.c_d_id;
		c_w_id = customer_vect_last_iter.c_w_id;
		strcpy(c_first, customer_vect_last_iter.c_first);
		strcpy(c_middle, customer_vect_last_iter.c_middle);
		strcpy(c_last, customer_vect_last_iter.c_last);
		strcpy(c_street_1, customer_vect_last_iter.c_street_1);
		strcpy(c_street_2, customer_vect_last_iter.c_street_2);
		strcpy(c_city, customer_vect_last_iter.c_city);
		strcpy(c_state, customer_vect_last_iter.c_state);
		strcpy(c_zip, customer_vect_last_iter.c_zip);
		strcpy(c_phone, customer_vect_last_iter.c_phone);
		c_since = customer_vect_last_iter.c_since;
		strcpy(c_credit, customer_vect_last_iter.c_credit);
		c_credit_lim = customer_vect_last_iter.c_credit_lim;
		c_discount = customer_vect_last_iter.c_discount;
		c_balance = customer_vect_last_iter.c_balance;
		c_ytd_paymenr = customer_vect_last_iter.c_ytd_paymenr;
		c_payment_cnt = customer_vect_last_iter.c_payment_cnt;
		c_delivery_cnt = customer_vect_last_iter.c_delivery_cnt;
		strcpy(c_data, customer_vect_last_iter.c_data);
	
		//Remove the entry for the last tuple in map, and insert a new one with new tuple_id
		customer_map_t::iterator customer_map_iter;
		customer_map_iter=customer_map.find(make_tuple(c_w_id,c_d_id,c_id));
		if(customer_map_iter != customer_map.end())
			customer_map.erase(customer_map_iter);
		customer_map.insert(make_pair(make_tuple(c_w_id,c_d_id,c_id), tuple_id));;
	
		//Call remove on the last entry of the vector
		customer_vect_last_iter.remove();
	}
	else {		//if the tuple is the last tuple in the vector
		count--;
		customer_vect.pop_back();
	}
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
	//Remove the entry in map that points to current tuple
	//Move last tuple in vector in the place of the deleted tuple
	//If current tuple is not the last tuple,
	if(tuple_id != count - 1) {

		//Move content of last tuple to fields in this tuple
		history history_vect_last_iter;
		history_vect_last_iter=history_vect.at(count - 1);

		h_c_id = history_vect_last_iter.h_c_id;
		h_c_d_id = history_vect_last_iter.h_c_d_id;
		h_c_w_id = history_vect_last_iter.h_c_w_id;
		h_d_id = history_vect_last_iter.h_d_id;
		h_w_id = history_vect_last_iter.h_w_id;
		h_date = history_vect_last_iter.h_date;
		h_amount = history_vect_last_iter.h_amount;
		strcpy(h_data, history_vect_last_iter.h_data);
	
		//Remove the entry for the last tuple in map, and insert a new one with new tuple_id
	}
	else {		//if the tuple is the last tuple in the vector
		count--;
		history_vect.pop_back();
	}
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
	//Remove the entry in map that points to current tuple
	neworder_map_t::iterator neworder_map_iter;
	neworder_map_iter=neworder_map.find(make_tuple(no_w_id,no_d_id,no_o_id));
	neworder_map.erase(neworder_map_iter);
	//Move last tuple in vector in the place of the deleted tuple
	//If current tuple is not the last tuple,
	if(tuple_id != count - 1) {

		//Move content of last tuple to fields in this tuple
		neworder neworder_vect_last_iter;
		neworder_vect_last_iter=neworder_vect.at(count - 1);

		no_o_id = neworder_vect_last_iter.no_o_id;
		no_d_id = neworder_vect_last_iter.no_d_id;
		no_w_id = neworder_vect_last_iter.no_w_id;
	
		//Remove the entry for the last tuple in map, and insert a new one with new tuple_id
		neworder_map_t::iterator neworder_map_iter;
		neworder_map_iter=neworder_map.find(make_tuple(no_w_id,no_d_id,no_o_id));
		if(neworder_map_iter != neworder_map.end())
			neworder_map.erase(neworder_map_iter);
		neworder_map.insert(make_pair(make_tuple(no_w_id,no_d_id,no_o_id), tuple_id));;
	
		//Call remove on the last entry of the vector
		neworder_vect_last_iter.remove();
	}
	else {		//if the tuple is the last tuple in the vector
		count--;
		neworder_vect.pop_back();
	}
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
	//Remove the entry in map that points to current tuple
	order_map_t::iterator order_map_iter;
	order_map_iter=order_map.find(make_tuple(o_w_id,o_d_id,o_id));
	order_map.erase(order_map_iter);
	//Move last tuple in vector in the place of the deleted tuple
	//If current tuple is not the last tuple,
	if(tuple_id != count - 1) {

		//Move content of last tuple to fields in this tuple
		order order_vect_last_iter;
		order_vect_last_iter=order_vect.at(count - 1);

		o_id = order_vect_last_iter.o_id;
		o_d_id = order_vect_last_iter.o_d_id;
		o_w_id = order_vect_last_iter.o_w_id;
		o_c_id = order_vect_last_iter.o_c_id;
		o_entry_d = order_vect_last_iter.o_entry_d;
		o_carrier_id = order_vect_last_iter.o_carrier_id;
		o_ol_cnt = order_vect_last_iter.o_ol_cnt;
		o_all_local = order_vect_last_iter.o_all_local;
	
		//Remove the entry for the last tuple in map, and insert a new one with new tuple_id
		order_map_t::iterator order_map_iter;
		order_map_iter=order_map.find(make_tuple(o_w_id,o_d_id,o_id));
		if(order_map_iter != order_map.end())
			order_map.erase(order_map_iter);
		order_map.insert(make_pair(make_tuple(o_w_id,o_d_id,o_id), tuple_id));;
	
		//Call remove on the last entry of the vector
		order_vect_last_iter.remove();
	}
	else {		//if the tuple is the last tuple in the vector
		count--;
		order_vect.pop_back();
	}
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
	//Remove the entry in map that points to current tuple
	orderline_map_t::iterator orderline_map_iter;
	orderline_map_iter=orderline_map.find(make_tuple(ol_w_id,ol_d_id,ol_o_id,ol_number));
	orderline_map.erase(orderline_map_iter);
	//Move last tuple in vector in the place of the deleted tuple
	//If current tuple is not the last tuple,
	if(tuple_id != count - 1) {

		//Move content of last tuple to fields in this tuple
		orderline orderline_vect_last_iter;
		orderline_vect_last_iter=orderline_vect.at(count - 1);

		ol_o_id = orderline_vect_last_iter.ol_o_id;
		ol_d_id = orderline_vect_last_iter.ol_d_id;
		ol_w_id = orderline_vect_last_iter.ol_w_id;
		ol_number = orderline_vect_last_iter.ol_number;
		ol_i_id = orderline_vect_last_iter.ol_i_id;
		ol_supply_w_id = orderline_vect_last_iter.ol_supply_w_id;
		ol_delivery_d = orderline_vect_last_iter.ol_delivery_d;
		ol_quantity = orderline_vect_last_iter.ol_quantity;
		ol_amount = orderline_vect_last_iter.ol_amount;
		strcpy(ol_dist_info, orderline_vect_last_iter.ol_dist_info);
	
		//Remove the entry for the last tuple in map, and insert a new one with new tuple_id
		orderline_map_t::iterator orderline_map_iter;
		orderline_map_iter=orderline_map.find(make_tuple(ol_w_id,ol_d_id,ol_o_id,ol_number));
		if(orderline_map_iter != orderline_map.end())
			orderline_map.erase(orderline_map_iter);
		orderline_map.insert(make_pair(make_tuple(ol_w_id,ol_d_id,ol_o_id,ol_number), tuple_id));;
	
		//Call remove on the last entry of the vector
		orderline_vect_last_iter.remove();
	}
	else {		//if the tuple is the last tuple in the vector
		count--;
		orderline_vect.pop_back();
	}
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
	//Remove the entry in map that points to current tuple
	item_map_t::iterator item_map_iter;
	item_map_iter=item_map.find(make_tuple(i_id));
	item_map.erase(item_map_iter);
	//Move last tuple in vector in the place of the deleted tuple
	//If current tuple is not the last tuple,
	if(tuple_id != count - 1) {

		//Move content of last tuple to fields in this tuple
		item item_vect_last_iter;
		item_vect_last_iter=item_vect.at(count - 1);

		i_id = item_vect_last_iter.i_id;
		i_im_id = item_vect_last_iter.i_im_id;
		strcpy(i_name, item_vect_last_iter.i_name);
		i_price = item_vect_last_iter.i_price;
		strcpy(i_data, item_vect_last_iter.i_data);
	
		//Remove the entry for the last tuple in map, and insert a new one with new tuple_id
		item_map_t::iterator item_map_iter;
		item_map_iter=item_map.find(make_tuple(i_id));
		if(item_map_iter != item_map.end())
			item_map.erase(item_map_iter);
		item_map.insert(make_pair(make_tuple(i_id), tuple_id));;
	
		//Call remove on the last entry of the vector
		item_vect_last_iter.remove();
	}
	else {		//if the tuple is the last tuple in the vector
		count--;
		item_vect.pop_back();
	}
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
	//Remove the entry in map that points to current tuple
	stock_map_t::iterator stock_map_iter;
	stock_map_iter=stock_map.find(make_tuple(s_w_id,s_i_id));
	stock_map.erase(stock_map_iter);
	//Move last tuple in vector in the place of the deleted tuple
	//If current tuple is not the last tuple,
	if(tuple_id != count - 1) {

		//Move content of last tuple to fields in this tuple
		stock stock_vect_last_iter;
		stock_vect_last_iter=stock_vect.at(count - 1);

		s_i_id = stock_vect_last_iter.s_i_id;
		s_w_id = stock_vect_last_iter.s_w_id;
		s_quantity = stock_vect_last_iter.s_quantity;
		strcpy(s_dist_01, stock_vect_last_iter.s_dist_01);
		strcpy(s_dist_02, stock_vect_last_iter.s_dist_02);
		strcpy(s_dist_03, stock_vect_last_iter.s_dist_03);
		strcpy(s_dist_04, stock_vect_last_iter.s_dist_04);
		strcpy(s_dist_05, stock_vect_last_iter.s_dist_05);
		strcpy(s_dist_06, stock_vect_last_iter.s_dist_06);
		strcpy(s_dist_07, stock_vect_last_iter.s_dist_07);
		strcpy(s_dist_08, stock_vect_last_iter.s_dist_08);
		strcpy(s_dist_09, stock_vect_last_iter.s_dist_09);
		strcpy(s_dist_10, stock_vect_last_iter.s_dist_10);
		s_ytd = stock_vect_last_iter.s_ytd;
		s_order_cnt = stock_vect_last_iter.s_order_cnt;
		s_remote_cnt = stock_vect_last_iter.s_remote_cnt;
		strcpy(s_data, stock_vect_last_iter.s_data);
	
		//Remove the entry for the last tuple in map, and insert a new one with new tuple_id
		stock_map_t::iterator stock_map_iter;
		stock_map_iter=stock_map.find(make_tuple(s_w_id,s_i_id));
		if(stock_map_iter != stock_map.end())
			stock_map.erase(stock_map_iter);
		stock_map.insert(make_pair(make_tuple(s_w_id,s_i_id), tuple_id));;
	
		//Call remove on the last entry of the vector
		stock_vect_last_iter.remove();
	}
	else {		//if the tuple is the last tuple in the vector
		count--;
		stock_vect.pop_back();
	}
	//stock_vect.erase(tuple_id);
}


