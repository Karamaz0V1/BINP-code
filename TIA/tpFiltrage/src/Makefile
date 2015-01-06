FLAGS=-g -Wall `libit-config --cflags`
LIBS=`libit-config --libs` -lm # -lefence
#CC=gcc
CC=clang

EXE=tp_filtrage

all: $(EXE)

$(EXE): $(EXE).c
	$(CC) $(FLAGS) -o $(EXE) $(EXE).c $(LIBS)

exe:
	./$(EXE)

clean:
	rm tp_filtrage *.pgm
