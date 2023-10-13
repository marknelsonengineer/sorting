
squeeze: squeeze.c
	export TMPDIR=~/tmp
	gcc -S -masm=intel squeeze.c
	# gcc -g -o squeeze -masm=intel squeeze.c
	gcc -march=native -mtune=native -o squeeze -masm=intel squeeze.c
	#gcc -O3 -march=native -mtune=native -o squeeze -masm=intel squeeze.c

bubble: bubble.c
	gcc -S -masm=intel bubble.c
	gcc -g -o bubble -masm=intel bubble.c

test: squeeze
	./squeeze
	
clean:
	rm -fr bubble squeeze *.s *.o
	
