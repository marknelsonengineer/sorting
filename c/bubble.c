#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>


void bubbleSortAsm( uint64_t arr[], uint64_t n ) {

   // Assumes dwSomeValue is not zero.
   asm (
      "mov r9, %1 \n\t"   // Outer counter
      "dec r9     \n\t"
      "outerLoop:  \n\t"
      
//   	"mov rcx, %1 \n\t"  // Inner counter
//   	"mov rdx, %0 \n\t"  // Inner current
//   	"mov rax, [rdx]  \n\t"
//   	"add rdx, 8 \n\t"        // Increment current
   	
//   	"innerLoop: \n\t"
//   	"mov rdi, [rdx] \n\t"
//   	"cmp rax, rdi \n\t"
//   	"jz  sorted   \n\t"
//   	"xchg rax, rdi  \n\t"
//   	"sorted:        \n\t"
//   	"mov rax, rdi \n\t"
//   	"dec  rcx \n\t"
 //  	"jnz  innerLoop  \n\t"
   	
   	"dec r9        \n\t"
   	"jnz outerLoop \n\t"
   	
     :                       /* Output   */
     : "r" (arr), "r" (n)    /* Input    */
     : );                    /* Clobbers */

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

//@todo alignment

void doRun( size_t n ) {
	unsigned long* randomList = (unsigned long*) calloc( n, sizeof( uint64_t ) );
	
	struct timespec tstart={0,0}, tend={0,0};
	
	
	for( size_t i = 0 ; i < n ; i++ ) {
		randomList[i] = (((uint64_t)rand())<<32) + ((uint64_t)rand()) ;
		// printf( "%lu\n", randomList[i]) ;
	}
	
	clock_gettime(CLOCK_MONOTONIC, &tstart);
	// bubbleSortAsm( randomList, n ) ;
	bubbleSort( randomList, n ) ;
	clock_gettime(CLOCK_MONOTONIC, &tend);
	
	printf("%zu: bubbleSort took about %.5f seconds\n", n, 
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - 
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
	
	free( randomList ) ; 
}


int main() {
	printf( "Bubble Sort\n" ) ;
	
	for( size_t i = 0 ; i < 30 ; i++ ) {
		doRun( 1<<i ) ;	
	}
}
