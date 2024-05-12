#include <stdio.h>
#include <stdlib.h>

#define SIZE_ARR 20
#define RAND_RANGE 100

void swap(int * x, int * y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void print_arr(const int arr[]) {
	for (int i = 0; i < SIZE_ARR; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n\n");
}

void insertion(int arr[]) {
	for (int i = 0; i < SIZE_ARR; i++) {
		for (int j = 0; j < i; j++) {
			if (arr[j] >  arr[i]) {
				swap(&arr[j], &arr[i]);
				print_arr(arr);
			}
		}
	}
}

int main(void) {
	int arr[SIZE_ARR];
	int n = 0;

	for (int i = 0; i < SIZE_ARR; i++) {
		n = rand() % (RAND_RANGE + 1); printf("%d", n);
		arr[i] = n;
	}

	print_arr(arr);
	insertion(arr);
	insertion(arr);

	return 0;
}
