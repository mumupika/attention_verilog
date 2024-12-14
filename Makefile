CC = g++
OBJ = ./build
SRC = ./src
CFLAGS = -std=c++17 -Wall -g

all: main
main: $(OBJ)/matrix_multiply.o $(OBJ)/data_generator.o $(OBJ)/softmax.o $(OBJ)/matrix_output.o $(OBJ)/fix_convert.o $(OBJ)/vector_ops.o $(OBJ)/test.o
	$(CC) $(CFLAGS) $^ -o main

$(OBJ)/fix_convert.o: $(SRC)/fix_convert.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/test.o: test.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/vector_ops.o: $(SRC)/vector_ops.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/matrix_output.o: $(SRC)/matrix_output.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/matrix_multiply.o: $(SRC)/matrix_multiply.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/softmax.o: $(SRC)/softmax.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/data_generator.o: $(SRC)/data_generator.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: all clean
clean: 
	rm -rf ./build/*