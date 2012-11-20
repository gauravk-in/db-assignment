CC=g++
CCFLAGS=-O0 -fno-stack-protector -std=c++11 -fpermissive

SOURCES= data_migrate.cpp schema_methods.cpp transactions.cpp oltp.cpp schema_constructors.cpp storage.cpp query.cpp
INCLUDE=include/data_migrate.h  include/main.h  include/transactions.h  include/oltp.h include/schema.h include/query.h

fakedb_query: main_query.cpp $(SOURCES) $(INCLUDE) gen_query_code.cpp
	$(CC) $(CCFLAGS) $^ -o $@

fakedb: main.cpp $(SOURCES) $(INCLUDE)
	$(CC) $(CCFLAGS) $^ -o $@ -ldl

lib_query: fakedb gen_query_code.cpp storage.cpp
	$(CC) $(CCFLAGS) -c -fPIC gen_query_code.cpp -o gen_query_code.o
	$(CC) $(CCFLAGS) -c -fPIC storage.cpp -o storage.o	
	$(CC) $(CCFLAGS) -shared -Wl,-soname,lib_query.so.1 -o lib_query.so.1.0.1 gen_query_code.o storage.o
	mkdir -p /tmp/lib_query
	mv lib_query.so.1.0.1 /tmp/lib_query/lib_query.so.1.0.1
	ln -sf /tmp/lib_query/lib_query.so.1.0.1 /tmp/lib_query/lib_query.so.1
	ln -sf /tmp/lib_query/lib_query.so.1.0.1 /tmp/lib_query/lib_query.so

clean:
	rm -rf fakedb fakedb_query *.o

run: clean fakedb
	./fakedb


