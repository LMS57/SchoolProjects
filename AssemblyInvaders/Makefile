NAME=space

all: space

clean:
	rm -rf space space.o

space: space.asm
	nasm -f elf -F dwarf -g space.asm
	gcc -g -m32 -o ./driver.c
