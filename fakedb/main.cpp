#include <iostream>
#include <cstdlib>                     //for random
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <list>
#include <ctime>
#include <sys/time.h>

#include "schema.h"
#include "data_migrate.h"
#include "oltp.h"

using namespace std;

/*
ostream &operator<<(ostream &output, const warehouse &o)
{
   output << o.w_id << ' ' << o.w_name << ' ' << o.w_zip << endl;
   return output;
}*/

void display_warehouse(const warehouse w)
{
	printf("%d\t%s\t%s\n",w.w_id, w.w_name, w.w_zip);
	return;
}

int warehouses=5;

int main(int argc, char* argv[]) {

	load_customer_from_file();
	load_district_from_file();
	load_history_from_file();
	load_item_from_file();
	load_neworder_from_file();
	load_order_from_file();
	load_orderline_from_file();
	load_stock_from_file();
	load_warehouse_from_file();

	//while(1) {
	int choice;
	timeval start_time, end_time, time_taken;

	list<warehouse>::iterator i;

	for(i=warehouse_list.begin(); i !=warehouse_list.end(); ++i)
		display_warehouse(*i);
		//cout << *i << " "; // print with overloaded operator

	gettimeofday(&start_time,NULL);
	for(double i=0;i<1000;i++)
		newOrderRandom(time(NULL), random()%warehouses+1);
	gettimeofday(&end_time,NULL);

	time_taken.tv_sec = end_time.tv_sec - start_time.tv_sec;
	time_taken.tv_usec = end_time.tv_usec - start_time.tv_usec;

	cout << "Time Taken " << time_taken.tv_sec << " s " << time_taken.tv_usec << " us\n";
	cout << "newOrder operations per second are " << 1000/time_taken.tv_sec << endl;

	return 0;
}