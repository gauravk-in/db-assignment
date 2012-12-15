CC=g++
CCFLAGS=-O0

SOURCES=main.cpp query_code.cpp exp_tree.cpp 
HEADERS=include/query_code.h include/exp_tree.h

run_load: query_compiler
	./query_compiler
	cp gen_query_code.cpp ../fakedb

query_compiler: $(SOURCES) $(HEADERS)
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	rm -rf query_compiler