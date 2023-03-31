#!/usr/bin/python3

# Quicksort Algorithm courtesy of: https://www.geeksforgeeks.org/python-program-for-quicksort/
# And, of course, Donald Knuth

# Python program for implementation of Quicksort Sort
 
# This implementation utilizes pivot as the last element in the nums list
# It has a pointer to keep track of the elements smaller than the pivot
# At the very end of partition() function, the pointer is swapped with the pivot
# to come up with a "sorted" nums relative to the pivot

import time
import random
import sys

 
# Function to find the partition position
def partition(array, low, high):
 
    # choose the rightmost element as pivot
    pivot = array[high]
 
    # pointer for greater element
    i = low - 1
 
    # traverse through all elements
    # compare each element with pivot
    for j in range(low, high):
        if array[j] <= pivot:
 
            # If element smaller than pivot is found
            # swap it with the greater element pointed by i
            i = i + 1
 
            # Swapping element at i with element at j
            (array[i], array[j]) = (array[j], array[i])
 
    # Swap the pivot element with the greater element specified by i
    (array[i + 1], array[high]) = (array[high], array[i + 1])
 
    # Return the position from where partition is done
    return i + 1
 
# function to perform quicksort
 
 
def quickSort(array, low, high):
    if low < high:
 
        # Find pivot element such that
        # element smaller than pivot are on the left
        # element greater than pivot are on the right
        pi = partition(array, low, high)
 
        # Recursive call on the left of pivot
        quickSort(array, low, pi - 1)
 
        # Recursive call on the right of pivot
        quickSort(array, pi + 1, high)
 


def doRun( n ):
	randomlist = []
	for i in range(0, n):
		randomlist.append( random.randint(0, sys.maxsize) )

	# print(randomlist)

	size = len(randomlist)

	start_time = time.time()

	quickSort(randomlist, 0, size - 1)

	print("%d: --- %s seconds ---" % (n, time.time() - start_time))



print( "Quicksort" )	

for n in (2**p for p in range(1, 30)):
	doRun( n )
