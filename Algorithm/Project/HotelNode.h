#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//이거 100개의 노드 가진 100개의 트리를 짜야함.
typedef struct Node{
	int color;	//1==red, 0==black
	struct Node* left;
	struct Node* right;
	struct Node* parent;
	int key; //hotel_num
	int price; //price: 100~999
} HotelNode;

HotelNode* Hotel_Left_Rotate(HotelNode* root, HotelNode* x);
HotelNode* Hotel_Right_Rotate(HotelNode* root, HotelNode* x);
HotelNode* Hotel_RB_Insert(HotelNode* root, int key);
HotelNode* Hotel_RB_InsertFixUP(HotelNode* root, HotelNode* z);
HotelNode* Hotel_Minimum(HotelNode* x);
HotelNode* Hotel_Successor(HotelNode* x);
HotelNode* Hotel_RB_Delete(HotelNode* root, int key);
HotelNode* Hotel_RB_DeleteFixUP(HotelNode* root, HotelNode* x);
void Hotel_Print_RBTree(HotelNode* root);
HotelNode* Hotel_Search(HotelNode* root, int key);
int Hotel_colorof(HotelNode* n);
int Hotel_Height(HotelNode* root);