CC=g++
CCFLAGS=-O0  -fno-stack-protector -std=c++11 

SOURCES=main.cpp data_migrate.cpp schema_methods.cpp neworder.cpp oltp.cpp schema_constructors.cpp
INCLUDE=include/data_migrate.h  include/main.h  include/neworder.h  include/oltp.h include/schema.h

fakedb: $(SOURCES) $(INCLUDE)
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	rm -rf fakedb
