
all:	compiler

compiler:
	g++ -o lottery lottery.cpp

clean:
	rm lottery
