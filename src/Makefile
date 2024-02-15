run: main
	./execute

main: compile
	g++ main.o Account.o AccountTree.o pwManager.o FileParser.o -o execute

compile: pwManager.h FileParser.h AccountTree.h Account.h
	g++ -c main.cpp pwManager.cpp FileParser.cpp AccountTree.cpp Account.cpp

cl:
	rm *.o execute
