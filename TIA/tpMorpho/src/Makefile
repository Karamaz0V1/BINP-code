FLAGS=-g -Wall `libit-config --cflags`
LIBS=`libit-config --libs` -lm # -lefence
CC=gcc

EXE=tp_morpho
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(LIBS)
	
%.o: %.c
	$(CC) $(FLAGS) -c $(SRC)

exe:
	./$(EXE)
	
clean:
	rm -rf $(EXE) *.o
	


