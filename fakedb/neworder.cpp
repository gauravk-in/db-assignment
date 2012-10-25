#include "schema.h"
#include "data_migrate.h"

#include <list>

using namespace std;


void newOrder(int w_id, int d_id, int c_id, int items, int supware[15], int itemid[15], int qty[15], uint64_t datetime) {
   list<warehouse>::iterator ware_iter;
   list<customer>::iterator cust_iter;
   list<district>::iterator dist_iter;

   //printf("w_id is %d\n",w_id);

   for(ware_iter=warehouse_list.begin(); (ware_iter!=warehouse_list.end() && (ware_iter->w_id!=w_id)); ++ware_iter);
   for(cust_iter=customer_list.begin(); (cust_iter!=customer_list.end() && (cust_iter->c_w_id!=w_id && cust_iter->c_d_id!=d_id && cust_iter->c_id!=c_id)); ++cust_iter);
   for(dist_iter=district_list.begin(); cust_iter!=customer_list.end() && (dist_iter->d_w_id!=w_id && dist_iter->d_id!=d_id); ++dist_iter);

   int all_local = 1;
   for(int i=0;i<items;i++) {
      if(w_id!=supware[i])
         all_local=0;
   }

   int o_id=dist_iter->d_next_o_id; //d_next_o_id as o_id

   order *order_new=new order(o_id,d_id,w_id,c_id,datetime,0,items,all_local);
   order_list.push_front(*order_new);

   neworder *neworder_new=new neworder(o_id,d_id,w_id);
   neworder_list.push_front(*neworder_new);

   for(int i=0;i<items;i++) {
      list<item>::iterator item_iter;
      list<stock>::iterator stock_iter;
      for(item_iter=item_list.begin();item_iter!=item_list.end() && item_iter->i_id!=itemid[i];++item_iter);
      for(stock_iter=stock_list.begin();stock_iter!=stock_list.end() && (stock_iter->s_w_id!=supware[i] && stock_iter->s_i_id!=itemid[i]);++stock_iter);
   
      if(stock_iter->s_quantity > qty[i])
         stock_iter->s_quantity = stock_iter->s_quantity - qty[i];
      else
         stock_iter->s_quantity = stock_iter->s_quantity + 91 - qty[i];

      if(supware[i] != w_id)
         stock_iter->s_remote_cnt = stock_iter->s_remote_cnt +1;
      else
         stock_iter->s_order_cnt = stock_iter->s_order_cnt +1;

      uint64_t ol_amount=qty[i]*(item_iter->i_price)*(1.0+(ware_iter->w_tax)*(1.0-(cust_iter->c_discount)));

      char s_dist[25];
      switch(d_id) {
         case 1: strcpy(stock_iter->s_dist_01,s_dist);
            break;
         case 2: strcpy(stock_iter->s_dist_02,s_dist);
            break;
         case 3: strcpy(stock_iter->s_dist_03,s_dist);
            break;
         case 4: strcpy(stock_iter->s_dist_04,s_dist);
            break;
         case 5: strcpy(stock_iter->s_dist_05,s_dist);
            break;
         case 6: strcpy(stock_iter->s_dist_06,s_dist);
            break;
         case 7: strcpy(stock_iter->s_dist_07,s_dist);
            break;
         case 8: strcpy(stock_iter->s_dist_08,s_dist);
            break;
         case 9: strcpy(stock_iter->s_dist_09,s_dist);
            break;
         case 10: strcpy(stock_iter->s_dist_10,s_dist);
            break;
         default: break;
      }            

      orderline *orderline_new=new orderline(o_id,d_id,w_id,i+1,itemid[i],supware[i],0,qty[i],ol_amount,s_dist);
      orderline_list.push_front(*orderline_new);
   }
}

/*
create transaction newOrder ( integer w_id, integer d_id, integer c_id, integer items, array(15) integer supware, array(15) integer itemid, array(15) integer qty, timestamp datetime)
{
   select w_tax from warehouse w where w.w_id=w_id;
   select c_discount from customer c where c_w_id=w_id and c_d_id=d_id and c.c_id=c_id;
   select d_next_o_id as o_id,d_tax from district d where d_w_id=w_id and d.d_id=d_id;
   update district set d_next_o_id=o_id+1 where d_w_id=w_id and district.d_id=d_id;

   var integer all_local = 1;
   forsequence (index between 0 and items-1) {
      if (w_id<>supware[index])
         all_local=0;
   }

   insert into "order" values (o_id,d_id,w_id,c_id,datetime,0,items,all_local);
   insert into neworder values (o_id,d_id,w_id);

   forsequence (index between 0 and items-1) {
      select i_price from item where i_id=itemid[index];
      select s_quantity,s_remote_cnt,s_order_cnt,case d_id when 1 then s_dist_01 when 2 then s_dist_02 when 3 then s_dist_03 when 4 then s_dist_04 when 5 then s_dist_05 when 6 then s_dist_06 when 7 then s_dist_07 when 8 then s_dist_08 when 9 then s_dist_09 when 10 then s_dist_10 end as s_dist from stock where s_w_id=supware[index] and s_i_id=itemid[index];

      if (s_quantity>qty[index]) {
         update stock set s_quantity=s_quantity-qty[index] where s_w_id=supware[index] and s_i_id=itemid[index];
      } else {
         update stock set s_quantity=s_quantity+91-qty[index] where s_w_id=supware[index] and s_i_id=itemid[index];
      }

      if (supware[index]<>w_id) {
         update stock set s_remote_cnt=s_remote_cnt+1 where s_w_id=w_id and s_i_id=itemid[index];
      } else {
         update stock set s_order_cnt=s_order_cnt+1 where s_w_id=w_id and s_i_id=itemid[index];
      }

      var numeric(6,2) ol_amount=qty[index]*i_price*(1.0+w_tax+d_tax)*(1.0-c_discount);
      insert into orderline values (o_id,d_id,w_id,index+1,itemid[index],supware[index],0,qty[index],ol_amount,s_dist);
   }

   commit;
};

*/


