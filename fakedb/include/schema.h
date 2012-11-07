#ifndef _SCHEMA_H_
#define _SCHEMA_H_

#include <stdint.h>  // for uint64_t
#include <stdio.h>  // for FILE

class warehouse {
public:
	static uint64_t count;
	uint64_t tuple_id;
	int w_id;
	char w_name[11];
	char w_street_1[21];
	char w_street_2[21];
	char w_city[21];
	char w_state[3];
	char w_zip[10];
	uint64_t w_tax;
	uint64_t w_ytd;

	void insert();
	void remove();
	int parse(FILE **fp);

	warehouse();
	warehouse (int _w_id,char _w_name[11],char _w_street_1[21],char _w_street_2[21],char _w_city[21],char _w_state[3],char _w_zip[10],uint64_t _w_tax,uint64_t _w_ytd);
};

class district {
public:
	static uint64_t count;
	uint64_t tuple_id;
	int d_id;
	int d_w_id;
	char d_name[11];
	char d_street_1[21];
	char d_street_2[21];
	char d_city[21];
	char d_state[3];
	char d_zip[10];
	uint64_t d_tax;
	uint64_t d_ytd;
	int d_next_o_id;

	void insert();
	void remove();
	int parse(FILE **fp);

	district();
	district (int _d_id,int _d_w_id,char _d_name[11],char _d_street_1[21],char _d_street_2[21],char _d_city[21],char _d_state[3],char _d_zip[10],uint64_t _d_tax,uint64_t _d_ytd,int _d_next_o_id);
};

class customer {
public:
	static uint64_t count;
	uint64_t tuple_id;
	int c_id;
	int c_d_id;
	int c_w_id;
	char c_first[17];
	char c_middle[3];
	char c_last[17];
	char c_street_1[21];
	char c_street_2[21];
	char c_city[21];
	char c_state[3];
	char c_zip[10];
	char c_phone[17];
	uint64_t c_since;
	char c_credit[3];
	uint64_t c_credit_lim;
	uint64_t c_discount;
	uint64_t c_balance;
	uint64_t c_ytd_paymenr;
	uint64_t c_payment_cnt;
	uint64_t c_delivery_cnt;
	char c_data[501];

	void insert();
	void remove();
	int parse(FILE **fp);

	customer();
	customer (int _c_id,int _c_d_id,int _c_w_id,char _c_first[17],char _c_middle[3],char _c_last[17],char _c_street_1[21],char _c_street_2[21],char _c_city[21],char _c_state[3],char _c_zip[10],char _c_phone[17],uint64_t _c_since,char _c_credit[3],uint64_t _c_credit_lim,uint64_t _c_discount,uint64_t _c_balance,uint64_t _c_ytd_paymenr,uint64_t _c_payment_cnt,uint64_t _c_delivery_cnt,char _c_data[501]);
};

class history {
public:
	static uint64_t count;
	uint64_t tuple_id;
	int h_c_id;
	int h_c_d_id;
	int h_c_w_id;
	int h_d_id;
	int h_w_id;
	uint64_t h_date;
	uint64_t h_amount;
	char h_data[25];

	void insert();
	void remove();
	int parse(FILE **fp);

	history();
	history (int _h_c_id,int _h_c_d_id,int _h_c_w_id,int _h_d_id,int _h_w_id,uint64_t _h_date,uint64_t _h_amount,char _h_data[25]);
};

class neworder {
public:
	static uint64_t count;
	uint64_t tuple_id;
	int no_o_id;
	int no_d_id;
	int no_w_id;

	void insert();
	void remove();
	int parse(FILE **fp);

	neworder();
	neworder (int _no_o_id,int _no_d_id,int _no_w_id);
};

class order {
public:
	static uint64_t count;
	uint64_t tuple_id;
	int o_id;
	int o_d_id;
	int o_w_id;
	int o_c_id;
	uint64_t o_entry_d;
	int o_carrier_id;
	uint64_t o_ol_cnt;
	uint64_t o_all_local;

	void insert();
	void remove();
	int parse(FILE **fp);

	order();
	order (int _o_id,int _o_d_id,int _o_w_id,int _o_c_id,uint64_t _o_entry_d,int _o_carrier_id,uint64_t _o_ol_cnt,uint64_t _o_all_local);
};

class orderline {
public:
	static uint64_t count;
	uint64_t tuple_id;
	int ol_o_id;
	int ol_d_id;
	int ol_w_id;
	int ol_number;
	int ol_i_id;
	int ol_supply_w_id;
	uint64_t ol_delivery_d;
	uint64_t ol_quantity;
	uint64_t ol_amount;
	char ol_dist_info[25];

	void insert();
	void remove();
	int parse(FILE **fp);

	orderline();
	orderline (int _ol_o_id,int _ol_d_id,int _ol_w_id,int _ol_number,int _ol_i_id,int _ol_supply_w_id,uint64_t _ol_delivery_d,uint64_t _ol_quantity,uint64_t _ol_amount,char _ol_dist_info[25]);
};

class item {
public:
	static uint64_t count;
	uint64_t tuple_id;
	int i_id;
	int i_im_id;
	char i_name[25];
	uint64_t i_price;
	char i_data[51];

	void insert();
	void remove();
	int parse(FILE **fp);

	item();
	item (int _i_id,int _i_im_id,char _i_name[25],uint64_t _i_price,char _i_data[51]);
};

class stock {
public:
	static uint64_t count;
	uint64_t tuple_id;
	int s_i_id;
	int s_w_id;
	uint64_t s_quantity;
	char s_dist_01[25];
	char s_dist_02[25];
	char s_dist_03[25];
	char s_dist_04[25];
	char s_dist_05[25];
	char s_dist_06[25];
	char s_dist_07[25];
	char s_dist_08[25];
	char s_dist_09[25];
	char s_dist_10[25];
	uint64_t s_ytd;
	uint64_t s_order_cnt;
	uint64_t s_remote_cnt;
	char s_data[51];

	void insert();
	void remove();
	int parse(FILE **fp);

	stock();
	stock (int _s_i_id,int _s_w_id,uint64_t _s_quantity,char _s_dist_01[25],char _s_dist_02[25],char _s_dist_03[25],char _s_dist_04[25],char _s_dist_05[25],char _s_dist_06[25],char _s_dist_07[25],char _s_dist_08[25],char _s_dist_09[25],char _s_dist_10[25],uint64_t _s_ytd,uint64_t _s_order_cnt,uint64_t _s_remote_cnt,char _s_data[51]);
};

#endif // _SCHEMA_H_