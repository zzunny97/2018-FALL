#include <stdio.h>

int arr[10];

void merge(int* arr, int left, int mid, int right){
	int index1 = left, index = left;
	int index2 = mid+1;
	int sorted[10];
	while(index1<=mid && index2<=right){
		if(index1==mid){
			while(index2!=right){
				sorted[index] = arr[index2];
				index2++;
			}
		}
		else if(index2==right){
			while(index1!=mid){
				sorted[index] = arr[index1];
				index1++;
			}
		}
		else{
			if(arr[index1] >= arr[index2]){
				sorted[index] = arr[index2++];
			}
			else{
				sorted[index] = arr[index1++];
			}
		}
	}
	for(int i=left; i<right; i++)
		arr[i] = sorted[i];
}

void mergesort(int*arr, int left, int right){
	if(left< right){
		int mid = (right+left)/2;
		printf("%d %d %d\n", left, mid, right);
		mergesort(arr, left, mid);
		for(int i=left; i<=mid; i++)
			printf("%d ", arr[i]);
		printf("\n");
		for(int i=mid+1; i<=right; i++)
			printf("%d ", arr[i]);
		printf("\n");
		mergesort(arr, mid + 1, right);
		merge(arr, left, mid, right);

	}
}

int main(){
	for(int i=0; i<10; i++)
		arr[i] = 9-i;

	mergesort(arr, 0, 9);
	for(int i=0; i<10; i++)
		printf("%d ", arr[i]);
	printf("\n");
}


