#include <stdio.h>

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}


int main(){
	int a[5] = {5,4,3,2,1};
	int index;
	for(int i=1; i<5; i++){
		for(int k=0; k<5; k++)
			printf("%d ", a[k]);
		printf("\n");
		int key = a[i];
		printf("key=%d\n", key);
		int j = i-1;
		while(j>=0){
			if(a[j]>key){
				a[j+1] = a[j];
			}
			else{
				break;
			}
			j--;
		}
		printf("j= %d\n",j); 
		a[j+1] = key;
	}
	for(int i=0; i<5; i++)
		printf("%d ", a[i]);
}
