#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {false, true} bool;

//이거 100개의 노드 가진 100개의 트리를 짜야함.
typedef struct _Node{
	int color;	//1==red, 0==black
	struct _Node* left;
	struct _Node* right;
	struct _Node* parent;
	int hotel_num;	//key
	int price;
} HotelNode;

// 이거는 하나만
typedef struct _Node2{
	int color;
	struct _Node2* left;
	struct _Node2* right;
	struct _Node2* parent;
	int customer_id;	//key
	typedef reserve_locate reserveinfo;
} ReserveNode;

typedef struct _Node3{
	int period;
	int budget;
	int city_num;
	int hotel_num;
} reserveinfo;

Node* Left_Rotate(Node* root, Node* x);
Node* Right_Rotate(Node* root, Node* x);
Node* RB_Insert(Node* root, int key);
Node* RB_InsertFixUP(Node* root, Node* z);
Node* Minimum(Node* x);
Node* Successor(Node* x);
Node* RB_Delete(Node* root, int key);
Node* RB_DeleteFixUP(Node* root, Node* x);
void Print_RBTree(Node* root);
Node* Search(Node* root, int key);
int colorof(Node* n);
int Height(Node* root);

// 101개의 rb트리를 만들 것

// 하나는 100개의 도시에서 100개의 호텔정보를 저장하는 rb 트리 가격 
// 예약정보 스트럭쳐에 id, 기간, 예산, 호텔위치
// 전체 예약정보를 보고싶다면, 예약정보들 이것저것 보여주는 형식으로

