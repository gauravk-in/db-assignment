CC=g++
CCFLAGS=-O0  -fno-stack-protector -std=c++11 

SOURCES=main.cpp data_migrate.cpp schema_methods.cpp transactions.cpp oltp.cpp schema_constructors.cpp storage.cpp query.cpp
INCLUDE=include/data_migrate.h  include/main.h  include/transactions.h  include/oltp.h include/schema.h include/query.h

fakedb: $(SOURCES) $(INCLUDE)
	$(CC) $(CCFLAGS) $^ -o $@

parser: 
	yacc -d par.y
	lex lex.l
	$(CC) lex.yy.c y.tab.c -o $@ -lfl

parser_clean:
	rm -rf lex.yy.c y.tab.c parser

clean:
	rm -rf fakedb

run: clean fakedb
	./fakedb


