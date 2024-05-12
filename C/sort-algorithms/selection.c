#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 5
#define RAND_RANGE 10

void swap(int * x, int * y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void print_arr(const int arr[]) {
	for (int i = 0; i < ARR_SIZE; i++)
		printf("%d ", arr[i]);
	
	printf("\n\n");
}

void selection(int arr[]) {
	int n = 0;
	for (int i = 0; i < ARR_SIZE - 1; i++) {
		n = i;
		for (int j = i + 1; j < ARR_SIZE; j++) {
			if (arr[j] < arr[n]) {
				n = j;
			}
		}

		if (n != i) {
			swap(&arr[i], &arr[n]);
		}

		print_arr(arr);
	}
}

int main(void) {
	int arr[ARR_SIZE];

	int n = 0;
	for (int i = 0; i < ARR_SIZE; i++) {
		arr[i] = rand() % RAND_RANGE; 
	}

	selection(arr);
	return 0;
}
