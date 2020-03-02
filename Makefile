SRC = Benchmark.cpp TreeMap.cpp main.cpp
main: $(SRC)
	g++ -o main -std=c++14 $(SRC) -Wall -pedantic
