all: n6

n6: main.o func.o
	gcc -o n6 main.o func.o -m32 -lm -no-pie
main.o: main.c
	gcc -c -o main.o main.c -m32
func.o: func.asm
	nasm -f elf32 -o func.o func.asm
clean:
	rm *.o n6
