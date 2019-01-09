#include <stdio.h>

int* insertion_sort(int *arr, int len)
{
	int i, j, min, key;
	for(i=0; i<len; i++){
		min=i;
		for(j=i+1; j<len; j++){
			if(arr[min]>arr[j]) min = j;
		}
		key=arr[min];
		for(j=min-1; j>=i; j--){
			arr[j+1]=arr[j];
		}
		arr[i]=key;
	}
	return arr;
}

int* insertion_sort2(int *arr, int len)
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
	return arr;
}

void Print(int* arr, int len)
{
	int i;
	for(i=0;i<len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main()
{
	int arr[]= {8,2,4,9,3,6};
	Print(arr, 6);
	int* sorted;
	int len = 6;
	//sorted=insertion_sort(arr, 6);
	sorted=insertion_sort2(arr, 6);
	Print(sorted, 6);
	return 0;
}