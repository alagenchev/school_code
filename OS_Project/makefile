CC = gcc
RELEASE_FLAGS = -O2 -w -std=c99
DEBUG_FLAGS = -g -O0 -std=c99
SOURCES = *.c
HEADERS = *.h 
EXECUTABLE= a.out
all: 
		$(CC) $(RELEASE_FLAGS) $(SOURCES) $(HEADERS) -o $(EXECUTABLE)
debug:
		
			$(CC) $(DEBUG_FLAGS) $(SOURCES) $(HEADERS) -o $(EXECUTABLE)
clean:
		rm -rf $(EXECUTABLE)
test:
		./$(EXECUTABLE)
