#ifndef _SCHEMA_H_
#define _SCHEMA_H_

#include <stdint.h>              //Needed for uint64_t
#include <stdio.h>               //Needed for FILE
#include <string.h>              //Needed for strcpy

#define E_EOF_REACHED -2

class warehouse {
   public:
      int w_id;                  // integer not null,
      char w_name[11];				// varchar(10) not null,
      char w_street_1[21];			// varchar(20) not null,
      char w_street_2[21];			// varchar(20) not null,
      char w_city[21];				// varchar(20) not null,
      char w_state[3];				// varchar(2) not null,
      char w_zip[10];			    	// varchar(9) not null,
      uint64_t w_tax;					
      uint64_t w_ytd;

      int parse(FILE **fp);
};

class district {
   public:
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
      //primary key (d_w_id,d_id)
      int parse(FILE **fp);
};



class customer {
   public:
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
      //primary key (c_w_id,c_d_id,c_id)

      int parse(FILE **fp);
};



//create index customer_wdl on customer(c_w_id,c_d_id,c_last,c_first);

class history {
   public:
      int h_c_id;
      int h_c_d_id;
      int h_c_w_id;
      int h_d_id;
      int h_w_id;
      uint64_t h_date;
      uint64_t h_amount;
      char h_data[25];

      int parse(FILE **fp);
};



class neworder {
   public:
      int no_o_id;
      int no_d_id;
      int no_w_id;
      //primary key (no_w_id,no_d_id,no_o_id)
      
      neworder();
      neworder(int _no_o_id, int _no_d_id, int _no_w_id);

      int parse(FILE **fp);
};



class order {
   public:
      int o_id;
      int o_d_id;
      int o_w_id;
      int o_c_id;
      uint64_t o_entry_d;                 //timestamp
      int o_carrier_id;
      uint64_t o_ol_cnt;
      uint64_t o_all_local;
      //primary key (o_w_id,o_d_id,o_id)
      
      order();
      order(int _o_id, int _o_d_id, int _o_w_id, int _o_c_id, uint64_t _o_entry_d, int _o_carried_id, uint64_t _o_ol_cnt, uint64_t _o_all_local);

      int parse(FILE **fp);
};




//create index order_wdc on "order"(o_w_id,o_d_id,o_c_id,o_id);

class orderline {
   public:
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
      //primary key (ol_w_id,ol_d_id,ol_o_id,ol_number)
      
      orderline();
      orderline(int _ol_o_id, int _ol_d_id, int _ol_w_id, int _ol_number, int _ol_i_id, int _ol_supply_w_id, uint64_t _ol_delivery_d, uint64_t _ol_quantity, uint64_t _ol_amount, char _ol_dist_info[24]);
      int parse(FILE **fp);
};



class item {
   public:
      int i_id;				// integer not null,
      int i_im_id;				// integer not null,
      char i_name[25];				// varchar(24) not null,
      uint64_t i_price;
      char i_data[51];
      							// primary key (i_id)
      int parse(FILE **fp);
};

class stock {
   public:
      int s_i_id;				// integer not null,
      int s_w_id;				// integer not null,
      uint64_t s_quantity;		// numeric(4,0) not null,
      char s_dist_01[25];		// char(24) not null,
      char s_dist_02[25];		// char(24) not null,
      char s_dist_03[25];		// char(24) not null,
      char s_dist_04[25];		// char(24) not null,
      char s_dist_05[25];		// char(24) not null,
      char s_dist_06[25];		// char(24) not null,
      char s_dist_07[25];		// char(24) not null,
      char s_dist_08[25];		// char(24) not null,
      char s_dist_09[25];		// char(24) not null,
      char s_dist_10[25];		// char(24) not null,
      uint64_t s_ytd;			// numeric(8,0) not null,
      uint64_t s_order_cnt;	// numeric(4,0) not null,
      uint64_t s_remote_cnt;	// numeric(4,0) not null,
      char s_data[51];			// varchar(50) not null,
      							// primary key (s_w_id,s_i_id)
      int parse(FILE **fp);
};



#endif //_SCHEMA_H_