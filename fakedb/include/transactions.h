#ifndef _NEWORDER_H_
#define _NEWORDER_H_

#include <stdint.h>                    //for uint64_t

extern void newOrder(uint64_t w_id, uint64_t d_id, uint64_t c_id, int items, long int supware[15], uint64_t itemid[15], long int qty[15], uint64_t datetime);
extern void delivery(uint64_t w_id, uint64_t o_carrier_id, uint64_t datetime);

#endif //_NEWORDER_H_