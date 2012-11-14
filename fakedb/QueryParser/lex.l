%{
	#include "y.tab.h"
%}

%%

"select"				{ return SELECT; }
"insert"				{ return INSERT; }
"from"					{ return FROM; }
"where"					{ return WHERE; }
"sum"					{ return SUM; }
"prod"					{ return PROD; }
","						{ return COMMA; }
"and"					{ return AND; }
[a-zA-Z_][a-zA-Z_0-9]*	{ 	char res[50];
							strcpy(res, yytext);
							yylval.str = res; 
							return STRNG; 
						}
[0-9]*					{ yylval.ival = atoi(yytext); return NUMBER; }
"+"						{ return PLUS; }
"-"						{ return MINUS; }
"*"						{ return MUL; }
"/"						{ return DIV; }
"="						{ return EQ; }
">"						{ return GT;}
"<"						{ return LT;}
">="					{ return GTE;}
"<="					{ return LTE;}
"!="					{ return NOT_EQ;}
"("						{ return LPAREN; }
")"						{ return RPAREN; }
"\""					{ return DBL_QT; }
"'"						{ return SNGL_QT; }
";"						{ return SEMICOLON; }	

%%

