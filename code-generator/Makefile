CC=g++
CCFLAGS=-O0

SOURCES=main.cpp parse_sql.cpp generate_code.cpp db_structs.cpp
HEADERS=include/main.h include/parse_sql.h include/generate_code.h include/db_structs.h

parse_sql: $(SOURCES) $(HEADERS)
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	rm -rf parse_sql

run: clean parse_sql
	mkdir -p gen_code
	./parse_sql schema.sql abc

run_load: clean parse_sql
	mkdir -p gen_code
	./parse_sql schema.sql abc
	./load_to_fakedb.sh
