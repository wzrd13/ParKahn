# compliler
CC = gcc

#folders
BIN=./bin

PROG_NAME=par_khan

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -fopenmp -O2

# the build target executable:
TARGET = par_khan
LIST = $(addprefix $(BIN)/, $(TARGET))

all: $(PROG_NAME) khan

$(PROG_NAME): $(TARGET).c
	$(CC) $(CFLAGS) -o $(LIST) $(TARGET).c

khan:
	$(CC) $(CFLAGS) -o $(BIN)/khan khan.c     

clean:    
	$(RM) $(LIST)
