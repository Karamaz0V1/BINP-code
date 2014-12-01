CC      =       g++
OPTIONS  = -O2 -c -g -static

SOURCES = .
INC = .

#######	Build rules

all : tache

tache	: module-fft.o fft-a-prog.o main-fft.o imagesRW.o
	$(CC) -g  -o main-fft \
	module-fft.o fft-a-prog.o \
	main-fft.o imagesRW.o 
	\rm *.o

main-fft.o	: $(SOURCES)/main-fft.cpp
	$(CC) $(OPTIONS) -I $(INC) $(SOURCES)/main-fft.cpp

module-fft.o	: $(SOURCES)/module-fft.cpp
	$(CC) $(OPTIONS) -I $(INC) $(SOURCES)/module-fft.cpp

fft-a-prog.o	: $(SOURCES)/fft-a-prog.cpp
	$(CC) $(OPTIONS) -I $(INC) $(SOURCES)/fft-a-prog.cpp

imagesRW.o	: $(SOURCES)/imagesRW.cpp
	$(CC) $(OPTIONS) -I $(INC) $(SOURCES)/imagesRW.cpp
