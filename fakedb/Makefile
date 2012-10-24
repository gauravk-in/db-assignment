CC=g++
CCFLAGS=-O0

fakedb: main.cpp data_migrate.cpp schema_methods.cpp neworder.cpp oltp.cpp schema_constructors.cpp data_migrate.h schema.h oltp.h neworder.h
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	rm -rf fakedb