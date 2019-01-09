#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ReserveNode.h"

typedef enum {false, true} bool;



int main(int argc, char const *argv[])
{
	srand(time(NULL));

	ReserveNode* root = (ReserveNode*)malloc(sizeof(ReserveNode));
	root->key = -1;
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
	root->reserve_list = NULL;
	root->color = 1;
	for(int i=0; i<3; i++){
		InfoNode* info = (InfoNode*)malloc(sizeof(InfoNode));
		info->period = i;
		info->price = i;
		info->city_num = i;
		info->hotel_num = i;
		info->next = NULL;
		root = Reserve_RB_Insert(root, i, info);
		Reserve_Print_RBTree(root); printf("\n");
	}
	InfoNode* info = (InfoNode*)malloc(sizeof(InfoNode));
	info->period = 12;
	info->price = 12;
	info->city_num = 12;
	info->hotel_num = 12;
	info->next = NULL;
	root = Reserve_RB_Insert(root, 0, info);
	Reserve_Print_RBTree(root); printf("\n");
	

	return 0;
}

int Reserve_Height(ReserveNode* root){
	if(root==NULL)
		return -1;
	int left_height = Reserve_Height(root->left);
	int right_height = Reserve_Height(root->right);

	if(left_height > right_height)
		return left_height+1;
	else
		return right_height+1;
}

ReserveNode* Reserve_Search(ReserveNode* root, int key){
	if (root==NULL||root->key==key) return root;
	else if (root->key>key)
		return Reserve_Search(root->left, key);
	else
		return Reserve_Search(root->right, key);
}


void Reserve_Print_RBTree(ReserveNode* root){
	if (root != NULL){
		Reserve_Print_RBTree(root->left);
		if(root->color==0)
			printf("%d(black) ", root->key);
		else
			printf("%d(red) ", root->key);
		InfoNode* cur = root->reserve_list;
		while(cur!=NULL){
			printf("period = %d ", cur->period);
			printf("price = %d ", cur->price);
			printf("city_num = %d ", cur->city_num);
			printf("hotel_num = %d\t", cur->hotel_num);
			cur = cur->next;
		}
		Reserve_Print_RBTree(root->right);
	}
}


ReserveNode* Reserve_Left_Rotate(ReserveNode* root, ReserveNode* x){
	ReserveNode* y = x->right;
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

ReserveNode* Reserve_Right_Rotate(ReserveNode* root, ReserveNode* x){
	ReserveNode* y = x->left;
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

ReserveNode* Reserve_RB_Insert(ReserveNode* root, int key, InfoNode* info){
	if (root->key == -1){
		root->key = key;
		root->color = 0;
		root->reserve_list = (InfoNode*)malloc(sizeof(InfoNode));
		root->reserve_list->period = info->period;
		root->reserve_list->price = info->price;
		root->reserve_list->city_num = info->city_num;
		root->reserve_list->hotel_num = info->hotel_num;
		root->reserve_list->next = NULL;
		return root;
	}
	
	ReserveNode* cur = Reserve_Search(root, key);
	if(cur != NULL){
		//insert info
		InfoNode* cur2 = cur->reserve_list;
		while(cur2->next!=NULL) cur2 = cur2->next;
		cur2->next = info;
		return root;
	}

	ReserveNode* new = (ReserveNode*)malloc(sizeof(ReserveNode));
	new->key = key;
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	new->color = 1;
	new->reserve_list = (InfoNode*)malloc(sizeof(InfoNode));
	new->reserve_list->period = info->period;
	new->reserve_list->price = info->price;
	new->reserve_list->city_num = info->city_num;
	new->reserve_list->hotel_num = info->hotel_num;
	new->reserve_list->next = NULL;


	ReserveNode* y = NULL;
	ReserveNode* x = root;
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
	root = Reserve_RB_InsertFixUP(root, new);
	return root;

}

ReserveNode* Reserve_RB_InsertFixUP(ReserveNode* root, ReserveNode* z){
	ReserveNode* p = NULL;
	ReserveNode* g = NULL;
	while(z!= root && z->color==1 && z->parent!=NULL && z->parent->color==1 && z->parent->parent!=NULL){
		ReserveNode* uncle = NULL;
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
					root = Reserve_Left_Rotate(root, p);
					z = p;
					p = z->parent;
				}
				root = Reserve_Right_Rotate(root, g);
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
					root = Reserve_Right_Rotate(root, p);
					z = p;
					p = z->parent;
				}
				root = Reserve_Left_Rotate(root, g);
				p->color = 0;
				g->color = 1;
				z = p;
			}
		}
	}
	root->color = 0;
	return root;
}

