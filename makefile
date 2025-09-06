# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Files
SRC = mytest.cpp course.cpp
OBJ = $(SRC:.cpp=.o)
HEADER = course.h
EXEC = program

# Default target
all: $(EXEC)

# Compile the executable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

# Compile .cpp files into .o files
%.o: %.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(EXEC)
	./$(EXEC)

# Run with Valgrind for memory leak check
valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./$(EXEC)

# Clean up build files
clean:
	rm -f $(OBJ) $(EXEC)