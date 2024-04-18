#######################
# QUAN NGUYEN         #
# cssc4550            #
# CS530, Spring 2024  # 
# Assignment 2        #
# makefile            #
#######################


EXEC = assemble 
FILES = tables.cpp utility.cpp Pass1.cpp main.cpp 
CC = g++ -std=c++11 
LFLAGS = -g
CFLAGS = -g -c

OBJECTS = $(FILES:.c=.o)

$:(EXEC):$(OBJECTS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJECTS)
	rm -f *.o
.c.o:
	$(CC) $(CFLAGS) $<
clean:
	rm -f *.o $(EXEC)
