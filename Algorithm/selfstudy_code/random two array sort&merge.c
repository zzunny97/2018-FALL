//다음 코드는 랜덤하게 생성된 두 배열을 각각 소팅하고 merge하는 코드임.
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void Print(int* arr, int len);
void insertion_sort(int *arr, int len);
int* merge_sort(int* arr1, int* arr2, int len1, int len2);
void array_generator(int *arr, int len);

void Print(int* arr, int len)
{
	int i;
	for(i=0;i<len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void insertion_sort(int *arr, int len)
{
	int i;
	for (i = 1; i < len; ++i)
	{
		int j=i-1, key=arr[i];
		while(arr[j]>key && j>=0){
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=key;
	}
}

int* merge_sort(int* arr1, int* arr2, int len1, int len2)
{
	int index1=0, index2=0, index=0;
	int *sorted = (int*)malloc(4*(len1+len2));
	int i;
	while(index1<len1 || index2<len2){
		if(index1==len1 || index2==len2){
			if(index1==len1)
				sorted[index++]=arr2[index2++];
			else
				sorted[index++]=arr1[index1++];
		} else{
			if(arr1[index1]>=arr2[index2])
				sorted[index++]=arr2[index2++];
			else
				sorted[index++]=arr1[index1++];
		}
	}
	return sorted;
}

void array_generator(int *arr, int len)
{
	int i;
	for(i=0; i<len; i++){
		arr[i]=rand()%10000;
	}
}

int main(int argc, char const *argv[])
{
	int* arr1 = (int*)malloc(4*MAX);
	int* arr2 = (int*)malloc(4*MAX);
	array_generator(arr1, MAX); array_generator(arr2, MAX);
	insertion_sort(arr1, MAX);
	insertion_sort(arr2, MAX);
	int *sorted = merge_sort(arr1, arr2, MAX, MAX);
	Print(sorted, 2*MAX);
	return 0;
}