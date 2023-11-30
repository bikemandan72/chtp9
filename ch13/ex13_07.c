/*
13.7 (Quicksort) We discussed various sorting techniques in the examples and exer-
cises of Chapter 6 and this chapter. We now present the recursive quicksort sorting
technique. The basic algorithm for a one-dimensional array of values is as follows:
a) Partitioning Step: Take the unsorted array’s first element and determine its
final location in the sorted array. That’s the position for which all values to
the element’s left are less than that value, and all values to the element’s right
are greater than that value. We now have one element in its proper location
and two unsorted subarrays.
b) Recursive Step: Perform the partitioning step on each unsorted subarray.
For each subarray, the partitioning step places another element in its final location of
the sorted array and creates two more unsorted subarrays. A subarray consisting of
one element is sorted, so that element is in its final location.
The basic algorithm seems simple enough, but how do we determine the final
position of each subarray’s first element? As an example, consider the following set of
values—the element in bold is the partitioning element that will be placed in its
final location in the sorted array:
37 2 6 4 89 8 10 12 68 45
a) Starting from the rightmost array element, compare each element with 37
until an element less than 37 is found, then swap 37 and that element. The
first element less than 37 is 12 , so we swap 37 and 12 . In the updated array
below, we show 12 in [] to indicate that it was just swapped with 37 :
[12] 2 6 4 89 8 10 37 68 45
b) Starting from the array’s left, but beginning with the element after 12 , com-
pare each element with 37 until an element greater than 37 is found, then
swap 37 and that element. The first element greater than 37 is 89 , so we swap
37 and 89 . The updated array is
12 2 6 4 37 8 10 [89] 68 45
c) Starting from the right, but beginning with the element before 89 , compare
each element with 37 until an element less than 37 is found, then swap 37
and that element. The first element less than 37 is 10 , so we swap 37 and 10 .
The updated array is
12 2 6 4 [10] 8 37 89 68 45
d) Starting from the left, but beginning with the element after 10 , compare
each element with 37 until an element greater than 37 is found, then swap
37 and that element. There are no more elements greater than 37 . When we
compare 37 with itself, we know that 37 is in its final location in the sorted
array.
Once the partition has been applied to the array, there are two unsorted subarrays.
The subarray with values less than 37 contains 12 , 2 , 6 , 4 , 10 and 8 . The subarray
with values greater than 37 contains 89 , 68 and 45 . Quicksort continues by partition-
ing both subarrays in the same manner as the original array.
Write recursive function quicksort to sort a one-dimensional integer array. The
function should receive as arguments an int array, a starting subscript and an ending
subscript. The quicksort should call the function partition to perform the parti-
tioning step.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MAXVALUE 100
#define RADIX 10
#define TOLEFT -1
#define TORIGHT 1

void printArray(int *array, size_t fromIndex, size_t toIndex);
void quicksort(int *array, int leftIndex, int rightIndex);
int partition(int *array, int fromIndex, int toIndex, int direction);
static int lessThan(int, int);
static int greaterThan(int, int);
static int (*compare[3])(int, int) = {lessThan,
	lessThan/*this could be greaterThan - anyway this function will never get called*/,
	greaterThan};
int inArray(int *array, int number);

int main (int argc, char *argv[])
{
	//partition algorithm doesn't work with duplicates!!!
	//int array[SIZE] = {39, 51, 55, 99, 72, 41, 91, 94, 37, 39};
	//int array[SIZE] = {60, 95, 59, 95, 54, 99, 25, 86, 61, 95};
	
	//generate array of unique elements
	int array[SIZE] = {0};
	srand(time(NULL));
	int number = 0;
	for (size_t i = 0; i < SIZE; ++i) {
		//to garantie 2 or 3 digit values we use this trick
		do {
			number = rand() % (MAXVALUE - MAXVALUE / RADIX) + MAXVALUE / RADIX;
		} while (inArray(array, number));
		array[i] = number;
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
	
	return 0;
}
void quicksort(int *array, int leftIndex, int rightIndex) {
	printf("leftIndex = %d, rightIndex = %d\n", leftIndex, rightIndex);
	//if (leftIndex != rightIndex) {
		printArray(array, leftIndex, rightIndex);
		int index = partition(array, rightIndex, leftIndex, TOLEFT);
		printf("index from partition = %d, element = %d\n", index, array[index]);
		if (leftIndex != index) {
			quicksort(array, leftIndex, index - 1);
		}
		//puts("left subarray done");
		if (rightIndex != index) {
			quicksort(array, index + 1, rightIndex);
		}
		//puts("right subarray done");
	//}
}
int partition(int *array, int fromIndex, int toIndex, int direction) {
	int index = 0;
	if (fromIndex == toIndex) {
		index = fromIndex;
	} else {
		//adjusting direction to avoid out-of-bounds when direction = -1
		while (compare[direction + 1](array[toIndex], array[fromIndex])) {
			fromIndex += direction;
			//check whether or not partition condition satisfied
			//it could already happen and we may be out of bounds
			if (fromIndex == toIndex) {
				index = fromIndex;
				return index;
			}
		}
		//swap the elements
		int temp = array[fromIndex];
		array[fromIndex] = array[toIndex];
		array[toIndex] = temp;
		//debug print
		printArray(array, 0, SIZE - 1);
		//adjust arguments for the next recursion call
		direction *= TOLEFT;
		temp = fromIndex;
		fromIndex = toIndex + direction;
		toIndex = temp;
		//call itself
		index = partition(array, fromIndex, toIndex, direction);
	}
	return index;
}
static int lessThan(int a, int b){
	return a < b;
}
static int greaterThan(int a, int b) {
	return a > b;
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
void printArray(int *array, size_t fromIndex, size_t toIndex) {
	for (size_t i = 0; i < SIZE; ++i) {
		if (i >= fromIndex && i <= toIndex) {
			printf("%d ", array[i]);
		} else {
			printf("%s ", "  ");
		}
	}
	puts("");
}