ReserveNode* Reserve_RB_Delete(ReserveNode* root, int key){
	if(Reserve_Search(root, key)==NULL){
		printf("The key %d doesn't exist in the tree\n", key);
		return root;
	}
	if(root->key==key && root->left==NULL && root->right==NULL)
		return NULL;
	ReserveNode* x = Reserve_Search(root, key);
	if(x->left!=NULL && x->right!=NULL){
		ReserveNode* y = x->left;
		while(y->right!=NULL)
			y = y->right;
		x->key = y->key;
		x = y;
	}
	ReserveNode* z;
	if(x->right==NULL)
		z = x->left;
	else
		z = x->right;
	if(x->color==0){
		x->color = Reserve_colorof(z);
		root = Reserve_RB_DeleteFixUP(root, x);
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

int Reserve_colorof(ReserveNode* n){
	return n==NULL ? 0 : n->color;
}

ReserveNode* Reserve_RB_DeleteFixUP(ReserveNode* root, ReserveNode* x){
	if(x->parent==NULL)
		return root;
	ReserveNode* s;
	if(x==x->parent->left)
		s = x->parent->right;
	else
		s = x->parent->left;
	if(Reserve_colorof(s)==1){
		x->parent->color = 1;
		s->color = 0;
		if(x==x->parent->left)
			root = Reserve_Left_Rotate(root, x->parent);
		else
			root = Reserve_Right_Rotate(root, x->parent);
	}
	if(x==x->parent->left)
		s = x->parent->right;
	else
		s = x->parent->left;
	if(Reserve_colorof(x->parent)==0 && Reserve_colorof(s)==0 && Reserve_colorof(s->left)==0 && Reserve_colorof(s->right)==0){
		s->color = 1;
		root = Reserve_RB_DeleteFixUP(root, x->parent);
	}
	else if(Reserve_colorof(x->parent)==1 && Reserve_colorof(s)==0 && Reserve_colorof(s->left)==0 && Reserve_colorof(s->right)==0){
		s->color = 1;
		x->parent->color = 0;
	}
	else{
		if(x==x->parent->left && Reserve_colorof(s)==0 && Reserve_colorof(s->left)==1 && Reserve_colorof(s->right)==0){
			s->color = 1;
			if(s->left!=NULL)
				s->left->color = 0;
			root = Reserve_Right_Rotate(root, s);
		}
		else if(x==x->parent->right && Reserve_colorof(s)==0 && Reserve_colorof(s->right)==1 && Reserve_colorof(s->left)==0){
			s->color = 1;
			s->right->color = 0;
			root = Reserve_Left_Rotate(root, s);
		}
		s->color = Reserve_colorof(x->parent);
		x->parent->color = 0;
		if(x==x->parent->left){
			s->right->color = 0;
			root = Reserve_Left_Rotate(root, x->parent);
		}
		else{
			s->left->color = 0;
			root = Reserve_Right_Rotate(root, x->parent);
		}
	}
	root->color = 0;
	return root;
}

ReserveNode* Reserve_Minimum(ReserveNode* x){
	while(x->left!=NULL)
		x = x->left;
	return x;
}

ReserveNode* Reserve_Successor(ReserveNode* x){
	if(x->right!=NULL){
		return Reserve_Minimum(x->right);
	} else{
		ReserveNode* y = x->parent;
		while(y!=NULL&&x==y->right){
			x = y;
			y = y->parent;
		}
		return y;
	}
}