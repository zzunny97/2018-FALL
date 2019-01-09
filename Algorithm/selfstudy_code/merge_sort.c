//다음 코드는 '이미 sort되어 있는 두 배열'을 merge하는 코드임.
#include <stdio.h>

void Print(int* arr, int len)
{
	int i;
	for(i=0;i<len; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
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
		//Print(sorted, index);
	}
	return sorted;
}



int main(int argc, char const *argv[])
{
	int arr1[]={2,7,13,20};
	int arr2[]={1,9,11,12};
	int *sorted = merge_sort(arr1, arr2, 4, 4);
	Print(sorted, 8);
	return 0;
}
