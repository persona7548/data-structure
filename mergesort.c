#include <stdio.h>
#include <stdlib.h>

void mergesort(int n, int S[]);
void merge(int h, int m, int U[], int V[], int S[]);

const int SIZE = 8;

int main() {
	int array[SIZE] = { 14, 27, 6, 5, 8, 22, 26, 32 };
	mergesort(SIZE, array);

	for(int i=0;i<SIZE;i++)
		printf("%d ", array[i]);

	return 0;
}

void mergesort(int n, int S[]) {
	const int h = n/2, m= n-h;
	int i,j;

	int *U = (int*)malloc(sizeof(int) * h);
	int *V = (int*)malloc(sizeof(int) * m);

	for (i = 0; i < h; i++)
		U[i] = i;
	for (i = 0; i < m; i++)
		V[i] = i;

	if (n > 1) {
		for (i=0; i < h; i++)
			U[i] = S[i];//copy S[1] through S[h] to U[1] through U[h];
		for (j=0 ; j < m; j++)
			V[j] = S[j+m];//copy S[h + 1] through S[n] to V[1] through V[m];

		mergesort(h, U);
		mergesort(m, V);
		merge(h, m, U, V, S);
	
	}
}

void merge(int h, int m, int U[], int V[], int S[]) {
	int i, j, k; //index
	int size = h + m;
	i = 0; j = 0; k = 0;
	while (i < h && j < m) {
		if (U[i] < V[j]) {
			S[k] = U[i]; i++;
		}
		else {
			S[k] = V[j]; j++;
		}
		k++;
	}
	if (i >= h)
		for (k; k < size; k++)
			S[k] = V[k-i];// copy V[j] through V[m] to S[k] through S[h + m];
	else
		for (k; k < size; k++)
			S[k] = U[k-j]; //copy U[i] through U[h] to S[k] through S[h + m];
}