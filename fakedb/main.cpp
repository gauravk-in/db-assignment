#include <iostream>
#include <cstdlib>                     //for rand
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <ctime>
#include <sys/time.h>
#include <signal.h>
#include <sys/types.h>

#include "include/schema.h"
#include "include/storage.h"
#include "include/data_migrate.h"
#include "include/oltp.h"
#include "include/query.h"

#include <dlfcn.h>

using namespace std;

/*
ostream &operator<<(ostream &output, const warehouse &o)
{
   output << o.w_id << ' ' << o.w_name << ' ' << o.w_zip << endl;
   return output;
}*/

volatile bool childRunning=false;

static void SIGCHLD_handler(int sig) {
   childRunning=false;
}

void display_order(const order o)
{
	printf("%llu\t%llu\t%llu\n",o.o_id, o.o_d_id, o.o_w_id);
	return;
}

int warehouses=5;

int main(int argc, char* argv[]) {
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=0;
	sa.sa_handler=SIGCHLD_handler;
	sigaction(SIGCHLD,&sa,NULL);

	load_customer_from_file();
	load_district_from_file();
	load_history_from_file();
	load_item_from_file();
	load_neworder_from_file();
	load_order_from_file();
	load_orderline_from_file();
	load_stock_from_file();
	load_warehouse_from_file();

	void *qcode_handle;
	void (*query_fn)(void);
	int choice;
/*
	while(1)
	{
		printf("\nChoice :\n1. Run Query\n2.Quit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("Enter path to library\n");
				char lib_path[50];
				scanf("%s",lib_path);
				qcode_handle = dlopen(lib_path, RTLD_LAZY);
				if(!qcode_handle)
				{
					printf("Error in loading library\n%s",dlerror());
					continue;
				}
				query_fn = dlsym(qcode_handle, "query2");
				if(!query_fn)
				{
					printf("Error in loading symbol\n");
					continue;
				}
				query_fn();
				dlclose(qcode_handle);
				break;
			case 2: return 0;
				break;
			default:
				printf("Error !!! \n");

		}
	}

*/
	//while(1) {
	int choice;
	timeval start_time, end_time, time_taken;
	vector<order>::iterator it;

	int i=0;
	for(it=order_vect.begin(); i<10; i++, it++)
		display_order(*it);
		//cout << *i << " "; // print with overloaded operator

	unsigned long int no_iterations=0;

	srand(time(NULL));
	for(int i=0;i<10;i++) {
		childRunning = true;
		gettimeofday(&start_time,NULL);
		pid_t pid=fork();
		if(pid) {
			while(childRunning) {
				//for(unsigned long i=0;i<no_iterations;i++) {
					choice = rand()%100;
					if(choice>10)
						newOrderRandom(time(NULL), rand()%warehouses+1);
					else
						deliveryRandom(time(NULL), rand()%warehouses+1);
				//}
					no_iterations++;
					usleep(500);
			}
		}
		else {
			run_query();
			return 0;
		}
	}
	gettimeofday(&end_time,NULL);

	time_taken.tv_sec = end_time.tv_sec - start_time.tv_sec;
	time_taken.tv_usec = end_time.tv_usec - start_time.tv_usec;

	cout << "Time Taken " << time_taken.tv_sec << " s " << time_taken.tv_usec << " us\n";
	unsigned long int tps;
	tps=no_iterations*1000/(time_taken.tv_sec*1000+time_taken.tv_usec/1000);
	cout << "Transactions per second are " << tps << endl;


	return 0;
}
