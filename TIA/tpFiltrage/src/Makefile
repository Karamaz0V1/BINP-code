FLAGS=-g -Wall -O2 `libit-config --cflags`
LIBS=`libit-config --libs` -lm # -lefence
CC=gcc

EXE=tp_filtrage

all: $(EXE)

$(EXE): $(EXE).c
	$(CC) $(FLAGS) -o $(EXE) $(EXE).c $(LIBS)

exe:
	./$(EXE)


