all: dirinfo.o
	gcc -o dirinfo dirinfo.o

dirinfo.o: dirinfo.c
	gcc -c dirinfo.c

clean:
	rm dirinfo *.o

run:
	./dirinfo
