#include "include/schema.h"
#include "include/data_migrate.h"

#include <vector>
#include <map>
#include <tuple>

using namespace std;


void newOrder(int w_id, int d_id, int c_id, int items, long int supware[15], long int itemid[15], long int qty[15], uint64_t datetime) {
   //vector<warehouse>::iterator ware_vec_iter;
   warehouse ware_vec_iter;
   //vector<customer>::iterator cust_vec_iter;
   customer cust_vec_iter;
   //vector<district>::iterator dist_vec_iter;
   district dist_vec_iter;

   ////printf("w_id is %d\n",w_id);

   //for(ware_vec_iter=warehouse_vect.begin(); (ware_vec_iter!=warehouse_vect.end() && (ware_vec_iter.w_id!=w_id)); ++ware_vec_iter);
   ware_vec_iter = warehouse_vect.at(warehouse_map.find(make_tuple(w_id))->second);
   //printf("KUKU: %s:%s:%d\n",__FILE__,__func__,__LINE__);
   ////printf("Warehouse found %d\n",ware_vec_iter.w_id);
   //for(cust_vec_iter=customer_vect.begin(); (cust_vec_iter!=customer_vect.end() && (cust_vec_iter.c_w_id!=w_id && cust_vec_iter.c_d_id!=d_id && cust_vec_iter.c_id!=c_id)); ++cust_vec_iter);
   cust_vec_iter = customer_vect.at(customer_map.find(make_tuple(w_id,d_id,c_id))->second);
   //printf("KUKU: %s:%s:%d\n",__FILE__,__func__,__LINE__);
   //for(dist_vec_iter=district_vect.begin(); cust_vec_iter!=customer_vect.end() && (dist_vec_iter.d_w_id!=w_id && dist_vec_iter.d_id!=d_id); ++dist_vec_iter);
   dist_vec_iter = district_vect.at(district_map.find(make_tuple(w_id,d_id))->second);
   //printf("KUKU: %s:%s:%d\n",__FILE__,__func__,__LINE__);

   int all_local = 1;
   for(int i=0;i<items;i++) {
      if(w_id!=supware[i])
         all_local=0;
   }

   int o_id=dist_vec_iter.d_next_o_id; //d_next_o_id as o_id

   order order_new(o_id,d_id,w_id,c_id,datetime,0,items,all_local);
   order_vect.push_back(order_new);

   neworder neworder_new(o_id,d_id,w_id);
   neworder_vect.push_back(neworder_new);

   for(int i=0;i<items;i++) {
      //vector<item>::iterator item_vec_iter;
      item item_vec_iter;
      //vector<stock>::iterator stock_vec_iter;
      stock stock_vec_iter;

      //for(item_vec_iter=item_vect.begin();item_vec_iter!=item_vect.end() && item_vec_iter.i_id!=itemid[i];++item_vec_iter);
      item_vec_iter = item_vect.at(item_map.find(make_tuple(itemid[i]))->second);
      //printf("KUKU: %s:%s:%d\n",__FILE__,__func__,__LINE__);
      //for(stock_vec_iter=stock_vect.begin();stock_vec_iter!=stock_vect.end() && (stock_vec_iter.s_w_id!=supware[i] && stock_vec_iter.s_i_id!=itemid[i]);++stock_vec_iter);
      stock_vec_iter = stock_vect.at(stock_map.find(make_tuple(supware[i],itemid[i]))->second);
      //printf("KUKU: %s:%s:%d\n",__FILE__,__func__,__LINE__);
   
      if(stock_vec_iter.s_quantity > qty[i])
         stock_vec_iter.s_quantity = stock_vec_iter.s_quantity - qty[i];
      else
         stock_vec_iter.s_quantity = stock_vec_iter.s_quantity + 91 - qty[i];

      if(supware[i] != w_id)
         stock_vec_iter.s_remote_cnt = stock_vec_iter.s_remote_cnt +1;
      else
         stock_vec_iter.s_order_cnt = stock_vec_iter.s_order_cnt +1;

      uint64_t ol_amount=qty[i]*(item_vec_iter.i_price)*(1.0+(ware_vec_iter.w_tax)*(1.0-(cust_vec_iter.c_discount)));

      char s_dist[25];
      switch(d_id) {
         case 1: strcpy(stock_vec_iter.s_dist_01,s_dist);
            break;
         case 2: strcpy(stock_vec_iter.s_dist_02,s_dist);
            break;
         case 3: strcpy(stock_vec_iter.s_dist_03,s_dist);
            break;
         case 4: strcpy(stock_vec_iter.s_dist_04,s_dist);
            break;
         case 5: strcpy(stock_vec_iter.s_dist_05,s_dist);
            break;
         case 6: strcpy(stock_vec_iter.s_dist_06,s_dist);
            break;
         case 7: strcpy(stock_vec_iter.s_dist_07,s_dist);
            break;
         case 8: strcpy(stock_vec_iter.s_dist_08,s_dist);
            break;
         case 9: strcpy(stock_vec_iter.s_dist_09,s_dist);
            break;
         case 10: strcpy(stock_vec_iter.s_dist_10,s_dist);
            break;
         default: break;
      }            

      orderline orderline_new(o_id,d_id,w_id,i+1,itemid[i],supware[i],0,qty[i],ol_amount,s_dist);
      orderline_new.insert_new();
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

void delivery(int w_id, int o_carrier_id, uint64_t datetime)
{
   int d_id;

   for(d_id=1; d_id <= 10; d_id++) {
      int o_id;
      order temp_order;
      customer temp_customer;
      neworder_map_t::iterator neworder_map_iter;

      neworder_map_iter = neworder_map.lower_bound(make_tuple(w_id,d_id,0));
      if(neworder_map_iter->second >= neworder_vect.size()) {
         return;
      }
      o_id=neworder_vect.at(neworder_map_iter->second).no_o_id;
      //neworder_vect.erase(neworder_vect.begin()+(neworder_map_iter->second));
      neworder_map.erase(neworder_map_iter);

      temp_order = order_vect.at(order_map.find(make_tuple(w_id, d_id, o_id))->second);
      int o_ol_cnt = temp_order.o_ol_cnt;
      int o_c_id = temp_order.o_c_id;
      temp_order.o_carrier_id=o_carrier_id;

      uint64_t ol_total=0;
      int ol_number;
      for(ol_number=1; ol_number<=temp_order.o_ol_cnt; ol_number++) {
         orderline temp_orderline;
         temp_orderline = orderline_vect.at(orderline_map.find(make_tuple(w_id,d_id,o_id,ol_number))->second);
         ol_total=ol_total + temp_orderline.ol_amount;
         temp_orderline.ol_delivery_d=datetime;
      }

      temp_customer = customer_vect.at(customer_map.find(make_tuple(w_id, d_id,o_c_id))->second);
      temp_customer.c_balance=temp_customer.c_balance + ol_total;

   }
}

/*
create transaction delivery(integer w_id, integer o_carrier_id, timestamp datetime)
{
   forsequence (d_id between 1 and 10) {
      select min(no_o_id) as o_id from neworder where no_w_id=w_id and no_d_id=d_id order by no_o_id else { continue; } -- ignore this district if no row found
      delete from neworder where no_w_id=w_id and no_d_id=d_id and no_o_id=o_id;

      select o_ol_cnt,o_c_id from "order" o where o_w_id=w_id and o_d_id=d_id and o.o_id=o_id;
      update "order" set o_carrier_id=o_carrier_id where o_w_id=w_id and o_d_id=d_id and "order".o_id=o_id;

      var numeric(6,2) ol_total=0;
      forsequence (ol_number between 1 and o_ol_cnt) {
         select ol_amount from orderline where ol_w_id=w_id and ol_d_id=d_id and ol_o_id=o_id and orderline.ol_number=ol_number;
         ol_total=ol_total+ol_amount;
         update orderline set ol_delivery_d=datetime where ol_w_id=w_id and ol_d_id=d_id and ol_o_id=o_id and orderline.ol_number=ol_number;
      }

      update customer set c_balance=c_balance+ol_total where c_w_id=w_id and c_d_id=d_id and c_id=o_c_id;
   }

   commit;
};
*/