

bubble: bubble.c
	gcc -S -masm=intel bubble.c
	gcc -g -o bubble -masm=intel bubble.c
	
clean:
	rm -fr bubble *.s *.o
	