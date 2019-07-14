# Name of the program
PROGRAM = CS216PA2

#Headers to include in compilation
HEADERS = main.cpp functions.cpp imdb.cpp

# Name of the object files
OBJECTS = main.o functions.o imdb.o

# Compiles the normal program 
$(PROGRAM): $(OBJECTS) 
	g++ -std=c++11 -o $@ $^
%.o: %.cpp $(HEADERS)
	g++ -std=c++11 -c $< -o $@

# Removes all the object files as well as the program and test program
clean:
	rm -i *.o $(PROGRAM) 
