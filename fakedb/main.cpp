#include <iostream>
#include <cstdlib>                     //for random
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <list>
#include <ctime>

#include "schema.h"
#include "data_migrate.h"
#include "oltp.h"

using namespace std;


ostream &operator<<(ostream &output, const warehouse &o)
{
   output << o.w_id << ' ' << o.w_name << ' ' << o.w_zip << endl;
   return output;
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


	list<warehouse>::iterator i;

	for(i=warehouse_list.begin(); i !=warehouse_list.end(); ++i)
		cout << *i << " "; // print with overloaded operator

	scanf("%d",&choice);

	for(double i=0;i<1000;i++)
		newOrderRandom(time(NULL), random()%warehouses+1);
/*
		switch(choice) {
			case 1: printf("\nWhich table to print?\n");
				printf("1. customer\n");
				printf("2. district\n");
				printf("3. history\n");
				printf("4. item\n");
				printf("5. neworder\n");
				printf("6. order\n");
				printf("7. orderline\n");
				printf("8. stock\n");
				printf("9. warehouse\n");
				scanf("%d",&choice);

					switch(choice) {
						case 1: display_customer();
							break;
						case 2: display_district();
							break;
						case 3: display_history();
							break;
						case 4: display_item();
							break;
						case 5: display_neworder();
							break;
						case 6: display_order();
							break;
						case 7: display_orderline();
							break;
						case 8: display_stock();
							break;
						case 9: display_warehouse();
							break;
						default: printf("Wrong Option\n");
					}
				break;
			case 2: return 0;
			default: printf("Wrong Option\n");
		}
	}

*/
	return 0;
}