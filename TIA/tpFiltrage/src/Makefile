FLAGS=-g -Wall -O2 `libit-config --cflags` -I/share/esir2/tia/libit/include -L/share/esir2/tia/libit/lib -lit
LIBS=`libit-config --libs` -lm # -lefence
CC=g++

EXE=tp_filtrage

all: $(EXE)

$(EXE): $(EXE).c
	$(CC) $(FLAGS) -o $(EXE) $(EXE).c $(LIBS)

exe:
	./$(EXE)


