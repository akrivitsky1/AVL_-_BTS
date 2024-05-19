CC=g++
DEV=-Wall -g -std=c++14
OPT=-O3 -std=c++14

.PHONY: all
all: BSTSanityCheck CreateData AVLCommands

CreateData: CreateData.cxx json.hpp
	$(CC) $(OPT) CreateData.cxx -o CreateData.exe

BSTSanityCheck: BSTSanityCheck.cxx BST.o
	$(CC) $(DEV) BSTSanityCheck.cxx BST.o -o BSTSanityCheck.exe

AVLCommands: AVL.o AVLCommands.o
	$(CC) $(DEV) AVL.o AVLCommands.o -o AVLCommands.exe

AVLCommands.o: AVLCommands.cxx AVL.h
	$(CC) $(DEV) -c AVLCommands.cxx

AVL.o: AVL.cpp AVL.h
	$(CC) $(DEV) -c AVL.cpp

BST.o: BST.cpp BST.h
	$(CC) $(DEV) -c BST.cpp

# Build
.PHONY: clean
clean:
	rm -f *.o
	rm -f *.exe
	rm -rf *dSYM

.PHONY: update
update:
	make clean
	make all