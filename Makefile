object = *.o
header = *.h
FF = -I/usr/lib/llvm-3.4/include -DNDEBUG -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS

all: compile
	g++ $(object) -lfl $(FF) `llvm-config --libs core ` `llvm-config --ldflags` -lpthread
compile :
	g++ -c y.tab.c -lfl $(FF)
	g++ -c lex.yy.c -lfl
	g++ -c *.cpp $(FF)
	g++ -c *.c $(FF)

