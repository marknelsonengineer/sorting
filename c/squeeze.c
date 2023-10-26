///////////////////////////////////////////////////////////////////////////////
//         University of Hawaii, College of Engineering
//         EE 205 - Spr 2023 - Sorting - Squeeze Sort
//
/// Implement a highly optimized O(n^2) sort
///
/// In an analysis of Insertion, Exchange and Selection sorts
///
///  Insertion Sorts generate a lot of writes as every out-of-order element
///                  triggers a ripple of writes to make room in the array
///                  for the new element.
///  Exchange Sorts  like Bubble sort generate a lot of writes because of the
///                  nearly continuous swapping of adjacent elements.
///  Selection Sorts have a lot of comparisons, but an optimal number of writes
///                  As you will only write data once.  That said, selection
///                  sorts are still O(n^2) algorithms.
///
/// @file   squeeze.c
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

#define PROGRAM_NAME "Squeeze Sort"

// Squeeze Sort:  Find the min & max values and swap them, squeezing the
// unsorted data into the middle.
//
// This is intended to be the very best O(n^2) algorithm you can make
//
// It is efficient in writes as it only writes the sorted data once
void squeezeSortAsm( uint64_t arr[], uint64_t n ) {
   // Input variables...
   //   arr is in rdi
   //   n is in rsi
   //
   // Register allocation...
   //   r15 = i_front
   //   r14 = i_back
   //   r13 = max_value
   //   r12 = max_index
   //   r11 = min_value
   //   r10 = min_index
   //   r9 = j
   //   r8 = arr[j]
   asm (
      "mov rdi, %0; "    // rdi = arr

      "xor r15, r15; "   // i_front = 0;
      "mov r14, %1; "    // i_back = n - 1;
      "dec r14;     "

      "outer_loop:; "    // while( i_front < i_back ) {}

      "xor r13, r13; "   // max_value = 0;
      "xor r11, r11; "   // min_value = UINT64_MAX;
      "dec r11; "

      // Find i_max & i_min
                         // for( size_t j = i_front ; j <= i_back ; j++ ) {
      "mov r9, r15; "    // j = i_front;
      "inner_loop:; "

      "mov r8, [rdi + r9*8]; "
      "cmp r8, r13; "    // if( arr[j] > max_value )
      "jna not_max; "    // IMPORTANT:  Be sure to use unsigned Jumps @see http://unixwiz.net/techtips/x86-jumps.html
         "mov r12, r9; " // max_index = j;
         "mov r13, r8; " // max_value = arr[j];
      "not_max:; "

      "cmp r8, r11; "    // if( arr[j] < min_value )
      "jae not_min; "
         "mov r10, r9; " // min_index = j;
         "mov r11, r8; " // min_value = arr[j];
      "not_min:; "

      "inc r9; "         // j++;
      "cmp r9, r14; "    // j <= i_back
      "jle inner_loop; " // for( size_t j = i_front ; j <= i_back ; j++ ) {

      // printf( "i_back=%lu  max_index=%lu  max_value=%016lx  i_front=%lu  min_index=%lu  min_value=%016lx\n", i_back, max_index, max_value, i_front, min_index, min_value );

      "cmp r10, r12; "   // if( min_index == max_index )
      "jz continue_outer_loop; "  // goto LOOP;

      "cmp r10, r15; "   // if( min_index != i_front )
      "jz min_is_already_in_front; "
         // exchangeValues( &arr[min_index], &arr[i_front] );
         "mov rax, [rdi + r10*8]; "
         "mov rbx, [rdi + r15*8]; "
         "mov [rdi + r10*8], rbx; "
         "mov [rdi + r15*8], rax; "
      "min_is_already_in_front:; "

      "cmp r12, r15; "   // if( max_index == i_front )
      "jnz max_is_not_in_front; "
         "mov r12, r10; "// max_index = min_index;
      "max_is_not_in_front:; "

      "cmp r12, r14; "   // if( max_index != i_back )
      "jz max_is_already_in_back; "
         // exchangeValues( &arr[max_index], &arr[i_back] );
         "mov rax, [rdi + r12*8]; "
         "mov rbx, [rdi + r14*8]; "
         "mov [rdi + r12*8], rbx; "
         "mov [rdi + r14*8], rax; "
      "max_is_already_in_back:; "

      "continue_outer_loop:; "

      // Iterate on the outer loop
      "inc r15; "       // i_front++;
      "dec r14; "       // i_back--;
      "cmp r15, r14; "  // while( i_front < i_back ) {}
      "jl outer_loop; "

     :                         /* Output   */
     : "irm" (arr), "irm" (n)  /* Input    */
     : "cc", "memory", "rdi", "rax", "rbx", "rcx", "rdx", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" );  /* Clobbers */
}


/// Efficiently exchange the values pointed to by v1 and v2
static inline void exchangeValues( uint64_t* v1, uint64_t* v2 ) {
   __asm("mov rsi, %0"::"rm" (v1));
   __asm("mov rax, [rsi]");
   __asm("mov rdi, %0"::"rm" (v2));
   __asm("mov rbx, [rdi]");

   __asm("mov [rdi], rax");
   __asm("mov [rsi], rbx");
}


// Squeeze Sort in C
static inline void squeezeSortInC(uint64_t arr[], size_t n) {
   size_t i_front = 0;
   size_t i_back  = n - 1;

   while( i_front < i_back ) {
      // printf( "i_front=%lu  i_back=%lu\n", i_front, i_back );

      uint64_t max_value = 0;
      size_t   max_index;
      uint64_t min_value = UINT64_MAX;
      size_t   min_index;

      // Find i_max & i_min
      for( size_t j = i_front ; j <= i_back ; j++ ) {
         if( arr[j] > max_value ) {
            max_index = j;
            max_value = arr[j];
         }
         if( arr[j] < min_value ) {
            min_index = j;
            min_value = arr[j];
         }
      }

      printf( "i_back=%lu  max_index=%lu  max_value=%016" PRIx64 "  i_front=%lu  min_index=%lu  min_value=%016" PRIx64 "\n", i_back, max_index, max_value, i_front, min_index, min_value );

      if( min_index == max_index ) {
         goto LOOP;
      }
      if( min_index != i_front ) {
         exchangeValues( &arr[min_index], &arr[i_front] );
      }
      if( max_index == i_front ) { // If we swapped an important index...
         max_index = min_index;
      }
      if( max_index != i_back ) {
         exchangeValues( &arr[max_index], &arr[i_back] );
      }

      LOOP:
      i_front++;
      i_back--;
   }
}


/// Print the first 4 and the last 4 unsigned long ints in randomList
///
/// This can be useful for examining the initial random numbers and the
/// sorted list
void printSampleData( uint64_t* randomList, size_t n ) {
   // Print the first 4 samples
   for( size_t i = 0 ; i < 4 ; i++ ) {
      printf( "%4zu: %p %016" PRIx64 "\n", i, &randomList[i], randomList[i] ) ;
   }

   printf( "...\n" );

   // Print the last 4 samples
   for( size_t i = n - 4 ; i < n ; i++ ) {
      printf( "%4zu: %p %016" PRIx64 "\n", i, &randomList[i], randomList[i] ) ;
   }
}


void doRun( size_t n ) {
   uint64_t aRandomValue = 0;
   uint64_t* randomList = (uint64_t*) calloc( n, sizeof( uint64_t ) );

   struct timespec tstart={0,0}, tend={0,0};

   for( size_t i = 0 ; i < n ; i++ ) {
      __asm( "rdrand rax" );
      __asm( "mov %0, rax":"=r" (aRandomValue) );
      randomList[i] = aRandomValue;

      // printf( "%016" PRIx64 "\n", randomList[i] ) ;
   }

   // printSampleData( randomList, n ) ;

   clock_gettime(CLOCK_MONOTONIC, &tstart);
   squeezeSortAsm( randomList, n ) ;
   // squeezeSortInC( randomList, n ) ;
   clock_gettime(CLOCK_MONOTONIC, &tend);

   printf("%zu: squeezeSort took about %.5f seconds\n", n,
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));

   // printSampleData( randomList, n ) ;

   free( randomList ) ;
}


int main() {
   printf( PROGRAM_NAME "\n" ) ;

// doRun( 8 );
// return 0;

   for( size_t i = 4 ; i < 30 ; i++ ) {
      doRun( 1<<i ) ;
   }
}
