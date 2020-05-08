# compliler
CC = gcc

#folders
BIN=./bin

PROG_NAME=par_khan

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -fopenmp -O3

# the build target executable:
TARGET = par_khan
LIST = $(addprefix $(BIN)/, $(TARGET))

all: $(PROG_NAME) kahn

$(PROG_NAME): $(TARGET).c
	$(CC) $(CFLAGS) -o $(LIST) $(TARGET).c

kahn: khan.c
	$(CC) $(CFLAGS) -o ./bin/khan khan.c    

clean:    
	$(RM) $(LIST)
