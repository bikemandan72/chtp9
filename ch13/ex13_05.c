/*
13.5 (Recursive Selection Sort)
A selection sort searches an array looking for the array’s smallest element. When that
element is found, it’s swapped with the first element of the array. The process is then
repeated for the subarray, beginning with the second element. Each pass of the array
results in one element being placed in its proper location. This sort requires
processing capabilities similar to bubble sort—for an array of n elements, n – 1 passes
must be made, and for each subarray, n – 1 comparisons must be made to find the
smallest value. When the subarray being processed contains one element, the array is
sorted. Write a recursive function selectionSort to perform this algorithm.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void printArray(int *array, size_t fromIndex, size_t toIndex);
void selectionSort(int *array, size_t fromIndex, size_t toIndex);
void printPass(int array[], size_t length, int pass, size_t index);

int main (int argc, char *argv[])
{
	//generate array
	int array[SIZE] = {0};
	srand(time(NULL));
	for (size_t i = 0; i < SIZE; ++i) {
		array[i] = rand() % 90 + 10;
	}
	//print unsorted array
	puts("Unsorted array:");
	printArray(array, 0, SIZE - 1);
	//sort it
	selectionSort(array, 0, SIZE - 1);
	//print sorted array
	puts("Sorted array:");
	printArray(array, 0, SIZE - 1);
	
	return 0;
}
void selectionSort(int *array, size_t fromIndex, size_t toIndex) {
	if (fromIndex < toIndex) {
		int smallest = fromIndex;
		for (size_t i = fromIndex + 1; i <= toIndex; ++i) {
			if (array[i] < array[smallest]) {
				smallest = i;
			}
		}
		printPass(array, SIZE, fromIndex + 1, smallest); // output pass 
		int temp = array[fromIndex];
		array[fromIndex] = array[smallest];
		array[smallest] = temp;
		selectionSort(array, fromIndex + 1, toIndex);
	}
}
void printArray(int *array, size_t fromIndex, size_t toIndex) {
	for (size_t i = fromIndex; i <= toIndex; ++i) {
		printf("%d ", array[i]);
	}
	puts("");
}
// function that prints a pass of the algorithm 
void printPass(int array[], size_t length, int pass, size_t index) {
	printf("After pass %2d: ", pass);
	
	// output elements till selected item 
	for (size_t i = 0; i < index; i++) {
		printf("%d  ", array[i]);
	}
	
	printf("%d* ", array[index]); // indicate swap 
	
	// finish outputting array 
	for (size_t i = index + 1; i < length; i++) {
		printf("%d  ", array[i]);
	}
	
	printf("%s", "\n               "); // for alignment 
	
	// indicate amount of array that is sorted 
	for (int i = 0; i < pass; i++) {
		printf("%s", "--  ");
	}
	
	puts(""); // add newline 
}