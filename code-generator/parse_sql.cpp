#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include "include/main.h"
#include "include/parse_sql.h"
#include "include/db_structs.h"
#include <list>

using namespace std;

void read_fieldSize(char* token, char* field_size) {
	char c;
	int i=0;
	int j=0;
	while(token[i++]!='(');
	do {
		field_size[j++]=token[i++];
	} while(token[i]!=')');
	field_size[j]='\0';
}

int parse_sql() {

	char token[20];
	char field_name[20];
	char field_size[5];
	int end_table;
	int i;
	char char_token;
	int end_pk, end_ik, reset_i;

	fp_sql = fopen(in_fname, "r");

	while(!feof(fp_sql)) {
		//printf("%d\n",__LINE__);
		fscanf(fp_sql, "%s", token);
		if(strcmp(token,"create")==0) {						//create table
			fscanf(fp_sql, "%s", token);
			if(strcmp(token,"table")==0)
			{
				//printf("\t%d\n",__LINE__);
				end_table=0;
				table_t new_table;
				
				//Table Name
				fscanf(fp_sql, "%s", token);
				strcpy(new_table.table_name, token);

				fscanf(fp_sql, "%s", token); 					// { FIX

				//Table Fields, PrimaryKeys
				while(!end_table) 
				{
					//printf("\t\t%d\n",__LINE__);
					fscanf(fp_sql, "%s", field_name);

					//Table Primary Keys
					if(strcmp(field_name,"primary")==0)			//token="primary"
					{
						//printf("\t\t\t\t%d\n",__LINE__);
						fscanf(fp_sql, "%s",token);				//token="key"
						//token="";
						while(fgetc(fp_sql)!='(');						// (
						i=0;
						reset_i=0;
						end_pk=0;
						while(!end_pk) {
							//printf("one key\n");
							if(reset_i) {
								i=0;
								reset_i=0;
							}
							token[i]=(char)fgetc(fp_sql);
							if(token[i]==')' || token[i]==',')
							{
								if(token[i]==')')					
									end_pk=1;
								if(token[i]==',')
									reset_i=1;
								token[i]='\0';
								//printf("\t\t\t\t\t pkey=%s\n",token);
								list<field_t>::iterator field_it=new_table.field_list.begin();
								while(strcmp(field_it->field_name,token)!=0) {
									field_it++;
									//TODO: Handle error of incorrect primary key name
								}
								//printf("\t\t\t\t\t fname=%s\n",field_it->field_name);
								field_it->primary_key=1;
								new_table.pkeys_list.push_back(*field_it);
							}
							i++;
						}

						do {
							fscanf(fp_sql, "%c",&char_token);
						} while(char_token!='\n');
					}
					
					else if(strcmp(field_name,");")==0)
					{
						//printf("table done\n");
						end_table=1;
						do {
							fscanf(fp_sql, "%c",&char_token);
						} while(char_token!='\n');
					}
					
					else if(strcmp(field_name,"primary")!=0)	//not primary
					{
						//printf("\t\t\t%d\n",__LINE__);
						field_t new_field;
						strcpy(new_field.field_name, field_name);

						fscanf(fp_sql, "%s", token);
						if(strcmp(token,"integer")==0) {
							strcpy(new_field.field_type, "uint64_t");
							new_field.field_size=-1;
						}

						else if(strncmp(token,"varchar",7)==0 || strncmp(token,"char",4)==0)
						{
							strcpy(new_field.field_type, "char");
							if(token[strlen(token)-1]==')')
							{
								read_fieldSize(token,field_size);
								new_field.field_size=atoi(field_size);
							}
							else
							{
								new_field.field_size=0;	
							}
						}
						
						else if(strncmp(token,"numeric",7)==0)
						{
							strcpy(new_field.field_type, "uint64_t");
							new_field.field_size=-1;
						}

						else if(strncmp(token,"timestamp",9)==0)
						{
							strcpy(new_field.field_type, "uint64_t");
							new_field.field_size=-1;
						}
						
						new_table.field_list.push_back(new_field);

						do {
							fscanf(fp_sql, "%c",&char_token);
						} while(char_token!='\n');
					}
				}
				//printf("tada!!! \t table_name=%s!!! %d\n",new_table.table_name	,__LINE__);

				table_list.push_back(new_table);
			}

			else if(!strcmp(token,"index"))
			{
				//printf("\t%d\n",__LINE__);
				index_t new_index;
				fscanf(fp_sql, "%s", token);
				strcpy(new_index.index_name, token);
				fscanf(fp_sql, "%s", token);						//token="on"
				while((char)fgetc(fp_sql)!='"');

				//printf("\t%d\n",__LINE__);
				//token="";
				i=0;
				do {
					//printf("\t%d\n",__LINE__);
					token[i]=(char)fgetc(fp_sql);
				} while(token[i++]!='"');
				token[i-1]='\0';
				//printf("\t\t\ttoken=%s\n",token);

				list<table_t>::iterator table_it=table_list.begin();
				while(strcmp(table_it->table_name,token)!=0)
					table_it++;
				//printf("table_name=%s",table_it->table_name);
				new_index.on_table=&(*table_it);

				while((char)fgetc(fp_sql)!='(');

				//token="";
				i=0;
				end_ik=0;								//end of index keys
				reset_i=0;
				while(!end_ik) {
					if(reset_i) {
						i=0;
						reset_i=0;
					}
					token[i]=(char)fgetc(fp_sql);
					if(token[i]==')' || token[i]==',')
					{
						//printf("\t\t\t%d\n",__LINE__);
						if(token[i]==')')					
							end_ik=1;
						if(token[i]==',')
							reset_i=1;
						token[i]='\0';
						list<field_t>::iterator field_it=table_it->field_list.begin();		
						while(strcmp(field_it->field_name,token)!=0) {
							field_it++;
							//TODO: Handle error of incorrect primary key name
						}
						new_index.on_field_list.push_back(*field_it);
					}
					i++;
				}

				index_list.push_back(new_index);
				do {
					fscanf(fp_sql, "%c",&char_token);
				} while(char_token!='\n');
			}
		}
	}
}
