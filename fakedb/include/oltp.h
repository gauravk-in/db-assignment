#ifndef _OLTP_H_
#define _OLTP_H_

#include <ctime>
#include <stdint.h>                    //for uint64_t

extern void newOrderRandom(time_t now, uint64_t w_id);
extern void deliveryRandom(time_t now, uint64_t w_id);

#endif //_OLTP_H_