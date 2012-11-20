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
#include "include/gen_query_code.h"

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

	query2();
}
