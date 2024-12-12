test: test.cpp
	g++ -std=c++17 -Wall -o test.o -g test.cpp

matrix_multiply: matrix_multiply.cpp
	g++ -std=c++17 -Wall -o matrix_multiply.o -g matrix_multiply.cpp

clean: 
	rm -rf *.o