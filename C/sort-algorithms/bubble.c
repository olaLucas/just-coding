#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 20
#define RAND_RANGE 100

void swap(int * x, int * y) {
	int temp = * x;
	*x = *y;
	*y = temp;
}


void print_arr(const int arr[]) {
	for (int i = 0; i < ARR_SIZE; i++) {
		printf("%d ", arr[i]);
	}
		
	printf("\n\n");
}


void bubble(int arr[]) {
	for (int i = 0; i < ARR_SIZE; i++) {
		for (int j = i + 1; j < ARR_SIZE; j++) {
			if (arr[j] < arr [i]) {
				swap(&arr[j], &arr[i]);
				print_arr(arr);
			}
		}
	}
}


int main(void) {
	int arr[ARR_SIZE];

	for (int i = 0; i < ARR_SIZE; i++) {
		arr[i] = rand() % RAND_RANGE;
	}

	bubble(arr);
	return 0;
}
