# Makefile 
# Hinam Mehra
# May 2015

OBJ     = main.o set.o heap.o graph.o 
CC      = gcc
EXE     = assn2
CFLAGS  = -O2 -Wall -m32

assn2:   $(OBJ) Makefile
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

clean:
	rm -f $(OBJ) $(EXE)

clobber: clean
	rm -f $(EXE)

usage: $(EXE)
	./$(EXE) 

main.o: set.h heap.h graph.h Makefile
set.o: set.h 
heap.o: heap.h
graph.o: set.h heap.h graph.h 
