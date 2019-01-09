#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "HotelNode.h"

#define new_price rand()%900+100

typedef enum {false, true} bool;


int main(int argc, char const *argv[])
{
	srand(time(NULL));

	HotelNode* root[100];

	for(int i=0; i<100; i++){
		root[i] = (HotelNode*)malloc(sizeof(HotelNode));
		root[i]->key = -1;
		root[i]->price = -1;
		root[i]->left = NULL;
		root[i]->right = NULL;
		root[i]->parent = NULL;
		root[i]->color = 1;
	}
	
	for (int i = 0; i < 100; ++i)
	{
		printf("\n---------city %d--------\n", i);
		for (int j = 0; j < 100; ++j)
		{	
			root[i] = Hotel_RB_Insert(root[i], j);
			Hotel_Print_RBTree(root[i]); printf("\n");
		}
	}
	

	return 0;
}

int Hotel_Height(HotelNode* root){
	if(root==NULL)
		return -1;
	int left_height = Hotel_Height(root->left);
	int right_height = Hotel_Height(root->right);

	if(left_height > right_height)
		return left_height+1;
	else
		return right_height+1;
}

HotelNode* Hotel_Search(HotelNode* root, int key){
	if (root==NULL||root->key==key) return root;
	else if (root->key>key)
		return Hotel_Search(root->left, key);
	else
		return Hotel_Search(root->right, key);
}


void Hotel_Print_RBTree(HotelNode* root){
	if (root != NULL){
		Hotel_Print_RBTree(root->left);
		if(root->color==0){
			printf("%d(black) ", root->key); printf("price=%d\t", root->price);
		}
		else{
			printf("%d(red) ", root->key); printf("price=%d\t", root->price);
		}
		Hotel_Print_RBTree(root->right);
	}
}


HotelNode* Hotel_Left_Rotate(HotelNode* root, HotelNode* x){
	HotelNode* y = x->right;
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

HotelNode* Hotel_Right_Rotate(HotelNode* root, HotelNode* x){
	HotelNode* y = x->left;
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

HotelNode* Hotel_RB_Insert(HotelNode* root, int key){
	if (root->key == -1){
		root->key = key;
		root->price = new_price;
		root->color = 0;
		return root;
	}
	
	HotelNode* new = (HotelNode*)malloc(sizeof(HotelNode));
	new->key = key;
	new->price = new_price;
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	new->color = 1;

	HotelNode* y = NULL;
	HotelNode* x = root;
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

	root = Hotel_RB_InsertFixUP(root, new);
	return root;

}

HotelNode* Hotel_RB_InsertFixUP(HotelNode* root, HotelNode* z){
	HotelNode* p = NULL;
	HotelNode* g = NULL;
	while(z!= root && z->color==1 && z->parent!=NULL && z->parent->color==1 && z->parent->parent!=NULL){
		HotelNode* uncle = NULL;
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
					root = Hotel_Left_Rotate(root, p);
					z = p;
					p = z->parent;
				}
				root = Hotel_Right_Rotate(root, g);
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
					root = Hotel_Right_Rotate(root, p);
					z = p;
					p = z->parent;
				}
				root = Hotel_Left_Rotate(root, g);
				p->color = 0;
				g->color = 1;
				z = p;
			}
		}
	}
	root->color = 0;
	return root;
}

HotelNode* Hotel_RB_Delete(HotelNode* root, int key){
	if(root->key==key && root->left==NULL && root->right==NULL)
		return NULL;
	HotelNode* x = Hotel_Search(root, key);
	if(x->left!=NULL && x->right!=NULL){
		HotelNode* y = x->left;
		while(y->right!=NULL)
			y = y->right;
		x->key = y->key;
		x = y;
	}
	HotelNode* z;
	if(x->right==NULL)
		z = x->left;
	else
		z = x->right;
	if(x->color==0){
		x->color = Hotel_colorof(z);
		root = Hotel_RB_DeleteFixUP(root, x);
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

int Hotel_colorof(HotelNode* n){
	return n==NULL ? 0 : n->color;
}

HotelNode* Hotel_RB_DeleteFixUP(HotelNode* root, HotelNode* x){
	if(x->parent==NULL)
		return root;
	HotelNode* s;
	if(x==x->parent->left)
		s = x->parent->right;
	else
		s = x->parent->left;
	if(Hotel_colorof(s)==1){
		x->parent->color = 1;
		s->color = 0;
		if(x==x->parent->left)
			root = Hotel_Left_Rotate(root, x->parent);
		else
			root = Hotel_Right_Rotate(root, x->parent);
	}
	if(x==x->parent->left)
		s = x->parent->right;
	else
		s = x->parent->left;
	if(Hotel_colorof(x->parent)==0 && Hotel_colorof(s)==0 && Hotel_colorof(s->left)==0 && Hotel_colorof(s->right)==0){
		s->color = 1;
		root = Hotel_RB_DeleteFixUP(root, x->parent);
	}
	else if(Hotel_colorof(x->parent)==1 && Hotel_colorof(s)==0 && Hotel_colorof(s->left)==0 && Hotel_colorof(s->right)==0){
		s->color = 1;
		x->parent->color = 0;
	}
	else{
		if(x==x->parent->left && Hotel_colorof(s)==0 && Hotel_colorof(s->left)==1 && Hotel_colorof(s->right)==0){
			s->color = 1;
			if(s->left!=NULL)
				s->left->color = 0;
			root = Hotel_Right_Rotate(root, s);
		}
		else if(x==x->parent->right && Hotel_colorof(s)==0 && Hotel_colorof(s->right)==1 && Hotel_colorof(s->left)==0){
			s->color = 1;
			s->right->color = 0;
			root = Hotel_Left_Rotate(root, s);
		}
		s->color = Hotel_colorof(x->parent);
		x->parent->color = 0;
		if(x==x->parent->left){
			s->right->color = 0;
			root = Hotel_Left_Rotate(root, x->parent);
		}
		else{
			s->left->color = 0;
			root = Hotel_Right_Rotate(root, x->parent);
		}
	}
	root->color = 0;
	return root;
}

HotelNode* Hotel_Minimum(HotelNode* x){
	while(x->left!=NULL)
		x = x->left;
	return x;
}

HotelNode* Hotel_Successor(HotelNode* x){
	if(x->right!=NULL){
		return Hotel_Minimum(x->right);
	} else{
		HotelNode* y = x->parent;
		while(y!=NULL&&x==y->right){
			x = y;
			y = y->parent;
		}
		return y;
	}
}