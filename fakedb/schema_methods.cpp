#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "schema.h"

int warehouse::parse(FILE **fp) {
   char token[25];
   int i,j;

   i=0;
   j=1;

   while(1)
   {
      token[i] = fgetc(*fp);
      if(token[i]==EOF)
         return E_EOF_REACHED;

      //printf("character from file = %c\n",token[i]);
      if(token[i]=='|' || token[i]=='\n') 
      {
         token[i] = '\0';
         i=0;

         //printf("j=%d\n",j);

         switch(j) 
         {
            case 1: w_id = atoi(token);
               break;
            case 2: strcpy(token, w_name);
               break;
            case 3: strcpy(token, w_street_1);
               break;
            case 4: strcpy(token, w_street_2);
               break;
            case 5: strcpy(token, w_city);
               break;
            case 6: strcpy(token, w_state);
               break;
            case 7: strcpy(token, w_zip);
               break;
            case 8: w_tax = (uint64_t) atof(token);
               break;
            case 9: w_ytd = (uint64_t) atof(token);
               //printf("all fields filled\n");
               break;
            default: printf("ERR\n");
         }
         if(j==9)
            break;
         else
            j++;
      }
      else
         i++;
   }

   //printf("Loaded warehouse\n");
   return 0;
}

int district::parse(FILE **fp) {
   char token[25];
   int i,j;

   i=0;
   j=1;

   while(1)
   {
      token[i] = fgetc(*fp);
      if(token[i]==EOF)
         return E_EOF_REACHED;

      //printf("character from file = %c\n",token[i]);
      if(token[i]=='|' || token[i]=='\n') 
      {
         token[i] = '\0';
         i=0;

         //printf("j=%d\n",j);

         switch(j) 
         {
            case 1: d_id = atoi(token);
               break;
            case 2: d_w_id = atoi(token);
               break;               
            case 3: strcpy(token, d_name);
               break;
            case 4: strcpy(token, d_street_1);
               break;
            case 5: strcpy(token, d_street_2);
               break;
            case 6: strcpy(token, d_city);
               break;
            case 7: strcpy(token, d_state);
               break;
            case 8: strcpy(token, d_zip);
               break;
            case 9: d_tax = (uint64_t) atof(token);
               break;
            case 10: d_ytd = (uint64_t) atof(token);
               break;
            case 11: d_next_o_id = atoi(token);
               //printf("all fields filled\n");
               break;
            default: printf("ERR\n");
         }
         if(j==11)
            break;
         else
            j++;
      }
      else
         i++;
   }

   //printf("Loaded district\n");
   return 0;
}

int customer::parse(FILE **fp) {
   char token[501];
   int i,j;

   i=0;
   j=1;

   while(1)
   {
      token[i] = fgetc(*fp);
      if(token[i]==EOF)
         return E_EOF_REACHED;

      //printf("character from file = %c\n",token[i]);
      if(token[i]=='|' || token[i]=='\n') 
      {
         token[i] = '\0';
         i=0;

         //printf("j=%d\n",j);

         switch(j) 
         {
            case 1: c_id = atoi(token);
               break;
            case 2: c_d_id = atoi(token);
               break;
            case 3: c_w_id = atoi(token);
               break;                              
            case 4: strcpy(token, c_first);
               break;
            case 5: strcpy(token, c_middle);
               break;
            case 6: strcpy(token, c_last);
               break;
            case 7: strcpy(token, c_street_1);
               break;
            case 8: strcpy(token, c_street_2);
               break;
            case 9: strcpy(token, c_city);
               break;
            case 10: strcpy(token, c_state);
               break;
            case 11: strcpy(token, c_zip);
               break;
            case 12: strcpy(token, c_phone);
               break;
            case 13: c_since = (uint64_t) atof(token);
               break;
            case 14: strcpy(token, c_credit);
               break;
            case 15: c_credit_lim = (uint64_t) atof(token);
               break;
            case 16: c_discount = (uint64_t) atof(token);
               break;
            case 17: c_balance = (uint64_t) atof(token);
               break;
            case 18: c_ytd_paymenr = (uint64_t) atof(token);
               break;
            case 19: c_payment_cnt = (uint64_t) atof(token);
               break;
            case 20: c_delivery_cnt = (uint64_t) atof(token);
               break;                                                                                       
            case 21: strcpy(token, c_data);
               //printf("all fields filled\n");
               break;
            default: printf("ERR\n");
         }
         if(j==21)
            break;
         else
            j++;
      }
      else
         i++;
   }

   //printf("Loaded customer\n");
   return 0;
}

