#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>


void bubbleSortAsm( uint64_t arr[], uint64_t n ) {
	// Input variables...
	//   arr is in rdi
	//   n is in rsi
	//
	// Register allocation...
	//   rsi = Outer counter
	//   rdi = Inner counter
	//   rcx = Current pointer
	//   rax = Compare 1
	//   rdx = Compare 2
	

   // Assumes dwSomeValue is not zero.
   asm (
      "mov rsi, %1       \n\t"   // Outer counter
      "dec rsi           \n\t"
      "outerLoop:        \n\t"
      
   	"xor rdi, rdi      \n\t"   // Inner counter = 0
      "mov rcx, %0       \n\t"   // Reset current pointer
      "mov rax, [rcx]    \n\t"
      "add rcx, 8        \n\t"
   	
   	"innerLoop:        \n\t"
   	"mov rdx, [rcx]    \n\t"
   	
   	// do the compare
   	
   	"cmp rdx, rax      \n\t"
   	"ja inOrder        \n\t"
   	"xchg rdx, rax     \n\t"
   	"mov  [rcx-8], rax \n\t"
   	"mov  [rcx],   rdx \n\t"
   	
   	"inOrder:          \n\t"

   	"add rcx, 8        \n\t"
   	"mov rax, rdx      \n\t"
   	
   	"inc rdi           \n\t"
   	"cmp rdi, rsi      \n\t"
   	"jb  innerLoop     \n\t"
   	
   	"dec rsi           \n\t"
   	"jnz outerLoop     \n\t"
   	
     :                       /* Output   */
     : "r" (arr), "U" (n)    /* Input    */
     : "cc", "memory", "rsi", "rdi", "rcx", "rax", "rdx" );  /* Clobbers */

}


// Bubble Sort courtesy of https://www.geeksforgeeks.org/bubble-sort/
void bubbleSort(uint64_t arr[], size_t n) {
	for (size_t i = 0; i < n - 1; i++) {
		for (size_t j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				uint64_t temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void printSampleData( uint64_t* randomList, size_t n ) {
	for( size_t i = 0 ; i < 6 ; i++ ) {
		printf( "%4zu: %20p %20lx\n", i, &randomList[i], randomList[i] ) ;
	}

	for( size_t i = n - 6 ; i < n ; i++ ) {
		printf( "%4zu: %20p %20lx\n", i, &randomList[i], randomList[i] ) ;
	}
}


//@todo alignment

void doRun( size_t n ) {
	uint64_t* randomList = (uint64_t*) calloc( n, sizeof( uint64_t ) );
	
	struct timespec tstart={0,0}, tend={0,0};
	
	
	for( size_t i = 0 ; i < n ; i++ ) {
		randomList[i] = (((uint64_t)rand())<<33) + ((uint64_t)rand()) ;
		// printf( "%lu\n", randomList[i]) ;
	}
		
	clock_gettime(CLOCK_MONOTONIC, &tstart);
	bubbleSortAsm( randomList, n ) ;
	// bubbleSort( randomList, n ) ;
	clock_gettime(CLOCK_MONOTONIC, &tend);

	// printSampleData( randomList, n ) ;
	
	printf("%zu: bubbleSort took about %.5f seconds\n", n, 
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - 
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));

	
	
	
	free( randomList ) ; 
}


int main() {
	printf( "Bubble Sort\n" ) ;
	
	for( size_t i = 4 ; i < 30 ; i++ ) {
		doRun( 1<<i ) ;	
	}
}
