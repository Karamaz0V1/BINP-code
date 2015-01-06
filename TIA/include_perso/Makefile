all:
	gcc -c *.c && ar cr libtia_utils.a *.o

install:
	mkdir ../lib_perso ; mv libtia_utils.a ../lib_perso

clean:
	rm *.a *.o
