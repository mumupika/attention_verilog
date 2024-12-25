CC = g++
OBJ = ./build
SRC = ./src
CFLAGS = -std=c++17 -Wall -g
SO = -shared

all: main dist-clean

main: $(OBJ)/test.o $(OBJ)/verilog_input.o $(OBJ)/data_generator.o $(OBJ)/matrix_lib.so $(OBJ)/operations.so
	$(CC) $(CFLAGS) $^ -o main

$(OBJ)/operations.so: $(OBJ)/quantify.o $(OBJ)/softmax.o $(OBJ)/fix_convert.o $(OBJ)/vector_ops.o
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $(SO) $^ -o $@

$(OBJ)/matrix_lib.so: $(OBJ)/matrix_multiply.o $(OBJ)/matrix_output.o $(OBJ)/fix_convert.o \
                      $(OBJ)/vector_ops.o
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $(SO) $^ -o $@

$(OBJ)/fix_convert.o: $(SRC)/fix_convert.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/vector_ops.o: $(SRC)/vector_ops.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/test.o: test.cpp
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

$(OBJ)/quantify.o: $(SRC)/quantify.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/verilog_input.o: $(SRC)/verilog_input.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean dist-clean
clean: 
	rm -rf ./build
dist-clean:
	rm -rf ./build/*.o