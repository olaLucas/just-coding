#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARR_SIZE 10
#define RAND_RANGE 100

void swap(int * x, int * y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void print_arr(const int arr[], const int ini, const int fim) {
	for (int i = ini; i < fim; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n\n");
}

int sort(int arr[], int ini, int fim) {
	int x = 0;
	if (fim - ini > 1) {
		x = (ini + fim) / 2;
	} else {
		x = fim;
	}

	int i = ini, j = fim;
	while (true) {
		while (arr[i] < arr[x] && i < j) {
			i++;	
		}

		while (arr[j] > arr[x] && i < j) {
			j--;
		}

		if (j <= i) {
			 break;
		} else {
			swap(&arr[i], &arr[j]);
			printf("x = %d, arr[%d]\n\n", arr[x], x);
			print_arr(arr, ini, fim);
		}
	}

	return x;
}

void quick(int arr[], int ini, int fim) {
	if (fim < ini)
		return;

	int x = sort(arr, ini, fim);
	if (ini < x)
		quick(arr, ini, x);
	
	if (fim > x)
		quick(arr, x, fim);
}

int main(void) {
	int arr[ARR_SIZE];

	for (int i = 0; i < ARR_SIZE; i++) {
		arr[i] = rand() % RAND_RANGE;
	}

	print_arr(arr, 0, ARR_SIZE - 1);
	quick(arr, 0, ARR_SIZE - 1);
	print_arr(arr, 0, ARR_SIZE - 1);
	
	return 0;
}
