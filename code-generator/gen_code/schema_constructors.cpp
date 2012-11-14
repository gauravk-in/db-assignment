#include <string.h>  // for strcpy()
#include "include/schema.h"


warehouse::warehouse() {}

warehouse::warehouse (uint64_t _w_id,char _w_name[11],char _w_street_1[21],char _w_street_2[21],char _w_city[21],char _w_state[3],char _w_zip[10],uint64_t _w_tax,uint64_t _w_ytd)
{
	w_id = _w_id;
	strcpy(w_name, _w_name);
	strcpy(w_street_1, _w_street_1);
	strcpy(w_street_2, _w_street_2);
	strcpy(w_city, _w_city);
	strcpy(w_state, _w_state);
	strcpy(w_zip, _w_zip);
	w_tax = _w_tax;
	w_ytd = _w_ytd;
}

district::district() {}

district::district (uint64_t _d_id,uint64_t _d_w_id,char _d_name[11],char _d_street_1[21],char _d_street_2[21],char _d_city[21],char _d_state[3],char _d_zip[10],uint64_t _d_tax,uint64_t _d_ytd,uint64_t _d_next_o_id)
{
	d_id = _d_id;
	d_w_id = _d_w_id;
	strcpy(d_name, _d_name);
	strcpy(d_street_1, _d_street_1);
	strcpy(d_street_2, _d_street_2);
	strcpy(d_city, _d_city);
	strcpy(d_state, _d_state);
	strcpy(d_zip, _d_zip);
	d_tax = _d_tax;
	d_ytd = _d_ytd;
	d_next_o_id = _d_next_o_id;
}

customer::customer() {}

customer::customer (uint64_t _c_id,uint64_t _c_d_id,uint64_t _c_w_id,char _c_first[17],char _c_middle[3],char _c_last[17],char _c_street_1[21],char _c_street_2[21],char _c_city[21],char _c_state[3],char _c_zip[10],char _c_phone[17],uint64_t _c_since,char _c_credit[3],uint64_t _c_credit_lim,uint64_t _c_discount,uint64_t _c_balance,uint64_t _c_ytd_paymenr,uint64_t _c_payment_cnt,uint64_t _c_delivery_cnt,char _c_data[501])
{
	c_id = _c_id;
	c_d_id = _c_d_id;
	c_w_id = _c_w_id;
	strcpy(c_first, _c_first);
	strcpy(c_middle, _c_middle);
	strcpy(c_last, _c_last);
	strcpy(c_street_1, _c_street_1);
	strcpy(c_street_2, _c_street_2);
	strcpy(c_city, _c_city);
	strcpy(c_state, _c_state);
	strcpy(c_zip, _c_zip);
	strcpy(c_phone, _c_phone);
	c_since = _c_since;
	strcpy(c_credit, _c_credit);
	c_credit_lim = _c_credit_lim;
	c_discount = _c_discount;
	c_balance = _c_balance;
	c_ytd_paymenr = _c_ytd_paymenr;
	c_payment_cnt = _c_payment_cnt;
	c_delivery_cnt = _c_delivery_cnt;
	strcpy(c_data, _c_data);
}

history::history() {}

history::history (uint64_t _h_c_id,uint64_t _h_c_d_id,uint64_t _h_c_w_id,uint64_t _h_d_id,uint64_t _h_w_id,uint64_t _h_date,uint64_t _h_amount,char _h_data[25])
{
	h_c_id = _h_c_id;
	h_c_d_id = _h_c_d_id;
	h_c_w_id = _h_c_w_id;
	h_d_id = _h_d_id;
	h_w_id = _h_w_id;
	h_date = _h_date;
	h_amount = _h_amount;
	strcpy(h_data, _h_data);
}

neworder::neworder() {}

neworder::neworder (uint64_t _no_o_id,uint64_t _no_d_id,uint64_t _no_w_id)
{
	no_o_id = _no_o_id;
	no_d_id = _no_d_id;
	no_w_id = _no_w_id;
}

order::order() {}

order::order (uint64_t _o_id,uint64_t _o_d_id,uint64_t _o_w_id,uint64_t _o_c_id,uint64_t _o_entry_d,uint64_t _o_carrier_id,uint64_t _o_ol_cnt,uint64_t _o_all_local)
{
	o_id = _o_id;
	o_d_id = _o_d_id;
	o_w_id = _o_w_id;
	o_c_id = _o_c_id;
	o_entry_d = _o_entry_d;
	o_carrier_id = _o_carrier_id;
	o_ol_cnt = _o_ol_cnt;
	o_all_local = _o_all_local;
}

orderline::orderline() {}

orderline::orderline (uint64_t _ol_o_id,uint64_t _ol_d_id,uint64_t _ol_w_id,uint64_t _ol_number,uint64_t _ol_i_id,uint64_t _ol_supply_w_id,uint64_t _ol_delivery_d,uint64_t _ol_quantity,uint64_t _ol_amount,char _ol_dist_info[25])
{
	ol_o_id = _ol_o_id;
	ol_d_id = _ol_d_id;
	ol_w_id = _ol_w_id;
	ol_number = _ol_number;
	ol_i_id = _ol_i_id;
	ol_supply_w_id = _ol_supply_w_id;
	ol_delivery_d = _ol_delivery_d;
	ol_quantity = _ol_quantity;
	ol_amount = _ol_amount;
	strcpy(ol_dist_info, _ol_dist_info);
}

item::item() {}

item::item (uint64_t _i_id,uint64_t _i_im_id,char _i_name[25],uint64_t _i_price,char _i_data[51])
{
	i_id = _i_id;
	i_im_id = _i_im_id;
	strcpy(i_name, _i_name);
	i_price = _i_price;
	strcpy(i_data, _i_data);
}

stock::stock() {}

stock::stock (uint64_t _s_i_id,uint64_t _s_w_id,uint64_t _s_quantity,char _s_dist_01[25],char _s_dist_02[25],char _s_dist_03[25],char _s_dist_04[25],char _s_dist_05[25],char _s_dist_06[25],char _s_dist_07[25],char _s_dist_08[25],char _s_dist_09[25],char _s_dist_10[25],uint64_t _s_ytd,uint64_t _s_order_cnt,uint64_t _s_remote_cnt,char _s_data[51])
{
	s_i_id = _s_i_id;
	s_w_id = _s_w_id;
	s_quantity = _s_quantity;
	strcpy(s_dist_01, _s_dist_01);
	strcpy(s_dist_02, _s_dist_02);
	strcpy(s_dist_03, _s_dist_03);
	strcpy(s_dist_04, _s_dist_04);
	strcpy(s_dist_05, _s_dist_05);
	strcpy(s_dist_06, _s_dist_06);
	strcpy(s_dist_07, _s_dist_07);
	strcpy(s_dist_08, _s_dist_08);
	strcpy(s_dist_09, _s_dist_09);
	strcpy(s_dist_10, _s_dist_10);
	s_ytd = _s_ytd;
	s_order_cnt = _s_order_cnt;
	s_remote_cnt = _s_remote_cnt;
	strcpy(s_data, _s_data);
}

