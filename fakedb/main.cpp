#include <iostream>
#include <cstdlib>                     //for rand
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <vector>
#include <ctime>
#include <sys/time.h>

#include "include/schema.h"
#include "include/data_migrate.h"
#include "include/oltp.h"

using namespace std;

#define no_iterations 1000000

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
	vector<warehouse>::iterator it;

	for(it=warehouse_vect.begin(); it !=warehouse_vect.end(); ++it)
		display_warehouse(*it);
		//cout << *i << " "; // print with overloaded operator

	gettimeofday(&start_time,NULL);
	for(unsigned long i=0;i<no_iterations;i++) {
		srand(time(NULL));
		choice = rand()%1000;
		if(choice>100)
			newOrderRandom(time(NULL), rand()%warehouses+1);
		else
			deliveryRandom(time(NULL), rand()%warehouses+1);
	}
	gettimeofday(&end_time,NULL);

	time_taken.tv_sec = end_time.tv_sec - start_time.tv_sec;
	time_taken.tv_usec = end_time.tv_usec - start_time.tv_usec;

	cout << "Time Taken " << time_taken.tv_sec << " s " << time_taken.tv_usec << " us\n";
	unsigned long int tps;
	tps=no_iterations*1000/(time_taken.tv_sec*1000+time_taken.tv_usec/1000);
	cout << "newOrder operations per second are " << tps << endl;

	return 0;
}