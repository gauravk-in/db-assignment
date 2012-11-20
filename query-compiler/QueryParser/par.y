%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "include/query.h"

#include <vector>

using namespace std;

extern int yylex();
extern void yyerror(string msg);
extern int yyparse();
extern FILE *yyin;

select_query new_select_query;

char* select_q(char* output, char* table_list)
{
	char ret[200];
	sprintf(ret, "select %s from %s\n", output, table_list);
	printf("%s\n", ret);
	return ret;
}

char* select_cond_q(char* output, char* table_list, char* cond_list)
{
	char ret[200];
	sprintf(ret, "select %s from %s where %s\n", output, table_list, cond_list);
	return ret;
}

void push_field_name(char* field_name)
{
	proj_field field_temp;
	strcpy(field_temp.name, field_name);
	strcpy(field_temp.table_name, "");
	new_select_query.field_list.push_back(field_temp);
}

void print_field_list()
{
	vector<proj_field>::iterator field_iter;
	printf("List of fields\n");
	for(field_iter = new_select_query.field_list.begin(); field_iter < new_select_query.field_list.end(); field_iter++)
		printf("\tfield name : %s\n", field_iter->name);
	return;
}

char* sum(char* expression)
{
	char ret[200];
	sprintf(ret, "sum(%s)\n", expression);
	printf("%s\n", ret);
	return ret;
}

char* prod(char* expression)
{
	char ret[200];
	sprintf(ret, "prod(%s)\n", expression);
	return ret;
}

char expr_str[200];

char* addition(char* expr, char* expression)
{
	strcat(expr_str, expr);
	strcat(expr_str, " + ");
	return expr_str;	
}

char* mul(char* expr, char* expression)
{
	strcat(expr_str, expr);
	strcat(expr_str, " * ");
	return expr_str;	
}

char* divide(char* expr, char* expression)
{
	strcat(expr_str, expr);
	strcat(expr_str, " / ");
	return expr_str;	
}

char* subtraction(char* expr, char* expression)
{
	strcat(expr_str, expr);
	strcat(expr_str, " / ");
	return expr_str;	
}

char* number(int num)
{
	char ret[100];
	int i=0;
	sprintf(ret, "%d", num);
	//itoa(num, ret, 10);
	return ret;
}

char table_list_str[200];

char* table_list(char* table_name, char* table_list)
{
	strcat(table_list_str, table_name);
	strcat(table_list_str, ", ");
	return table_list_str;
}

char cond_list_str[200];

char* cond_list(char* cond_name, char* cond_list)
{
	strcat(cond_list_str, cond_name);
	strcat(cond_list_str, " and ");
	return cond_list_str;
}

char* eq(char* loperand, char* roperand)
{
	char ret[50]="";
	strcat(ret, loperand);
	strcat(ret, " = ");
	strcat(ret, roperand);
	return ret;
}

char* not_equal(char* loperand, char* roperand)
{
	char ret[50]="";
	strcat(ret, loperand);
	strcat(ret, " != ");
	strcat(ret, roperand);
	return ret;
}

char* gt(char* loperand, char* roperand)
{
	char ret[50]="";
	strcat(ret, loperand);
	strcat(ret, " > ");
	strcat(ret, roperand);
	return ret;
}

char* lt(char* loperand, char* roperand)
{
	char ret[50]="";
	strcat(ret, loperand);
	strcat(ret, " < ");
	strcat(ret, roperand);
	return ret;
}

char* gte(char* loperand, char* roperand)
{
	char ret[50]="";
	strcat(ret, loperand);
	strcat(ret, " >= ");
	strcat(ret, roperand);
	return ret;
}

char* lte(char* loperand, char* roperand)
{
	char ret[50]="";
	strcat(ret, loperand);
	strcat(ret, " <= ");
	strcat(ret, roperand);
	return ret;
}

%}

%union {
	char* str;
	int ival;
};

%start queries

%token SELECT
%token INSERT
%token FROM
%token WHERE
%token SUM
%token PROD
%token COMMA
%token AND
%token<str> STRNG
%token<ival> NUMBER
%token PLUS
%token MINUS
%token MUL
%token DIV
%token EQ
%token GT
%token LT
%token GTE
%token LTE
%token NOT_EQ
%token LPAREN
%token RPAREN
%token DBL_QT
%token SNGL_QT
%token SEMICOLON

%type <str> query select_q output field_list field_name arithmetic_exp expression expr table_list table_name cond_list condition

%%

queries:
query |
query queries
;

query:
select_q { $$ = $1; printf("%s\n", $$); }

select_q:
SELECT output FROM table_list SEMICOLON { printf("Query Complete\n"); } |
SELECT output FROM table_list WHERE cond_list SEMICOLON { select_cond_q($2, $4, $6); }

output:
field_list { printf("Output done\n"); print_field_list(); } |
arithmetic_exp { $$ = $1; printf("%s\n", $$); }

field_list:
field_name {  }|
field_name COMMA field_list {  }

field_name:
STRNG { $$ = $1; push_field_name($1); }

arithmetic_exp:
SUM LPAREN expression RPAREN { $$ = sum($3); } | 
PROD LPAREN expression RPAREN { $$ = prod($3); }

expression:
expr { $$ = $1; printf("%s\n", $$); }|
expr PLUS expression  { $$ = addition($1, $3); } |
expr MINUS expression  { $$ = subtraction($1, $3); } |
expr MUL expression  { $$ = mul($1, $3); } |
expr DIV expression  { $$ = divide($1, $3); }

expr:
STRNG { $$ = $1; printf("%s\n", $$); } |
NUMBER { $$ = number($1); }

table_list:
table_name { $$ = $1; printf("%s\n", $$); }|
table_name COMMA table_list { $$ = table_list($1, $3); }

table_name:
STRNG { $$ = $1; printf("%s\n", $$); } |
DBL_QT STRNG DBL_QT { $$ = $2; }

cond_list:
condition { $$ = $1; printf("%s\n", $$); } |
condition AND cond_list { $$ = cond_list($1, $3); }

condition:
STRNG EQ STRNG  { $$ = eq($1, $3); } |
STRNG GT STRNG  { $$ = gt($1, $3); } |
STRNG LT STRNG  { $$ = lt($1, $3); } |
STRNG GTE STRNG  { $$ = gte($1, $3); } |
STRNG LTE STRNG  { $$ = lte($1, $3); } |
STRNG NOT_EQ STRNG  { $$ = not_equal($1, $3); }

%%

void yyerror(string msg)
{
	cout << "ERROR" << msg << endl;
}

int yywrap()
{
	return 1;
}

main()
{
	yyparse();
}


