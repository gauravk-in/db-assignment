CC=g++
CCFLAGS=-fpermissive -std=c++11

SOURCE=main.cpp parse_tree.cpp input_parsetree.cpp
INCLUDE=include/parse_tree.h

compile_query: $(SOURCE) $(INCLUDE)
	$(CC) $(CCFLAGS) $^ -o $@

run: compile_query
	./compile_query
	cp gen_query_code.cpp ../fakedb/

clean:
	rm -rf compile_query *.o