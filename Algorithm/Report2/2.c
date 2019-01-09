#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _Node{
	struct _Node* left;
	struct _Node* right;
	struct _Node* parent;
	int key;
}Node;

typedef enum {false, true} bool;


void Insert(Node* root, int key);
Node* Search(Node* root, int key);
void Search2(Node* root, int key);
Node* Minimum(Node* x);
Node* Maximum(Node* x);
Node* Successor(Node* x);
Node* Predecessor(Node* x);
Node* Nearest_Neighbor(Node* root, int key);
void Delete(Node* root, int key);
void Print_BST(Node* root);
int Height(Node* root);

void Insert(Node* root, int key)
{
	if(root->key == -1){
		root->key = key;
		return;
	}
	if(Search(root, key)!=NULL){
		printf("The key %d already exists in the tree\n", key);
		return;
	}
	Node* z = (Node*)malloc(sizeof(Node));
	z->key = key;
	z->left = NULL;
	z->right = NULL;
	z->parent = NULL;
	Node* y = NULL;
	Node* x = root;
	while(x!=NULL){
		y = x;
		if(z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if(z->key < y->key)
		y->left = z;
	else
		y->right = z;
}

Node* Search(Node* root, int key){
	if (root==NULL||root->key==key) return root;
	else if (root->key>key)
		return Search(root->left, key);
	else
		return Search(root->right, key);
}

void Search2(Node* root, int key){
	Node* cur = root;
	while(cur!=NULL && cur->key!=key){
		if (cur->key > key){
			printf("%d ", cur->key);
			cur = cur->left;
		}
		else if(cur->key < key){
			printf("%d ", cur->key);
			cur = cur->right;
		}
	}
	if(cur==NULL){
		printf("\nThe key %d doesn't exist in the tree\n\n", key);
	}
	else{
		printf("%d ", cur->key);
		printf("\nSearching %d completed\n\n", key);
	}
}

Node* Minimum(Node* x){
	while(x->left!=NULL)
		x = x->left;
	return x;
}
Node* Maximum(Node* x){
	while(x->right!=NULL)
		x = x->right;
	return x;
}

Node* Successor(Node* x){
	if(x->right!=NULL){
		return Minimum(x->right);
	} else{
		Node* y = x->parent;
		while(y!=NULL&&x==y->right){
			x = y;
			y = y->parent;
		}
		return y;
	}
}

Node* Predecessor(Node* x){
	if(x->left!=NULL){
		return Maximum(x->left);
	} else{
		return x->parent;
	}
}

Node* Nearest_Neighbor(Node* root, int key){
	Node* a = Search(root, key);
	if(a==NULL){
		Node* temp = root;
		while(1){
			if (temp->key > key){
				if(temp->left!=NULL)
					temp = temp->left;
				else
					break;
			}
			else if(temp->key < key){
				if(temp->right!=NULL)
					temp = temp->right;
				else
					break;
			}
			else{
				printf("fucking error happened\n");
			}
		}
		a = temp;
	}
	Node* b = Successor(a);
	Node* c = Predecessor(a);

	Node* x = a;
	int result = key-(a->key);
	if(result > key-(b->key))
		x = b;
	if(result > key-(c->key))
		x = c;
	return x;
	
}

void Delete(Node* root, int key)
{
	Node* cur = Search(root, key);
	Node* y = NULL;
	Node* x = NULL;
	if(cur==NULL){
		printf("The key %d doesn't exist in the tree\n", key);
		return;
	} else{
		if(cur->left==NULL && cur->right==NULL){
			y = cur;
		} else{
			y = Successor(cur);
		}

		if(y->left!=NULL){
			x = y->left;
		} else{
			x = y->right;
		}

		if(x!=NULL) x->parent = y->parent;
		if(y->parent==NULL){
			root = x;
		} else if(y == y->parent->left){
			y->parent->left = x;
		} else{
			y->parent->right = x;
		}

		if(y!=cur){
			cur->key = y->key;
		}
	}
}

void Print_BST(Node* root){
	if (root != NULL){
		Print_BST(root->left);
		printf("%d ", root->key);
		Print_BST(root->right);
	}
}

int Height(Node* root){
	if(root==NULL)
		return -1;
	int left_height = Height(root->left);
	int right_height = Height(root->right);

	if(left_height > right_height)
		return left_height+1;
	else
		return right_height+1;
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	bool check[50] = {false};
	int *keys = (int*)malloc(sizeof(int)*20);
	for(int i=0; i<20; i++){
		while(1){
			int candidate = rand()%50;
			if(check[candidate] == false){
				keys[i] = candidate;
				check[candidate] = true;
				break;
			} else{
				continue;
			}
		}
	}
	for(int i=0; i<20; i++){
		printf("keys[%d] = %d\n", i, keys[i]);
	}
	Node* root = (Node*)malloc(sizeof(Node));
	root->key = -1;
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
	for(int i=0; i<20; i++){
		Insert(root, keys[i]);
	}
	printf("Randomized 20 keys has been inserted\n");
	Print_BST(root); printf("\n\n");
	printf("Search 15\n");
	Search2(root, 15);
	printf("Search 8\n");
	Search2(root, 8);
	printf("Search 18\n");
	Search2(root, 18);
	printf("Nearest neighbor of 17 = %d\n", Nearest_Neighbor(root, 17)->key);
	printf("Nearest neighbor of 3 = %d\n", Nearest_Neighbor(root, 3)->key);
	printf("Nearest neighbor of 8 = %d\n\n", Nearest_Neighbor(root, 8)->key);
	printf("Insert 5\n");
	Insert(root, 5);
	Print_BST(root);printf("\n");
	printf("Insert 7\n");
	Insert(root, 7); 
	Print_BST(root);printf("\n");
	printf("Insert 17\n");
	Insert(root, 17);
	Print_BST(root);printf("\n");
	printf("Insert 51\n");
	Insert(root, 51);
	Print_BST(root);printf("\n");
	printf("Delete 17\n");
	Delete(root, 17);
	Print_BST(root);printf("\n");
	printf("Delete 5\n");
	Delete(root, 5);
	Print_BST(root);printf("\n");
	printf("Delete 51\n");
	Delete(root, 51);
	Print_BST(root);printf("\n");
	printf("Delete 17\n");
	Delete(root, 17);
	Print_BST(root);printf("\n");

	printf("\n\nSolution of problem 3-5\n");
	printf("Input : 1 ~ 20 succesively\n");
	Node* root2 = (Node*)malloc(sizeof(Node));
	root2->key = -1;
	root2->left = NULL;
	root2->right = NULL;
	root2->parent = NULL;
	for(int i=0; i<20; i++){
		Insert(root2, i+1);
	}
	Print_BST(root2); printf("\n");
	printf("Height = %d\n", Height(root2));

	return 0;
}