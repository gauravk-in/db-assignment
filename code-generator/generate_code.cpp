#include <stdio.h>
#include <string.h>
#include <list>
#include "include/db_structs.h"
#include "include/main.h"

using namespace std;

int depth=0;

char out_fname_pf[40];

char fname_schema[50];
FILE *fp_schema;

char fname_storage_cpp[50];
FILE *fp_storage_h;

char fname_storage_h[50];
FILE *fp_storage_cpp;

char fname_const_cpp[50];
FILE *fp_const_cpp;

void indent() {
	int i;
	for(i=0;i<depth;i++)
		fprintf(fp_schema, "\t");
}

int generate_code()
{
	list<table_t>::iterator table_it;
	list<field_t>::iterator field_it;

	strcpy(out_fname_pf, out_folder);
	//strcat(out_fname_pf, db_name);


	//_schema.h
	strcpy(fname_schema, out_fname_pf);
	strcat(fname_schema,"schema.h");
	fp_schema=fopen(fname_schema,"w");

	//fprintf(fp_schema, "");
	fprintf(fp_schema, "#ifndef _SCHEMA_H_\n");
	fprintf(fp_schema, "#define _SCHEMA_H_\n\n");
	fprintf(fp_schema, "#include <stdint.h>  // for uint64_t\n");
	fprintf(fp_schema, "#include <stdio.h>  // for FILE\n\n");
	//fprintf(fp_schema, "");
	//fprintf(fp_schema, "");


	for(table_it=table_list.begin();table_it!=table_list.end(); table_it++)
	{
		fprintf(fp_schema, "class %s {\n", table_it->table_name);
		fprintf(fp_schema, "public:\n");
		depth++;
		indent();
		fprintf(fp_schema, "static uint64_t count;\n");
		indent();
		fprintf(fp_schema, "uint64_t tuple_id;\n");
		for(field_it=table_it->field_list.begin();field_it!=table_it->field_list.end();field_it++)
		{
			indent();
			if(field_it->field_size>0)
				fprintf(fp_schema, "%s %s[%d];\n",field_it->field_type,field_it->field_name,field_it->field_size+1);
			else
				fprintf(fp_schema, "%s %s;\n",field_it->field_type,field_it->field_name);
		}
		fprintf(fp_schema, "\n");
		indent();
		fprintf(fp_schema, "void insert();\n");
		indent();
		fprintf(fp_schema, "void remove();\n");
		indent();
		fprintf(fp_schema, "int parse(FILE **fp);\n\n");
		indent();
		fprintf(fp_schema, "%s();\n",table_it->table_name);
		indent();
		//create parameter string
		char par_s[600]="(";
		for(field_it=table_it->field_list.begin();field_it!=table_it->field_list.end();field_it++)
		{
		/*	strcat(par_s, field_it->field_type);
			strcat(par_s, " ");
			strcat(par_s, field_it->field_name);
			if(field_it->field_size>0)
				strcat(par_s, (itoa(field_it->field_size+1),NULL,10);
			strcat(par_s, ",");
		*/
			sprintf(par_s+strlen(par_s), "%s _%s",field_it->field_type, field_it->field_name);
			if(field_it->field_size>0)
				sprintf(par_s+strlen(par_s), "[%d]", field_it->field_size+1);
			sprintf(par_s+strlen(par_s),",");
		}
		par_s[strlen(par_s)-1]=')';
		fprintf(fp_schema, "%s %s;\n",table_it->table_name,par_s);
		depth--;
		fprintf(fp_schema, "};\n\n");
	}

	fprintf(fp_schema, "#endif // _SCHEMA_H_");
	fclose(fp_schema);


	//storage.h
	strcpy(fname_storage_h, out_fname_pf);
	strcat(fname_storage_h,"storage.h");

	fp_storage_h=fopen(fname_storage_h, "w");

	fprintf(fp_storage_h, "#ifndef _STORAGE_H_\n");
	fprintf(fp_storage_h, "#define _STORAGE_H_\n\n");
	fprintf(fp_storage_h, "#include <stdint.h> // for uint64_t\n\n");
	fprintf(fp_storage_h, "#include <vector>\n");
	fprintf(fp_storage_h, "#include <map>\n");
	fprintf(fp_storage_h, "#include <tuple>\n\n");
	fprintf(fp_storage_h, "#include \"schema.h\"\n\n\n");
	fprintf(fp_storage_h, "using namespace std;\n");
	//fprintf(fp_storage_h, "");


	for(table_it=table_list.begin();table_it!=table_list.end(); table_it++)
	{
		fprintf(fp_storage_h,"extern vector<%s> %s_vect;\n",table_it->table_name,table_it->table_name);
		
		if(!table_it->pkeys_list.empty())
		{
			char map_key_s[50]="<";
			for(field_it=table_it->pkeys_list.begin();field_it!=table_it->pkeys_list.end();field_it++)
			{
				strcat(map_key_s,field_it->field_type);
				strcat(map_key_s,",");
			}
			map_key_s[strlen(map_key_s)-1]='>';

			fprintf(fp_storage_h,"typedef map<tuple%s, uint64_t> %s_map_t;\n",map_key_s,table_it->table_name);
			fprintf(fp_storage_h,"extern %s_map_t %s_map;\n",table_it->table_name,table_it->table_name);
		}
		fprintf(fp_storage_h,"extern vector<uint64_t> %s_deleted_vect;\n\n\n",table_it->table_name);
	}

	fprintf(fp_storage_h, "#endif // _STORAGE_H_");
	fclose(fp_storage_h);


	//storage.cpp
	strcpy(fname_storage_cpp, out_fname_pf);
	strcat(fname_storage_cpp,"storage.cpp");

	fp_storage_cpp=fopen(fname_storage_cpp, "w");

	fprintf(fp_storage_cpp, "#include <stdint.h> // for uint64_t\n\n");

	fprintf(fp_storage_cpp, "#include <vector>\n");
	fprintf(fp_storage_cpp, "#include <map>\n");
	fprintf(fp_storage_cpp, "#include <tuple>\n\n");
	fprintf(fp_storage_cpp, "#include \"include/schema.h\"\n");
	fprintf(fp_storage_cpp, "#include \"include/storage.h\"\n\n\n");
	fprintf(fp_storage_cpp, "using namespace std;\n");
	//fprintf(fp_storage_cpp, "");
	//fprintf(fp_storage_cpp, "");

	for(table_it=table_list.begin();table_it!=table_list.end(); table_it++)
	{
		fprintf(fp_storage_cpp,"vector<%s> %s_vect;\n",table_it->table_name,table_it->table_name);
		if(!table_it->pkeys_list.empty())
		{
			fprintf(fp_storage_cpp,"%s_map_t %s_map;\n",table_it->table_name,table_it->table_name);
		}
		fprintf(fp_storage_cpp,"vector<uint64_t> %s_deleted_vect;\n\n\n",table_it->table_name);

		
		//----------------------------------------------
		//insert() code
		fprintf(fp_storage_cpp,"void %s::insert() {\n",table_it->table_name);
		
		//initialize the tuple_id
		fprintf(fp_storage_cpp,"\ttuple_id = count;\n");
		//push this to _vect
		fprintf(fp_storage_cpp,"\t%s_vect.push_back(*this);\n",table_it->table_name);
		
		if(!table_it->pkeys_list.empty())
		{
			//create tuple_string
			char tuple_string[50]="(";
			for(field_it=table_it->pkeys_list.begin();field_it!=table_it->pkeys_list.end();field_it++)
			{
				strcat(tuple_string,field_it->field_name);
				strcat(tuple_string,",");
			}
			tuple_string[strlen(tuple_string)-1]=')';

			//insert key to _map
			fprintf(fp_storage_cpp,"\t%s_map.insert(make_pair(make_tuple%s, count));\n",table_it->table_name,tuple_string);
		}
		//increment count
		fprintf(fp_storage_cpp,"\tcount++;\n");
		fprintf(fp_storage_cpp,"}\n\n\n");
		//---------------------------------------------
		
		//---------------------------------------------
		//remove() code
		fprintf(fp_storage_cpp,"void %s::remove() {\n",table_it->table_name);
		
		if(!table_it->pkeys_list.empty())
		{
			//declare iterator on map
			fprintf(fp_storage_cpp,"\t%s_map_t::iterator %s_map_iter;\n",table_it->table_name,table_it->table_name);
			//create tuple_string
			char tuple_string[50]="(";
			for(field_it=table_it->pkeys_list.begin();field_it!=table_it->pkeys_list.end();field_it++)
			{
				strcat(tuple_string,field_it->field_name);
				strcat(tuple_string,",");
			}
			tuple_string[strlen(tuple_string)-1]=')';

			//find entry in map and erase
			fprintf(fp_storage_cpp,"\t%s_map_iter=%s_map.find(make_tuple%s);\n",table_it->table_name,table_it->table_name,tuple_string);
			fprintf(fp_storage_cpp,"\t%s_map.erase(%s_map_iter);\n",table_it->table_name,table_it->table_name);
		}
		//add deleted tuple_id to _deleted_vect
		fprintf(fp_storage_cpp,"\t%s_deleted_vect.push_back(tuple_id);\n",table_it->table_name);

		//do not erase for now. Put this as a hint.
		fprintf(fp_storage_cpp,"\t//%s_vect.erase(tuple_id);\n",table_it->table_name);
		fprintf(fp_storage_cpp,"}\n\n\n");
		//-----------------------------------------------

	}

	fclose(fp_storage_cpp);

	//schema_constructors.cpp
	strcpy(fname_const_cpp, out_fname_pf);
	strcat(fname_const_cpp,"schema_constructors.cpp");

	fp_const_cpp=fopen(fname_const_cpp, "w");

	fprintf(fp_const_cpp, "#include <string.h>  // for strcpy()\n");
	fprintf(fp_const_cpp, "#include \"include/schema.h\"\n\n\n");
	//fprintf(fp_const_cpp, "\n");
	//fprintf(fp_const_cpp, "\n");
	//fprintf(fp_const_cpp, "\n");
	//fprintf(fp_const_cpp, "\n");
	//fprintf(fp_const_cpp, "\n");
	//fprintf(fp_const_cpp, "\n");
	//fprintf(fp_const_cpp, "\n");


	for(table_it=table_list.begin();table_it!=table_list.end(); table_it++)
	{
		fprintf(fp_const_cpp, "%s::%s() {count=0;}\n\n",table_it->table_name,table_it->table_name);

		//create parameter string
		char par_s[600]="(";
		for(field_it=table_it->field_list.begin();field_it!=table_it->field_list.end();field_it++)
		{
		/*	strcat(par_s, field_it->field_type);
			strcat(par_s, " ");
			strcat(par_s, field_it->field_name);
			if(field_it->field_size>0)
				strcat(par_s, (itoa(field_it->field_size+1),NULL,10);
			strcat(par_s, ",");
		*/
			sprintf(par_s+strlen(par_s), "%s _%s",field_it->field_type, field_it->field_name);
			if(field_it->field_size>0)
				sprintf(par_s+strlen(par_s), "[%d]", field_it->field_size+1);
			sprintf(par_s+strlen(par_s),",");
		}
		par_s[strlen(par_s)-1]=')';

		fprintf(fp_const_cpp, "%s::%s %s\n",table_it->table_name,table_it->table_name,par_s);
		fprintf(fp_const_cpp, "{\n");
		for(field_it=table_it->field_list.begin();field_it!=table_it->field_list.end();field_it++)
		{
			if(!strcmp(field_it->field_type,"char") && field_it->field_size>0)
			{
				fprintf(fp_const_cpp, "\tstrcpy(%s, _%s);\n",field_it->field_name,field_it->field_name);
			}
			else
				fprintf(fp_const_cpp, "\t%s = _%s;\n",field_it->field_name, field_it->field_name);
		}
		fprintf(fp_const_cpp, "}\n\n");
	}
	
	fclose(fp_const_cpp);

	return 1;
}
