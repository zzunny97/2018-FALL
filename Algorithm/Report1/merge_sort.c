#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 100
void ran();
void alr_sorted();
void rev_sorted();
void print(int* arr);
void inser_sort(int *arr);
int* merge_sort(int* arr1, int* arr2, int len1, int len2);
int cnt;

int main(int argc, char const *argv[])
{
	ran();
	printf("\n\n\n");
	alr_sorted();
	printf("\n\n\n");
	rev_sorted();
	printf("\n\n\n");
	return 0;
}

void ran()
{
	int A[LEN]; cnt = 0;
	srand(time(NULL));
	for(int i=0; i<LEN; i++){
		A[i]=rand()%1000;
	}
	print(A);
	int a[LEN/2], b[LEN/2];
	for(int i=0; i<LEN; i++){
		if(i<LEN/2){
			a[i] = A[i];
		} else{
			b[i-LEN/2] = A[i];
		}
	}
	for(int i=0; i<LEN/2; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
	for(int i=0; i<LEN/2; i++){
		printf("%d ", b[i]);
	}
	printf("\n");

	inser_sort(a); inser_sort(b);
	for(int i=0; i<LEN/2; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
	for(int i=0; i<LEN/2; i++){
		printf("%d ", b[i]);
	}
	printf("\n");
	int* result = merge_sort(a, b, LEN/2, LEN/2);
	print(result);
}

void alr_sorted()
{
	int A[LEN]; cnt = 0;
	for(int i=0; i<LEN; i++){
		A[i] = i+1;
	}
	print(A);
	int a[LEN/2], b[LEN/2];
	for(int i=0; i<LEN; i++){
		if(i<LEN/2){
			a[i] = A[i];
		} else{
			b[i-LEN/2] = A[i];
		}
	}
	for(int i=0; i<LEN/2; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
	for(int i=0; i<LEN/2; i++){
		printf("%d ", b[i]);
	}
	printf("\n");

	inser_sort(a); inser_sort(b);
	for(int i=0; i<LEN/2; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
	for(int i=0; i<LEN/2; i++){
		printf("%d ", b[i]);
	}
	printf("\n");
	int* result = merge_sort(a, b, LEN/2, LEN/2);
	print(result);
}

void rev_sorted()
{
	int A[LEN]; cnt = 0;
	for(int i=0; i<LEN; i++){
		A[i] = LEN-i;
	}
	print(A);
	int a[LEN/2], b[LEN/2];
	for(int i=0; i<LEN; i++){
		if(i<LEN/2){
			a[i] = A[i];
		} else{
			b[i-LEN/2] = A[i];
		}
	}
	for(int i=0; i<LEN/2; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
	for(int i=0; i<LEN/2; i++){
		printf("%d ", b[i]);
	}
	printf("\n");

	inser_sort(a); inser_sort(b);
	for(int i=0; i<LEN/2; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
	for(int i=0; i<LEN/2; i++){
		printf("%d ", b[i]);
	}
	printf("\n");
	int* result = merge_sort(a, b, LEN/2, LEN/2);
	print(result);
}

void print(int* arr)
{
	int i;
	for(i=0;i<LEN; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void inser_sort(int *arr)
{
	int i;
	for (i = 1; i < LEN/2; ++i)
	{
		int j=i-1, key=arr[i];
		while(arr[j]>key && j>=0){
			cnt++;
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=key;
	}
}

int* merge_sort(int* arr1, int* arr2, int len1, int len2)
{
	int idx1=0, idx2=0, idx=0;
	int *result = (int*)malloc(4*LEN);
	do{
		if(idx1==len1){
			while(idx2!=len2){
				result[idx++]=arr2[idx2++];
				cnt++;
			}
		} else if(idx2==len2){
			while(idx1!=len1){
				result[idx++]=arr1[idx1++];
				cnt++;
			}
		} else{
			cnt++;
			if(arr1[idx1]>=arr2[idx2])
				result[idx++]=arr2[idx2++];
			else
				result[idx++]=arr1[idx1++];
		}
	}while(!(idx1==len1&&idx2==len2));

	printf("# count = %d\n", cnt);
	return result;
}
