#ifndef __HEAP_HPP__
#define __HEAP_HPP__

#include <iostream>
using namespace std;

int parent(int i) {
	return (i - 1) / 2;
}
int left(int i) {
	return 2 * i + 1;
}
int rigth(int i) {
	return 2 * i + 2;
}

void maxHeapify(int A[], int n, int i) {
	int l = left(i);
	int r = rigth(i);
	int largest(0);
	if (l <= (n - 1) && A[l] > A[i]) {
		largest = l;
	}
	else
		largest = i;
	if (r <= (n - 1) && A[r] > A[largest]) {
		largest = r;
	}
	if (largest != i) {
		swap(A[i], A[largest]);
		maxHeapify(A, n, largest);
	}
}

void buildMaxHeap(int A[], int n) {
	for (int i = n / 2 - 1; i >= 0; --i) {
		maxHeapify(A, n, i);
	}
}

void print(int A[], int n) {
	for (int i = 0; i < n; ++i) {
		cout << A[i] << " ";
		//cout << endl;
	}
}

//aplicación de ordenamiento
void heapsort(int A[], int n) {
	buildMaxHeap(A, n);
	for (int i = n - 1; i > 0; --i) {
		swap(A[0], A[i]);
		maxHeapify(A, --n, 0);
	}
}

#endif // !__HEAP_HPP__
/*
int main() {
	int A[10] = { 16,14,10,8,7,19,3,2,4,1 };
	buildMaxHeap(A, 10);
	print(A, 10);
	cout << endl;
	heapsort(A, 10);
	print(A, 10);

	cin.ignore();
	cin.get();
	return 0;
}
*/