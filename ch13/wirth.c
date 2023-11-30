/*
13.7 (Quicksort)
Implementation from the niklaus Wirth Algorithms and Data Structures
Pivot is random, no Dutch flag improvement, but less comparisons than Sedgewick
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
		//if (leftIndex < bounds.right) {
			quicksort(array, leftIndex, bounds.right);
		//}
		//if (bounds.left < rightIndex) {
			quicksort(array, bounds.left, rightIndex);
		//}
	}
}
Indices partition(int *array, int leftIndex, int rightIndex) {
	int left = leftIndex - 1, right = rightIndex + 1;
	int index = leftIndex + rand() % (rightIndex - leftIndex);
	printf("\npivot index = %d, element = %d\n", index, array[index]);
	int pivot = array[index];
	while (1) {
		do {//go to the right
			left++;
		} while (array[left] < pivot);//till we found an item greater than the pivot
		printf("array[%d] = %d, ", left, array[left]);
		do {//go to the left
			right--;
		} while (array[right] > pivot);//till we found an item less than the pivot
		printf("array[%d] = %d\n", right, array[right]);
		if (left > right) {
			//indices crossed - break the cycle
			break;
		}
		//swap the elements
		int temp = array[right];
		array[right] = array[left];
		array[left] = temp;
		printArray(array, 0, SIZE - 1, left, right);
	}
	puts("After partition:");
	printArray(array, 0, SIZE - 1, left, right);
	Indices bounds = {.left = left, .right = right};
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