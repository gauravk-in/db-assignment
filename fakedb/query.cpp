#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <map>
#include <string.h>

#include "include/query.h"
#include "include/storage.h"
#include "include/schema.h"

using namespace std;

/*	select sum(ol_quantity*ol_amount)                                                                                                                                                                                                            
 *	from customer, "order", orderline                                                                                                                                                                                                            
 *	where o_c_id = c_id                                                                                                                                                                                                                          
 *	and o_w_id = ol_w_id                                                                                                                                                                                                                         
 *	and o_d_id = ol_d_id                                                                                                                                                                                                                         
 *	and o_id = ol_o_id                                                                                                                                                                                                                           
 *	and c_last = 'BARBARBAR'
 */

/*
void query2()
{
	printf("%s\n",__func__);

	vector<orderline>::iterator orderline_iter;
	vector<order>::iterator order_iter;
	vector<customer>::iterator customer_iter;

	orderline_map_t::iterator orderline_map_iter;
	order_map_t::iterator order_map_iter;
	customer_map_t::iterator customer_map_iter;

	uint64_t total_amount=0;

	for(customer_iter=customer_vect.begin(); customer_iter < customer_vect.end(); customer_iter++)
	{
		if(strcmp(customer_iter->c_last, "BARBARBAR")!=0)
			continue;
		else
		{
			order_map_iter=order_map.find()
		}
	}
}
*/

void query1()
{

	vector<orderline>::iterator orderline_iter;
	vector<order>::iterator order_iter;
	vector<customer>::iterator customer_iter;

	orderline_map_t::iterator orderline_map_iter;
	order_map_t::iterator order_map_iter;
	customer_map_t::iterator customer_map_iter;

	order order_temp;
	customer customer_temp;

	uint64_t total_amount=0;
	uint64_t count=0;

	for(orderline_iter=orderline_vect.begin(); orderline_iter < orderline_vect.end(); orderline_iter++)
	{
		order_map_iter=order_map.find(make_tuple(orderline_iter->ol_w_id,
			orderline_iter->ol_d_id, orderline_iter->ol_o_id));
		order_temp=order_vect.at(order_map_iter->second);
		customer_map_iter=customer_map.find(make_tuple(orderline_iter->ol_w_id,
			orderline_iter->ol_d_id, order_temp.o_c_id));
		customer_temp=customer_vect.at(customer_map_iter->second);
		if(strcmp(customer_temp.c_last, "BARBARBAR")==0)
		{
			total_amount += (uint64_t)(orderline_iter->ol_quantity*orderline_iter->ol_amount);
			count++;
		}
	}

	printf("Total Amount = %llu\n", total_amount);
	printf("Count = %llu\n", count);

}

void run_query()
{
	printf("Child Running\n");

	printf("No. of entries = %lld :: %s\n",customer::count,__func__);
	printf("No. of entries = %lld :: %s\n",district::count,__func__);
	printf("No. of entries = %lld :: %s\n",history::count,__func__);
	printf("No. of entries = %lld :: %s\n",item::count,__func__);
	printf("No. of entries = %lld :: %s\n",neworder::count,__func__);
	printf("No. of entries = %lld :: %s\n",order::count,__func__);
	printf("No. of entries = %lld :: %s\n",orderline::count,__func__);
	printf("No. of entries = %lld :: %s\n",stock::count,__func__);
	printf("No. of entries = %lld :: %s\n",warehouse::count,__func__);

	query1();
}