all: .o dirinfo.o
	gcc -o dirinfo dirinfo.o

dirinfo.o: dirinfo.c dirinfo.h
	gcc -c dirinfo.c

clean:
	rm dirinfo *.o
