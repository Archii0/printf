ALL=printf

all: ${ALL}
clean:
	rm -f ${ALL} *.o

printf.o:
	gcc -c printf.c
printf: printf.o
	gcc -O0 printf.o -o printf