all: main

main: main.cpp circuit.cpp fault.cpp 
	  g++ -std=c++11  -o ex main.cpp circuit.cpp fault.cpp 