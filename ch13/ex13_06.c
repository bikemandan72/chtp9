/*
13.6 (Bucket Sort)
A bucket sort begins with a one-dimensional array of positive integers to sort, and a
two-dimensional array of integers with rows subscripted from 0 to 9 and columns
subscripted from 0 to n – 1, where n is the array’s number of values to sort. Each row
of the two-dimensional array is a “bucket.” In this exercise, you’ll write a
bucketSort function that takes as arguments an int array and its size.
The algorithm is as follows:
a) Loop through the one-dimensional array and, based on each value’s ones digit, place
the value in a bucket (a row of the two-dimensional bucket array). For example, place
97 in row 7, 3 in row 3 and 100 in row 0.
b) Loop through the bucket array’s rows and columns and copy the values back to the
original array. The new order of the above values in the one-dimensional array is 100,
3 and 97.
c) Repeat this process for each subsequent digit position (tens, hundreds, thousands,
and so on) and stop when the largest number’s leftmost digit has been processed.
The second pass of the array places 100 in row 0, 3 in row 0 (it had only one
digit, so we treat it as 03) and 97 in row 9. After this pass, the values’ order in the
one-dimensional array is 100, 3 and 97. The third pass places 100 in row 1, 3 (003)
in row zero and 97 (097) in row zero (after 3). The bucket sort is guaranteed to
properly sort all the values after processing the leftmost digit of the largest number.
The bucket sort knows it’s done when all the values are copied into row zero of the
two-dimensional bucket array.
The two-dimensional bucket array is ten times the size of the int array being
sorted. This sorting technique provides far better performance than, for example, a
bubble sort but requires much larger storage capacity. Bubble sort requires only one
additional memory location for the type of data being sorted. Bucket sort is an
example of a space–time trade-off. It uses more memory but performs better.
The bucket sort algorithm described above requires copying all the data back to
the original array on each pass. Another possibility is to create a second two-dimen-
sional bucket array and repeatedly move the data between the two bucket arrays
until all the data is copied into row zero of one of the arrays. Row zero then contains
the sorted array.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#define SIZE 10
#define MAXVALUE 100
#define DIGITS 10 /*row 0..9 in the helper array(matrix)*/
#define RADIX 10

void printArray(int *array, size_t fromIndex, size_t toIndex);
void bucketSort(int *array, size_t fromIndex, size_t toIndex);
void resetBuckets(int buckets[][SIZE]);
void refillTargetArray(int *array, int buckets[][SIZE]);
int getDigit(int number, unsigned int digit);

int main(int argc, char *argv[])
{
	//generate array
	int array[SIZE] = {0};
	srand(time(NULL));
	for (size_t i = 0; i < SIZE; ++i) {
		//to garantie 2 or 3 digit values we use this trick
		array[i] = rand() % (MAXVALUE - MAXVALUE / 10) + MAXVALUE / 10;
	}
	//print unsorted array
	puts("Unsorted array:");
	printArray(array, 0, SIZE - 1);
	//sort it
	bucketSort(array, 0, SIZE - 1);
	//print sorted array
	puts("Sorted array:");
	printArray(array, 0, SIZE - 1);
	
	return 0;
}
void bucketSort(int *array, size_t fromIndex, size_t toIndex) {
	int maxBucket = 0;
	unsigned long digit = 1;
	unsigned long maxDigit = digit;
	while (getDigit(INT_MAX, maxDigit)) {
		maxDigit++;
	}
	maxDigit -= 2; // adjust once for future comparisons
	printf("maxDigit = %lu given INT_MAX = %d\n", maxDigit, INT_MAX);
	int buckets[DIGITS][SIZE] = {0};
	resetBuckets(buckets);
	do {
		maxBucket = 0;
		for (size_t i = 0; i < SIZE; ++i) {
			//define the digit (or "bucket")
			int bucket = getDigit(array[i], digit);
			//track that all digits are zeroes
			maxBucket += bucket;
			//put number in the approppriate bucket
			for (size_t j = 0; j < SIZE; ++j) {
				if (buckets[bucket][j] < 0) {
					buckets[bucket][j] = array[i];
					break;
				}
			}
		}
		refillTargetArray(array, buckets);
		if (maxBucket == 0) {
			break;
		}
		puts("Sorting...");
		printArray(array, 0, SIZE - 1);
		resetBuckets(buckets);
		digit++;
		if (digit > maxDigit) {
			puts("Error! Element in the array contains more digits than the program "
				"can handle. Exiting without sorting.");
			break;
		}
	} while (maxBucket > 0 && (digit <= maxDigit));
}
int getDigit(int number, unsigned int digit) {
	int quotient, remainder;
	quotient = number;
	for (size_t i = 0; i < digit; ++i) {
		remainder = quotient % RADIX;
		quotient = quotient / RADIX;
	}
	return remainder;
}
void refillTargetArray(int *array, int buckets[][SIZE]){
	int j = 0;
	for (size_t bucket = 0; bucket < DIGITS; ++bucket) {
		for (size_t i = 0; i < SIZE; ++i) {
			if (buckets[bucket][i] >= 0) {
				array[j] = buckets[bucket][i];
				j++;
				if (j == SIZE) {
					return;
				}
			}
		}
	}
}
void resetBuckets(int buckets[][SIZE]) {
	for (size_t i = 0; i < DIGITS; ++i) {
		memset(buckets[i], -1, SIZE * sizeof(int));
	}
}
void printArray(int *array, size_t fromIndex, size_t toIndex) {
	for (size_t i = fromIndex; i <= toIndex; ++i) {
		printf("%d ", array[i]);
	}
	puts("");
}