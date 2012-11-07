#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <string.h>

#include "include/db_structs.h"
#include "include/parse_sql.h"
#include "include/generate_code.h"

FILE *fp_sql;

char in_fname[30];
char db_name[30];
char out_folder[30]="gen_code/";

int main(int argc, char** argv) {

	printf("Input File ==> %s\n",argv[1]);
	printf("Output File ==> %s\n",argv[2]);

	strcpy(in_fname,argv[1]);
	strcpy(db_name,argv[2]);

	parse_sql();
	generate_code();

}
