# compliler
CC = gcc

#folders
BIN=./bin/

PROG_NAME=par_khan

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -fopenmp

# the build target executable:
TARGET = par_khan
LIST = $(addprefix $(BIN)/, $(TARGET))

all: $(PROG_NAME)

$(PROG_NAME): $(TARGET).c
	$(CC) $(CFLAGS) -o $(LIST) $(TARGET).c      

clean:    
	$(RM) $(LIST)
