test: 
	clang++ -std=c++17 -c main.cpp

	clang++ -std=c++17 main.o  -o main
	./main