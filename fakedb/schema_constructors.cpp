#include "schema.h"

orderline::orderline() {}

orderline::orderline(int _ol_o_id, int _ol_d_id, int _ol_w_id, int _ol_number, int _ol_i_id, int _ol_supply_w_id, uint64_t _ol_delivery_d, uint64_t _ol_quantity, uint64_t _ol_amount, char _ol_dist_info[24]) {
      ol_o_id=_ol_o_id;
      ol_d_id=_ol_d_id;
      ol_w_id=_ol_w_id;
      ol_number=_ol_number;
      ol_i_id=_ol_i_id;
      ol_supply_w_id=_ol_supply_w_id;
      ol_delivery_d=_ol_delivery_d;
      ol_quantity=_ol_quantity;
      ol_amount=_ol_amount;
      strcpy(_ol_dist_info, ol_dist_info);
}

order::order() {}

order::order(int _o_id, int _o_d_id, int _o_w_id, int _o_c_id, uint64_t _o_entry_d, int _o_carried_id, uint64_t _o_ol_cnt, uint64_t _o_all_local) {
      o_id=_o_id;
      o_d_id=_o_d_id;
      o_w_id=_o_w_id;
      o_c_id=_o_c_id;
      o_entry_d=_o_entry_d;
      o_carrier_id=_o_carried_id;
      o_ol_cnt=_o_ol_cnt;
      o_all_local=_o_all_local;
}

neworder::neworder() {}

neworder::neworder(int _no_o_id, int _no_d_id, int _no_w_id) {
      no_o_id=_no_o_id;
      no_d_id=_no_d_id;
      no_w_id=_no_w_id;
}