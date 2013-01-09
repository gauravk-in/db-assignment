CC=g++
CCFLAGS=-std=c++11 -O3

SOURCE=hash_trial.cpp
INCLUDE=hash_map.h

hash_trial: $(SOURCE) $(INCLUDE)
	$(CC) $(CCFLAGS) -o $@ $^

clean:
	rm -rf *.o hash_trial
