all: dirinfo.o
	gcc -o dirinfo dirinfo.o

dirinfo.o: dirinfo.c
	gcc -c dirinfo.c

clean:
	rm dirinfo_debug dirinfo *.o

run:
	./dirinfo $(args)

bug: 
	gcc -g -c dirinfo.c
	gcc -o dirinfo_debug dirinfo.o

debug:
	gdb ./dirinfo_debug
