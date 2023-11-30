/*
13.7 (Quicksort)
Lomuto partition - pivot is the right element of an array
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

void printArray(int *array, size_t fromIndex, size_t toIndex, ...);
void quicksort(int *array, int leftIndex, int rightIndex);
int partition(int *array, int fromIndex, int toIndex);
int inArray(int *array, int number);
int checkArray(int *array);

int main (int argc, char *argv[])
{
	
	//generate array of unique elements
	int array[SIZE] = {0};
	int seed = time(NULL);//1700834141;//time(NULL);
	printf("seed = %d\n", seed);
	srand(seed);
	//int number = 0;
	for (size_t i = 0; i < SIZE; ++i) {
		//to garantie 2 or 3 digit values we use this trick
		/*
		do {
			number = rand() % (MAXVALUE - MAXVALUE / RADIX) + MAXVALUE / RADIX;
		} while (inArray(array, number));
		array[i] = number;
		*/
		array[i] = rand() % (MAXVALUE - MAXVALUE / RADIX) + MAXVALUE / RADIX;
	}

	//print unsorted array
	puts("Unsorted array:");
	printArray(array, 0, SIZE - 1);

	//sort it
	quicksort(array, 0, SIZE - 1);
	/*
	int index = partition(array, SIZE - 1, 0, TOLEFT);
	printf("index from partition = %d, element = %d\n", index, array[index]);
	*/
	//print sorted array
	puts("Sorted array:");
	printArray(array, 0, SIZE - 1);
	printf("Array %s been sorted.\n", (checkArray(array) ? "has" : "has NOT"));
	return 0;
}
void quicksort(int *array, int leftIndex, int rightIndex) {
	if (rightIndex > leftIndex) {
		printf("leftIndex = %d, rightIndex = %d\n", leftIndex, rightIndex);
		int index = partition(array, leftIndex, rightIndex);
		printf("\nindex from quicksort = %d, element = %d\n", index, array[index]);
		printArray(array, leftIndex, rightIndex, index);
		quicksort(array, leftIndex, index - 1);
		quicksort(array, index + 1, rightIndex);
	}
}
int partition(int *array, int leftIndex, int rightIndex) {
	//everything to the right of this index is greateg than pivot
	int tempPivot = leftIndex;
	int pivot = array[rightIndex];
	printf("\npivot array[%d] = %d\n", rightIndex, pivot);
	for (size_t i = leftIndex; i < rightIndex; ++i) {
		if (array[i] < pivot) {
			printf("array[%d] = %d <= ", i, array[i]);
			printf("array[%d] = %d\n", tempPivot, array[tempPivot]);
			
			//swap the current and the temporary pivot index
			int temp = array[i];
			array[i] = array[tempPivot];
			array[tempPivot] = temp;

			printArray(array, 0, SIZE - 1, tempPivot, i);

			//increment the appropriate index
			tempPivot++;
		}
	}
	//move pivot to the right position
	int temp = array[tempPivot];
	array[tempPivot] = pivot;
	array[rightIndex] = temp;
	
	puts("After partition:");
	printArray(array, 0, SIZE - 1, tempPivot);
	
	return tempPivot;
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