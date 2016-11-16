CC = gcc
CXX = g++

C99 = -std=c99
CPP11 = -std=c++11

CFLAGS = -Wall -Wextra -Werror -Wpedantic

.PHONY: clean

.PRECIOUS: %.c %.cpp %.o

%.o : %.c
	$(CC) $(C99) $(CFLAGS) -c $< -o $@ 

%.o : %.cpp
	$(CXX) $(CPP11) $(CFLAGS) -c $< -o $@

%.out : %.o
	$(CXX) $(CPP11) $(CFLAGS) $< -o $@ 

clean:
	@rm *.o *.out