int history::parse(FILE **fp) {
   char token[25];
   int i,j;

   i=0;
   j=1;

   while(1)
   {
      token[i] = fgetc(*fp);
      if(token[i]==EOF)
         return E_EOF_REACHED;

      //printf("character from file = %c\n",token[i]);
      if(token[i]=='|' || token[i]=='\n') 
      {
         token[i] = '\0';
         i=0;

         //printf("j=%d\n",j);

         switch(j) 
         {
            case 1: h_c_id = atoi(token);
               break;
            case 2: h_c_d_id = atoi(token);
               break;
            case 3: h_c_w_id = atoi(token);
               break;
            case 4: h_d_id = atoi(token);
               break;
            case 5: h_w_id = atoi(token);
               break;                                                   
            case 6: h_date = (uint64_t) atof(token);
               break;
            case 7: h_amount = (uint64_t) atof(token);
               break;
            case 8: strcpy(token, h_data);
               //printf("all fields filled\n");
               break;
            default: printf("ERR\n");
         }
         if(j==8)
            break;
         else
            j++;
      }
      else
         i++;
   }

   //printf("Loaded history\n");
   return 0;
}

int neworder::parse(FILE **fp) {
   char token[10];
   int i,j;

   i=0;
   j=1;

   while(1)
   {
      token[i] = fgetc(*fp);
      if(token[i]==EOF)
         return E_EOF_REACHED;

      //printf("character from file = %c\n",token[i]);
      if(token[i]=='|' || token[i]=='\n') 
      {
         token[i] = '\0';
         i=0;

         //printf("j=%d\n",j);

         switch(j) 
         {
            case 1: no_o_id = atoi(token);
               break;
            case 2: no_d_id = atoi(token);
               break;
            case 3: no_w_id = atoi(token);   
               //printf("all fields filled\n");
               break;
            default: printf("ERR\n");
         }
         if(j==3)
            break;
         else
            j++;
      }
      else
         i++;
   }

   //printf("Loaded neworder\n");
   return 0;
}

int order::parse(FILE **fp) {
   char token[25];
   int i,j;

   i=0;
   j=1;

   while(1)
   {
      token[i] = fgetc(*fp);
      if(token[i]==EOF)
         return E_EOF_REACHED;

      //printf("character from file = %c\n",token[i]);
      if(token[i]=='|' || token[i]=='\n') 
      {
         token[i] = '\0';
         i=0;

         //printf("j=%d\n",j);

         switch(j) 
         {
            case 1: o_id = atoi(token);
               break;
            case 2: o_d_id = atoi(token);
               break;
            case 3: o_w_id = atoi(token);
               break;
            case 4: o_c_id = atoi(token);
               break;
            case 5: o_entry_d = (uint64_t) atof(token);
               break;
            case 6: o_carrier_id = atoi(token);
               break;
            case 7: o_ol_cnt = (uint64_t) atof(token);
               break;
            case 8: o_all_local = (uint64_t) atof(token);
               //printf("all fields filled\n");
               break;
            default: printf("ERR\n");
         }
         if(j==8)
            break;
         else
            j++;
      }
      else
         i++;
   }

   //printf("Loaded order\n");
   return 0;
}

