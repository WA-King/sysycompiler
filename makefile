main: scan.o parser.o AST.o main.o symbol.o global.o TAC.o gen.o
	g++ -o main scan.o main.o AST.o parser.o symbol.o global.o TAC.o gen.o
scan.o: scan.cpp scan.h global.h
	g++ -c scan.cpp
main.o: scan.h main.cpp  global.h
	g++ -c main.cpp
AST.o: AST.h AST.cpp global.h
	g++ -c AST.cpp
symbol.o: AST.h global.h symbol.cpp symbol.h
	g++ -c symbol.cpp
parser.o: parser.h parser.cpp global.h
	g++ -c parser.cpp
global.o: global.h global.cpp
	g++ -c global.cpp
TAC.o : TAC.h TAC.cpp
	g++ -c TAC.cpp
gen.o : TAC.h gen.h gen.cpp
	g++ -c gen.cpp