int main(int argc, char const *argv[])
{
	// srand(time(NULL));
	// bool check[20] = {false};
	// int *keys = (int*)malloc(sizeof(int)*20);
	// for(int i=0; i<20; i++){
	// 	while(1){
	// 		int candidate = rand()%50;
	// 		if(check[candidate] == false){
	// 			keys[i] = candidate;
	// 			check[candidate] = true;
	// 			break;
	// 		} else{
	// 			continue;
	// 		}
	// 	}
	// }
	int keys[10];

	for(int i=0; i<10; i++){
		keys[i] = i;
	}
	Node* root = (Node*)malloc(sizeof(Node));
	root->key = -1;
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
	root->color = 1;
	for(int i=0; i<10; i++){
		root = RB_Insert(root, keys[i]);
		printf("root's key: %d\n", root->key);
		Print_RBTree(root); printf("\n");
	}
	for(int i=0; i<10; i++){
		printf("Deletion %d\n", i);
		root = RB_Delete(root, i);
		//printf("root's key: %d\n", root->key);
		Print_RBTree(root); printf("\n");
	}

	

	return 0;
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

Node* Search(Node* root, int key){
	if (root==NULL||root->key==key) return root;
	else if (root->key>key)
		return Search(root->left, key);
	else
		return Search(root->right, key);
}


void Print_RBTree(Node* root){
	if (root != NULL){
		Print_RBTree(root->left);
		if(root->color==0)
			printf("%d(black) ", root->key);
		else
			printf("%d(red) ", root->key);
		Print_RBTree(root->right);
	}
}


Node* Left_Rotate(Node* root, Node* x){
	Node* y = x->right;
	x->right = y->left;
	if(x->right!=NULL)
		x->right->parent = x;
	y->parent = x->parent;
	if(x->parent==NULL)
		root = y;
	else if(x==x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
	return root;
}

Node* Right_Rotate(Node* root, Node* x){
	Node* y = x->left;
	x->left = y->right;
	if(x->left!=NULL)
		x->left->parent = x;
	y->parent = x->parent;
	if(x->parent==NULL)
		root = y;
	else if(x==x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->right = x;
	x->parent = y;
	return root;
}

Node* RB_Insert(Node* root, int key){
	if (root->key == -1){
		root->key = key;
		root->color = 0;
		return root;
	}
	if(Search(root, key)!=NULL){
		printf("The key %d already exists in the tree\n", key);
		return root;
	}
	Node* new = (Node*)malloc(sizeof(Node));
	new->key = key;
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	new->color = 1;
	Node* y = NULL;
	Node* x = root;
	while(x!=NULL){
		y = x;
		if(new->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	new->parent = y;
	if(new->key < y->key)
		y->left = new;
	else
		y->right = new;
	root = RB_InsertFixUP(root, new);
	return root;

}

Node* RB_InsertFixUP(Node* root, Node* z){
	Node* p = NULL;
	Node* g = NULL;
	while(z!= root && z->color==1 && z->parent!=NULL && z->parent->color==1 && z->parent->parent!=NULL){
		Node* uncle = NULL;
		p = z->parent;
		g = z->parent->parent;
		if(g==NULL || p==NULL){
			break;
		}
		if(g!=NULL && p==g->left){
			uncle = g->right;
			if(uncle!=NULL && uncle->color==1){
				p->color = 0;
				uncle->color = 0;
				g->color = 1;
				z = g;
			}
			else{
				if(z==p->right){
					root = Left_Rotate(root, p);
					z = p;
					p = z->parent;
				}
				root = Right_Rotate(root, g);
				p->color = 0;
				g->color = 1;
				z = p;
			}
		}
		else{
			uncle = g->left;
			if(uncle!=NULL && uncle->color==1){
				p->color = 0;
				uncle->color = 0;
				g->color = 1;
				z = g;
			}
			else{
				if(z==p->left){
					root = Right_Rotate(root, p);
					z = p;
					p = z->parent;
				}
				root = Left_Rotate(root, g);
				p->color = 0;
				g->color = 1;
				z = p;
			}
		}
	}
	root->color = 0;
	return root;
}

Node* RB_Delete(Node* root, int key){
	if(Search(root, key)==NULL){
		printf("The key %d doesn't exist in the tree\n", key);
		return root;
	}
	if(root->key==key && root->left==NULL && root->right==NULL)
		return NULL;
	Node* x = Search(root, key);
	if(x->left!=NULL && x->right!=NULL){
		Node* y = x->left;
		while(y->right!=NULL)
			y = y->right;
		x->key = y->key;
		x = y;
	}
	Node* z;
	if(x->right==NULL)
		z = x->left;
	else
		z = x->right;
	if(x->color==0){
		x->color = colorof(z);
		root = RB_DeleteFixUP(root, x);
	}
	if(x->parent==NULL){
		root = z;
	}
	else{
		if(x == x->parent->left)
			x->parent->left = z;
		else
			x->parent->right = z;
	}

	if(z!=NULL)
		z->parent = x->parent;
	free(x);
	printf("root key = %d\n", root->key);
	root->color = 0;
	return root;
}

int colorof(Node* n){
	return n==NULL ? 0 : n->color;
}

Node* RB_DeleteFixUP(Node* root, Node* x){
	if(x->parent==NULL)
		return root;
	Node* s;
	if(x==x->parent->left)
		s = x->parent->right;
	else
		s = x->parent->left;
	if(colorof(s)==1){
		x->parent->color = 1;
		s->color = 0;
		if(x==x->parent->left)
			root = Left_Rotate(root, x->parent);
		else
			root = Right_Rotate(root, x->parent);
	}
	if(x==x->parent->left)
		s = x->parent->right;
	else
		s = x->parent->left;
	if(colorof(x->parent)==0 && colorof(s)==0 && colorof(s->left)==0 && colorof(s->right)==0){
		s->color = 1;
		root = RB_DeleteFixUP(root, x->parent);
	}
	else if(colorof(x->parent)==1 && colorof(s)==0 && colorof(s->left)==0 && colorof(s->right)==0){
		s->color = 1;
		x->parent->color = 0;
	}
	else{
		if(x==x->parent->left && colorof(s)==0 && colorof(s->left)==1 && colorof(s->right)==0){
			s->color = 1;
			if(s->left!=NULL)
				s->left->color = 0;
			root = Right_Rotate(root, s);
		}
		else if(x==x->parent->right && colorof(s)==0 && colorof(s->right)==1 && colorof(s->left)==0){
			s->color = 1;
			s->right->color = 0;
			root = Left_Rotate(root, s);
		}
		s->color = colorof(x->parent);
		x->parent->color = 0;
		if(x==x->parent->left){
			s->right->color = 0;
			root = Left_Rotate(root, x->parent);
		}
		else{
			s->left->color = 0;
			root = Right_Rotate(root, x->parent);
		}
	}
	root->color = 0;
	return root;
}

Node* Minimum(Node* x){
	while(x->left!=NULL)
		x = x->left;
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