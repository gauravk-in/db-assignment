#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <list>
#include <stdio.h>

#include "schema.h"
//#include "data_migrate.h"

using namespace std;

char CUSTOMER_TBL_FILE[40]="./../../tables/tpcc_customer.tbl";
char DISTRICT_TBL_FILE[40]="./../../tables/tpcc_district.tbl";
char HISTORY_TBL_FILE[40]="./../../tables/tpcc_history.tbl";
char ITEM_TBL_FILE[40]="./../../tables/tpcc_item.tbl";
char NEWORDER_TBL_FILE[40]="./../../tables/tpcc_neworder.tbl";
char ORDERLINE_TBL_FILE[40]="./../../tables/tpcc_orderline.tbl";
char ORDER_TBL_FILE[40]="./../../tables/tpcc_order.tbl";
char STOCK_TBL_FILE[40]="./../../tables/tpcc_stock.tbl";
char WAREHOUSE_TBL_FILE[40]="./../../tables/tpcc_warehouse.tbl";

list<customer> customer_list;
list<district> district_list;
list<history> history_list;
list<item> item_list;
list<neworder> neworder_list;
list<orderline> orderline_list;
list<order> order_list;
list<stock> stock_list;
list<warehouse> warehouse_list;

int load_customer_from_file() {
	FILE *customer_tbl;
	int count=0;

	customer_tbl=fopen(CUSTOMER_TBL_FILE, "r");

	while(!feof(customer_tbl)) {
		customer temp_customer;
		if(temp_customer.parse(&customer_tbl)==0)
		{
			customer_list.push_front(temp_customer);
			count++;
		}
		else
		{
			//printf("EOF found\n");
		}
	}

	printf("No. of entries = %d :: %s\n",count,__func__);

	fclose(customer_tbl);
	return 0;
}

int load_district_from_file() {
	FILE *district_tbl;
	int count=0;

	district_tbl=fopen(DISTRICT_TBL_FILE, "r");

	while(!feof(district_tbl)) {
		district temp_district;
		if(temp_district.parse(&district_tbl)==0)
		{
			district_list.push_front(temp_district);
			count++;
		}
		else
		{
			//printf("EOF found\n");
		}
	}

	printf("No. of entries = %d :: %s\n",count,__func__);

	fclose(district_tbl);
	return 0;
}

int load_history_from_file() {
	FILE *history_tbl;
	int count=0;

	history_tbl=fopen(HISTORY_TBL_FILE, "r");

	while(!feof(history_tbl)) {
		history temp_history;
		if(temp_history.parse(&history_tbl)==0)
		{
			history_list.push_front(temp_history);
			count++;
		}
		else
		{
			//printf("EOF found\n");
		}
	}

	printf("No. of entries = %d :: %s\n",count,__func__);

	fclose(history_tbl);
	return 0;
}

int load_item_from_file() {
	FILE *item_tbl;
	int count=0;

	item_tbl=fopen(ITEM_TBL_FILE, "r");

	while(!feof(item_tbl)) {
		item temp_item;
		if(temp_item.parse(&item_tbl)==0)
		{
			item_list.push_front(temp_item);
			count++;
		}
		else
		{
			//printf("EOF found\n");
		}
	}

	printf("No. of entries = %d :: %s\n",count,__func__);

	fclose(item_tbl);
	return 0;
}

int load_neworder_from_file() {
	FILE *neworder_tbl;
	int count=0;

	neworder_tbl=fopen(NEWORDER_TBL_FILE, "r");

	while(!feof(neworder_tbl)) {
		neworder temp_neworder;
		if(temp_neworder.parse(&neworder_tbl)==0)
		{
			neworder_list.push_front(temp_neworder);
			count++;
		}
		else
		{
			//printf("EOF found\n");
		}
	}

	printf("No. of entries = %d :: %s\n",count,__func__);

	fclose(neworder_tbl);
	return 0;
}

int load_order_from_file() {
	FILE *order_tbl;
	int count=0;

	order_tbl=fopen(ORDER_TBL_FILE, "r");

	while(!feof(order_tbl)) {
		order temp_order;
		if(temp_order.parse(&order_tbl)==0)
		{
			order_list.push_front(temp_order);
			count++;
		}
		else
		{
			//printf("EOF found\n");
		}
	}

	printf("No. of entries = %d :: %s\n",count,__func__);

	fclose(order_tbl);
	return 0;
}

int load_orderline_from_file() {
	FILE *orderline_tbl;
	int count=0;

	orderline_tbl=fopen(ORDERLINE_TBL_FILE, "r");

	while(!feof(orderline_tbl)) {
		orderline temp_orderline;
		if(temp_orderline.parse(&orderline_tbl)==0)
		{
			orderline_list.push_front(temp_orderline);
			count++;
		}
		else
		{
			//printf("EOF found\n");
		}
	}

	printf("No. of entries = %d :: %s\n",count,__func__);

	fclose(orderline_tbl);
	return 0;
}

int load_stock_from_file() {
	FILE *stock_tbl;
	int count=0;

	stock_tbl=fopen(STOCK_TBL_FILE, "r");

	while(!feof(stock_tbl)) {
		stock temp_stock;
		if(temp_stock.parse(&stock_tbl)==0)
		{
			stock_list.push_front(temp_stock);
			count++;
		}
		else
		{
			//printf("EOF found\n");
		}
	}

	printf("No. of entries = %d :: %s\n",count,__func__);

	fclose(stock_tbl);
	return 0;
}

int load_warehouse_from_file() {
	FILE *warehouse_tbl;
	int count=0;

	warehouse_tbl=fopen(WAREHOUSE_TBL_FILE, "r");

	while(!feof(warehouse_tbl)) {
		warehouse temp_warehouse;
		if(temp_warehouse.parse(&warehouse_tbl)==0)
		{
			warehouse_list.push_front(temp_warehouse);
			count++;
		}
		else
		{
			//printf("EOF found\n");
		}
	}

	printf("No. of entries = %d :: %s\n",count,__func__);

	fclose(warehouse_tbl);
	return 0;
}