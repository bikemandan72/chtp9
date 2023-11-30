/*
13.7 (Quicksort)
Algorithm from Sedgewick's "Algorithms in C"
Pivot is the right element of an array
Improved realization for repeated elements
Slightly different implementation of qsort algorithm from Sedgewick book
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <math.h>

#define SIZE 10
#define MAXVALUE 100
#define RADIX 10
#define TOLEFT -1
#define TORIGHT 1

struct indices {
	int left;
	int right;
};
typedef struct indices Indices;

void printArray(int *array, size_t fromIndex, size_t toIndex, ...);
void quicksort(int *array, int leftIndex, int rightIndex);
Indices partition(int *array, int fromIndex, int toIndex);
int inArray(int *array, int number);
int checkArray(int *array);

int main (int argc, char *argv[])
{
	//int array[SIZE] = {39, 51, 39, 99, 26, 41, 91, 56, 37, 39};
	
	//generate array of unique elements
	int array[SIZE] = {0};
	int seed = time(NULL);//1700834141;//time(NULL);
	printf("seed = %d\n", seed);
	srand(seed);
	//int number = 0;
	for (size_t i = 0; i < SIZE; ++i) {
		//to garantie 2 or 3 digit values we use this trick
		
		//do {
			//number = rand() % (MAXVALUE - MAXVALUE / RADIX) + MAXVALUE / RADIX;
		//} while (inArray(array, number));
		//array[i] = number;
		
		array[i] = rand() % (MAXVALUE - MAXVALUE / RADIX) + MAXVALUE / RADIX;
	}
	
	//print unsorted array
	puts("Unsorted array:");
	printArray(array, 0, SIZE - 1);

	//sort it
	quicksort(array, 0, SIZE - 1);

	//print sorted array
	puts("Sorted array:");
	printArray(array, 0, SIZE - 1);
	printf("Array %s been sorted.\n", (checkArray(array) ? "has" : "has NOT"));
	return 0;
}
void quicksort(int *array, int leftIndex, int rightIndex) {
	if (rightIndex > leftIndex) {
		printf("leftIndex = %d, rightIndex = %d\n", leftIndex, rightIndex);
		Indices bounds = partition(array, leftIndex, rightIndex);
		//printf("\nindex from quicksort = %d, element = %d\n", index, array[index]);
		printArray(array, leftIndex, rightIndex, bounds.left, bounds.right);
		quicksort(array, leftIndex, bounds.left);
		quicksort(array, bounds.right, rightIndex);
	}
}
Indices partition(int *array, int leftIndex, int rightIndex) {
	int left = leftIndex - 1, right = rightIndex;
	int leftEqual = leftIndex, rightEqual = rightIndex - 1;
	int index = rightIndex;
	printf("\npivot index = %d, element = %d\n", index, array[index]);
	int pivot = array[index];
	while (1) {
		do {//go to the right
			left++;
		} while (array[left] < pivot);//till we found an item greater than the pivot
		printf("array[%d] = %d, ", left, array[left]);
		do {//go to the left
			right--;
			//check to avoid out-of-bounds if pivot is the smallest element
			if (right == leftIndex) {
				//break;
			}
		} while (array[right] > pivot);//till we found an item less than the pivot
		printf("array[%d] = %d\n", right, array[right]);
		if (left >= right) {
			//indices crossed - break the cycle
			break;
		}
		//swap the elements
		int temp = array[right];
		array[right] = array[left];
		array[left] = temp;
		printArray(array, 0, SIZE - 1, left, right);
		if (array[left] == pivot) {
			int temp = array[leftEqual];
			array[leftEqual] = array[left];
			array[left] = temp;
			leftEqual++;
			puts("Saved equals of left:");
			printArray(array, 0, SIZE - 1, left, leftEqual - 1);
		}
		if (array[right] == pivot) {
			int temp = array[rightEqual];
			array[rightEqual] = array[right];
			array[right] = temp;
			rightEqual--;
			puts("Saved equals of right:");
			printArray(array, 0, SIZE - 1, right, rightEqual + 1);
		}
	}
	//put the last element in its correct position
	//down here is left because it point to the element greater than the pivot
	int temp = array[left];
	array[left] = array[rightIndex];
	array[rightIndex] = temp;
	printf("left = %d, leftEqual = %d, rightEqual = %d\n", left, leftEqual, rightEqual);
	Indices bounds = {.left = left - 1, .right = left + 1};
	//put left equals to theirs positions
	for (size_t i = leftIndex; i < leftEqual; ++i) {
		int temp = array[bounds.left];
		array[bounds.left] = array[i];
		array[i] = temp;
		bounds.left--;
	}
	//put right equals to theirs positions
	for (size_t i = rightEqual + 1; i <= rightIndex - 1; ++i) {
		int temp = array[bounds.right];
		array[bounds.right] = array[i];
		array[i] = temp;
		bounds.right++;
	}
	
	puts("After partition:");
	printArray(array, 0, SIZE - 1, bounds.left, bounds.right);
	
	return bounds;
}
int inArray(int *array, int number) {
	int result = 0;
	for (size_t i = 0; i < SIZE; ++i) {
		if (array[i] == number) {
			result = 1;
			break;
		}
	}
	return result;
}
void printArray(int *array, size_t fromIndex, size_t toIndex, ...) {
	va_list ap;
	va_start(ap, toIndex);
	int mark = va_arg(ap, int);
	for (size_t i = 0; i < SIZE; ++i) {
		if (i >= fromIndex && i <= toIndex) {
			if (mark == i) {
				printf("%d* ", array[i]);
				mark = va_arg(ap, int);
			} else {
				printf("%d ", array[i]);
			}
		} else {
			printf("%s ", "  ");
		}
	}
	va_end(ap);
	puts("");
}
int checkArray(int *array) {
	int check = 1;
	for (size_t i = 0; i < SIZE - 1; ++i) {
		if (array[i] > array[i + 1]) {
			check = 0;
			break;
		}
	}
	return check;
}