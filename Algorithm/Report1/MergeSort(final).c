#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN 100

typedef enum { false, true } bool;

void random_array();
void already_sorted_array();
void reversely_sorted_array();
void print(int* list);
void merge(int* list, int left, int mid, int right);
void merge_sort(int* list, int left, int right);

int cnt;

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	random_array();
	printf("\n\n");
	already_sorted_array();
	printf("\n\n");
	reversely_sorted_array();
	return 0;
}

void random_array()
{
	bool check[1000] = {false};
	int A[LEN];
	for(int i=0; i<LEN; ){
		int temp = rand()%1000;
		if(check[temp] == false){
			check[temp] = true;
			A[i] = temp;
			i++;
		}
	}
	cnt = 0;
	print(A);
	merge_sort(A, 0 , LEN-1);
	print(A);
	printf("# of comparison = %d\n", cnt);
}

void already_sorted_array()
{
	int A[LEN];
	for(int i=0; i<LEN; i++){
		A[i] = i+1;
	}
	cnt = 0;
	print(A);
	merge_sort(A, 0 , LEN-1);
	print(A);
	printf("# of comparison = %d\n", cnt);
}

void reversely_sorted_array()
{
	int A[LEN];
	for(int i=0; i<LEN; i++){
		A[i] = LEN-i;
	}
	cnt = 0;
	print(A);
	merge_sort(A, 0 , LEN-1);
	print(A);
	printf("# of comparison = %d\n", cnt);
}

void print(int* list)
{
	for(int i=0; i<LEN; i++){
		printf("%d ", list[i]);
	}
	printf("\n");
}

void merge_sort(int* list, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		merge_sort(list, left, mid);	
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

void merge(int* list, int left, int mid, int right)
{
	int sorted[LEN];
	int first = left, second = mid + 1, i = left;

	while (first <= mid && second <= right) {
		cnt++;
		if (list[first] <= list[second]){
			sorted[i++] = list[first++];
		}
		else{
			sorted[i++] = list[second++];
		}
	}

	if (first > mid) {
		for (int j = second; j <= right; j++)
			sorted[i++] = list[j];
	} else {
		for (int j = first; j <= mid; j++)
			sorted[i++] = list[j];
	}

	for (int j = left; j <= right; j++)
		list[j] = sorted[j];
}