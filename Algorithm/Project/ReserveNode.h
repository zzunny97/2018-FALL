#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct list{
	int period;
	int price;
	int city_num;
	int hotel_num;	
	struct list* next;
} InfoNode;

typedef struct Node{
	int color;	//1==red, 0==black
	struct Node* left;
	struct Node* right;
	struct Node* parent;
	int key; //customer_id
	InfoNode* reserve_list;
} ReserveNode;

ReserveNode* Reserve_Left_Rotate(ReserveNode* root, ReserveNode* x);
ReserveNode* Reserve_Right_Rotate(ReserveNode* root, ReserveNode* x);
ReserveNode* Reserve_RB_Insert(ReserveNode* root, int key, InfoNode* info);
ReserveNode* Reserve_RB_InsertFixUP(ReserveNode* root, ReserveNode* z);
ReserveNode* Reserve_Minimum(ReserveNode* x);
ReserveNode* Reserve_Successor(ReserveNode* x);
ReserveNode* Reserve_RB_Delete(ReserveNode* root, int key);
ReserveNode* Reserve_RB_DeleteFixUP(ReserveNode* root, ReserveNode* x);
void Reserve_Print_RBTree(ReserveNode* root);
ReserveNode* Reserve_Search(ReserveNode* root, int key);
int Reserve_colorof(ReserveNode* n);
int Reserve_Height(ReserveNode* root);
