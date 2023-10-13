
squeeze: squeeze.c
	gcc -S -masm=intel squeeze.c
	gcc -g -o squeeze -masm=intel squeeze.c

bubble: bubble.c
	gcc -S -masm=intel bubble.c
	gcc -g -o bubble -masm=intel bubble.c
	
clean:
	rm -fr bubble squeeze *.s *.o
	