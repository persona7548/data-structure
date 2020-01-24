#include <stdio.h>
#include <stdlib.h>

int partition(int S[],int low, int high);
void quicksort(int S[],int low, int high);
void exchange(int* a, int* b);


int main() {
	
	int S[] = {14,27,2,15,8,25,22,32,9};
	int size = sizeof(S) / sizeof(int) - 1;
	quicksort(S,0,size);
	
	for (int i = 0; i<=size; i++)
		printf("%d ", S[i]);
	printf("\n");
	return 0;
}

void quicksort(int S[], int low, int high) {
	int pivotpoint;
	if (high > low) {
		pivotpoint = partition(S, low, high);
		quicksort(S, low, pivotpoint - 1);
		quicksort(S, pivotpoint+1, high);
	}
}

int partition(int S[],int low, int high) {
	int i, j,pivotitem;

	pivotitem = S[low];	          
	j = low;
	for (i = low + 1; i <= high; i++)
		if (S[i] < pivotitem) {
			j++;
			exchange(&S[i], &S[j]);
		}

	exchange(&S[low], &S[j]);

	return j;
}


void exchange(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