int orderline::parse(FILE **fp) {
   char token[25];
   int i,j;

   i=0;
   j=1;

   while(1)
   {
      token[i] = fgetc(*fp);
      if(token[i]==EOF)
         return E_EOF_REACHED;

      //printf("character from file = %c\n",token[i]);
      if(token[i]=='|' || token[i]=='\n') 
      {
         token[i] = '\0';
         i=0;

         //printf("j=%d\n",j);

         switch(j) 
         {
            case 1: ol_o_id = atoi(token);
               break;
            case 2: ol_d_id = atoi(token);
               break;
            case 3: ol_w_id = atoi(token);
               break;
            case 4: ol_number = atoi(token);
               break;
            case 5: ol_i_id = atoi(token);
               break;
            case 6: ol_supply_w_id = atoi(token);
               break;
            case 7: ol_delivery_d = (uint64_t) atof(token);
               break;
            case 8: ol_quantity = (uint64_t) atof(token);
               break;
            case 9: ol_amount = (uint64_t) atof(token);
               break;
            case 10: strcpy(token, ol_dist_info);
               //printf("all fields filled\n");
               break;
            default: printf("ERR\n");
         }
         if(j==10)
            break;
         else
            j++;
      }
      else
         i++;
   }

   //printf("Loaded orderline\n");
   return 0;
}

int item::parse(FILE **fp) {
   char token[51];
   int i,j;

   i=0;
   j=1;

   while(1)
   {
      token[i] = fgetc(*fp);
      if(token[i]==EOF)
         return E_EOF_REACHED;

      //printf("character from file = %c\n",token[i]);
      if(token[i]=='|' || token[i]=='\n') 
      {
         token[i] = '\0';
         i=0;

         //printf("j=%d\n",j);

         switch(j) 
         {
            case 1: i_id = atoi(token);
               break;
            case 2: i_im_id = atoi(token);
               break;
            case 3: strcpy(token, i_name);
               break;
            case 4: i_price = (uint64_t) atof(token);
               break;
            case 5: strcpy(token, i_data);
               //printf("all fields filled\n");
               break;
            default: printf("ERR\n");
         }
         if(j==5)
            break;
         else
            j++;
      }
      else
         i++;
   }

   //printf("Loaded item\n");
   return 0;
}

int stock::parse(FILE **fp) {
   char token[51];
   int i,j;

   i=0;
   j=1;

   while(1)
   {
      token[i] = fgetc(*fp);
      if(token[i]==EOF)
         return E_EOF_REACHED;

      //printf("character from file = %c\n",token[i]);
      if(token[i]=='|' || token[i]=='\n') 
      {
         token[i] = '\0';
         i=0;

         //printf("j=%d\n",j);

         switch(j) 
         {
            case 1: s_i_id = atoi(token);
               break;
            case 2: s_w_id = atoi(token);
               break;
            case 3: s_quantity = (uint64_t) atof(token);
               break;
            case 4: strcpy(token, s_dist_01);
               break;
            case 5: strcpy(token, s_dist_02);
               break;
            case 6: strcpy(token, s_dist_03);
               break;
            case 7: strcpy(token, s_dist_04);
               break; 
            case 8: strcpy(token, s_dist_05);
               break;
            case 9: strcpy(token, s_dist_06);
               break;
            case 10: strcpy(token, s_dist_07);
               break;
            case 11: strcpy(token, s_dist_08);
               break;
            case 12: strcpy(token, s_dist_09);
               break;
            case 13: strcpy(token, s_dist_10);
               break;
            case 14: s_ytd = (uint64_t) atof(token);
               break;
            case 15: s_order_cnt = (uint64_t) atof(token);
               break;
            case 16: s_remote_cnt = (uint64_t) atof(token);
               break;
            case 17: strcpy(token, s_data);
               //printf("all fields filled\n");
               break;
            default: printf("ERR\n");
         }
         if(j==17)
            break;
         else
            j++;
      }
      else
         i++;
   }

   //printf("Loaded stock\n");
   return 0;
}