#include <stdint.h>                    //for uint64_t
#include <ctime>                       //for time_t
#include <string.h>                    //For strcpy and strcat
#include <cstdlib>                     //for random
#include "neworder.h"                  //for neworder()
#include <stdio.h>                     // DEBUG for printf

using namespace std;

//create constant integer warehouses = 5;
static int warehouses = 5;

/*
create function varchar(20) genName(integer id)
{
   var array(10) varchar(5) parts = {'BAR','OUGHT','ABLE','PRI','PRES','ESE','ANTI','CALLY','ATION','EING'};
   return parts[(id/100)%10]+parts[(id/10)%10]+parts[id%10];
};
*/

char* genName(int id) {
   char parts[10][6] = {"BAR","OUGHT","ABLE","PRI","PRES","ESE","ANTI","CALLY","ATION","EING"};
   return strcat(strcat(parts[(id/100)%10], parts[(id/10)%10]),parts[id%10]);
}

/*
create function numeric(6,2) randomnumeric62(numeric(6,2) min,numeric(6,2) max)
{
   return min+((cast (random%cast ((max-min)*100) as integer) as numeric(6,2))/100);
};
*/

/*
create function integer nurand(integer A,integer x,integer y)
{
   return ((((random%A)|(random%(y-x+1)+x))+42)%(y-x+1))+x;
};
*/
int nurand(int A, int x, int y) {
   return ((((random()%A)|(random()%(y-x+1)+x))+42)%(y-x+1))+x;
}

/*
create function integer urand(integer min,integer max)
{
   return (random%(max-min+1))+min;
};
*/
int urand(int min, int max)
{
      return (random()%(max-min+1))+min;
}

/*
create function integer urandexcept(integer min,integer max,integer v)
{
   if (max<=min)
      return min;
   var integer r=(random%(max-min))+min;
   if (r>=v)
      return r+1; else
      return r;
};
*/

int urandexcept(int min, int max, int v) {
   if(max<=min)
      return min;
   int r=(random()%(max-min))+min;
   if(r>=v)
      return r+1;
   else
      return r;
}

/*
create function void newOrderRandom(timestamp now,integer w_id)
{
   var integer d_id=execute urand(1,10);
   var integer c_id=execute nurand(1023,1,3000);
   var integer ol_cnt=execute urand(5,15);

   var array(15) integer supware;
   var array(15) integer itemid;
   var array(15) integer qty;
   forsequence (index between 0 and ol_cnt-1) {
      if (execute urand(1,100)>1)
         supware[index]=w_id; else
         supware[index]=execute urandexcept(1,warehouses,w_id);
      itemid[index]=execute nurand(8191,1,100000);
      qty[index]=execute urand(1,10);
   }
   forsequence (index between ol_cnt and 14) {
      supware[index]=w_id;
   }

   execute newOrder(w_id,d_id,c_id,ol_cnt,supware,itemid,qty,now);
};
*/
void newOrderRandom(time_t now, int w_id) {
   int d_id=urand(1,10);
   int c_id=nurand(1023,1,3000);
   int ol_cnt=urand(5,15);

   int supware[15];
   int itemid[15];
   int qty[15];

   //printf("ol_cnt is %d\n",ol_cnt);

   for(int i=0;i<ol_cnt;i++) {
      if(urand(1,100) > 1)
         supware[i]=w_id;
      else
         supware[i]=urandexcept(1,warehouses,w_id);
      itemid[i]=nurand(8191,1,100000);
      qty[i]=urand(1,10);
   }
   for(int i=ol_cnt;i<15;i++) {
      supware[i]=w_id;
   }

   newOrder(w_id,d_id,c_id,ol_cnt,supware,itemid,qty,(uint64_t)now);
}

/*
create function void paymentRandom(timestamp now,integer w_id)
{
   var integer d_id=execute urand(1,10);
   var integer c_w_id;
   var integer c_d_id;
   if (execute urand(1,100)<=85) {
      c_w_id=w_id;
      c_d_id=d_id;
   } else {
      c_w_id=execute urandexcept(1,warehouses,w_id);
      c_d_id=execute urand(1,10);
   }
   var numeric(6,2) h_amount=execute randomnumeric62(1.00,5000.00);
   var timestamp h_date=now;

   if (execute urand(1,100)<=60) {
      execute paymentByName(w_id,d_id,c_w_id,c_d_id,execute genName(execute nurand(255,0,999)),h_date,h_amount,now);
   } else {
      execute paymentById(w_id,d_id,c_w_id,c_d_id,execute nurand(1023,1,3000),h_date,h_amount,now);
   }
};

create function void ostatRandom(integer w_id)
{
   var integer d_id=execute urand(1,10);

   if (execute urand(1,100)<=60) {
      execute ostatByName(w_id,d_id,execute genName(execute nurand(255,0,999)));
   } else {
      execute ostatById(w_id,d_id,execute nurand(1023,1,3000));
   }
};

create function void deliveryRandom(timestamp now,integer w_id)
{
   var integer carrier_id=execute urand(1,10);
   execute delivery(w_id,carrier_id,now);
};

create function void slevRandom(integer w_id)
{
   var integer d_id=execute urand(1,10);
   var integer threshold=execute urand(10,20);

   execute slev(w_id,d_id,threshold);
};

create procedure integer partitionedOltp(timestamp now,integer w_id)
{
   var integer choice=execute urand(1,1000);

   -- Payment?
   if (choice<=430) {
      execute paymentRandom(now,w_id);
      return 1;
   }
   choice=choice-430;

   -- Order status?
   if (choice<=40) {
      execute ostatRandom(w_id);
      return 2;
   }
   choice=choice-40;

   -- Delivery?
   if (choice<=45) {
      execute deliveryRandom(now,w_id);
      return 3;
   }
   choice=choice-45;

   -- Stock level?
   if (choice<=40) {
      execute slevRandom(w_id);
      return 40;
   }

   -- Default to new order
   execute newOrderRandom(now,w_id);
   return 0;
};

create procedure integer oltp(timestamp now)
{
   return execute partitionedOltp(now,execute urand(1,warehouses));
};
*/