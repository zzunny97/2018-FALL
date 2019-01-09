#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN 100

typedef enum { false, true } bool;

void random_array();
void already_sorted_array();
void reversely_sorted_array();
void print(int* list);
int bubble_sort(int* list);

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
	
	print(A);
	printf("# of comparison = %d\n", bubble_sort(A));
	print(A);
}

void already_sorted_array()
{
	int A[LEN];
	for(int i=0; i<LEN; i++){
		A[i] = i+1;
	}
	print(A);
	printf("# of comparison = %d\n", bubble_sort(A));
	print(A);
}

void reversely_sorted_array()
{
	int A[LEN];
	for(int i=0; i<LEN; i++){
		A[i] = LEN-i;
	}
	print(A);
	printf("# of comparison = %d\n", bubble_sort(A));
	print(A);
}

void print(int* arr)
{
	for(int i=0; i<LEN; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int bubble_sort(int* list)
{
	int cnt = 0;
	int temp;
	int i, j, k;
	for(i=0; i<LEN; i++){
		for(j=0; j<LEN-(i+1); j++){
			cnt++;
			if(list[j] > list[j+1]){
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
	return cnt;
}
