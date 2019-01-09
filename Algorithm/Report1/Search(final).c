#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100

typedef enum { false, true } bool;

typedef struct _Node{
	int val;
	struct _Node* left;
	struct _Node* right;	
} Node;


void filler(int* a);
void linear_search(int* a, int key);
void binary_search(int* a, int key);
void sort(int* a);
Node* tree_create(int* a);
Node* CreateRoot(int val);
void CreateLeft(Node* root, int val);
void CreateRight(Node* root, int val);
void Insert(Node* root, int val);
void traverse(Node* root);


int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int A[N];
	filler(A);
	for(int i=0; i<N; i++){
		printf("%d ", A[i]);
	}
	printf("\n");
	int key = rand()%1000;
	printf("Linear Search\n");
	linear_search(A, key);
	printf("Binary Search\n");
	binary_search(A, key);
	return 0;
}

void filler(int* a){
	bool check[1000];
	for(int i=0; i<N; ){
		int temp = rand()%1000;
		
		if(check[temp] == false){
			check[temp] = true;
			a[i] = temp;
			i++;
		}
	}
}

void linear_search(int* a, int key){
	int result = -1, comparison = 0;
	for(int i=0; i<N; i++){
		comparison++;
		if(a[i] == key){
			result = i;
			break;
		}
	}

	if(result == -1){
		printf("key not detected\n");
		printf("key = %d\n", key);
		printf("# of comparison = %d\n", comparison);
	}
	else{
		printf("key detected\n");
		printf("key = %d", key);
		printf("A[%d] = %d", result, a[result]);
		printf("# of comparison = %d\n", comparison);
	}
}

void binary_search(int* a, int key){
	int comparison = 0;
	Node* root = tree_create(a);
	//traverse(root);
	Node* cur = root;
	while(cur!=NULL){
		comparison++;
		if(cur->val > key){
			cur = cur->left;
		}
		else if(cur->val < key){
			cur = cur->right;
		}
		else{
			printf("key detected\n");
			printf("key = %d\n", key);
			printf("cur->val = %d\n", cur->val);
			printf("# of comparison = %d\n", comparison);
			return;
		}
	}
	printf("key not detected\n");
	printf("key = %d\n", key);
	printf("# of comparison = %d\n", comparison);
}

Node* tree_create(int* a){
	Node* root = CreateRoot(a[0]);

	for(int i=1; i<N; i++){
		Insert(root, a[i]);
	}

	return root;

}

Node* CreateRoot(int val){
	Node* node = (Node*)malloc(sizeof(Node));
	node->val = val;
	node->left = NULL;
	node->right = NULL;

	return node;
}

void Insert(Node* root, int val){
	if(root->val == val) exit(1);
	else if(root->val > val){
		if(root->left == NULL)
			CreateLeft(root, val);
		else
			Insert(root->left, val);
	}
	else{
		if(root->right == NULL)
			CreateRight(root, val);
		else
			Insert(root->right, val);
	}
}

void CreateLeft(Node* root, int val){
	Node* new = (Node*)malloc(sizeof(Node));
	new->val = val;
	new->left = NULL;
	new->right = NULL;
	root->left = new;
}

void CreateRight(Node* root, int val){
	Node* new = (Node*)malloc(sizeof(Node));
	new->val = val;
	new->left = NULL;
	new->right = NULL;
	root->right = new;
}

void traverse(Node* root){
	if(root!=NULL){
		traverse(root->left);
		printf("%d ", root->val);
		traverse(root->right);
	}
}


