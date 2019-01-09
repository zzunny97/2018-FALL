#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {false, true} bool;

typedef struct _Node{
	int key;
	struct _Node* next;
}Node;


int hashfunc_a(int key){
	return key % 7;
}

int hashfunc_b(int key){
	return key % 11;
}

int hashfunc_c(int key){
	return key % 13;
}

void table_a(int* keys){
	printf("hash function k mod 7\n");
	Node table[7];
	for(int i=0; i<7; i++)
		table[i].next = NULL;
	for(int i=0; i<50; i++){
		int index = hashfunc_a(keys[i]);
		Node* new = (Node*)malloc(sizeof(Node));
		new->key = keys[i];
		new->next = NULL;
		Node* cur = &table[index];
		if(cur->next!=NULL){
			new->next = cur->next;
			cur->next = new;
		} else{
			cur->next = new;
		}
	}
	for(int i=0; i<7; i++){
		printf("%d: ", i);
		Node* cur = &table[i];
		cur = cur->next;
		while(cur!=NULL){
			printf("%d ", cur->key);
			cur = cur->next;
		}
		printf("\n");
	}

	for(int i=1; i<=10; i++){
		Node* cur = &table[hashfunc_a(i)];
		if(cur->next->key==i){
			cur->next = cur->next->next;
		} else{
			cur = cur->next;
			while(cur!=NULL && cur->key!=i){
				if(cur->next==NULL){
					cur = cur->next;
				}
				else{
					if(cur->next->key==i){
						cur->next = cur->next->next;
						break;
					} else{
						cur = cur->next;
					}
				}
			}
		}
	}
	printf("\nafter deletion 1~10\n");
	for(int i=0; i<7; i++){
		printf("%d: ", i);
		Node* cur = &table[i];
		cur = cur->next;
		while(cur!=NULL){
			printf("%d ", cur->key);
			cur = cur->next;
		}
		printf("\n");
	}
	printf("\n\n");
}

void table_b(int* keys){
	printf("hash function k mod 11\n");
	Node table[11];
	for(int i=0; i<11; i++)
		table[i].next = NULL;
	for(int i=0; i<50; i++){
		int index = hashfunc_b(keys[i]);
		Node* new = (Node*)malloc(sizeof(Node));
		new->key = keys[i];
		new->next = NULL;
		Node* cur = &table[index];
		if(cur->next!=NULL){
			new->next = cur->next;
			cur->next = new;
		} else{
			cur->next = new;
		}
	}
	for(int i=0; i<11; i++){
		printf("%d: ", i);
		Node* cur = &table[i];
		cur = cur->next;
		while(cur!=NULL){
			printf("%d ", cur->key);
			cur = cur->next;
		}
		printf("\n");
	}
	printf("\nafter deletion 1~10\n");
	for(int i=1; i<=10; i++){
		Node* cur = &table[hashfunc_a(i)];
		if(cur->next->key==i){
			cur->next = cur->next->next;
		} else{
			cur = cur->next;
			while(cur!=NULL && cur->key!=i){
				if(cur->next==NULL){
					cur = cur->next;
				}
				else{
					if(cur->next->key==i){
						cur->next = cur->next->next;
						break;
					} else{
						cur = cur->next;
					}
				}
			}
		}
	}

	for(int i=0; i<11; i++){
		printf("%d: ", i);
		Node* cur = &table[i];
		cur = cur->next;
		while(cur!=NULL){
			printf("%d ", cur->key);
			cur = cur->next;
		}
		printf("\n");
	}
	printf("\n\n");
}

void table_c(int* keys){
	printf("hash function k mod 13\n");
	Node table[13];
	for(int i=0; i<13; i++)
		table[i].next = NULL;
	for(int i=0; i<50; i++){
		int index = hashfunc_c(keys[i]);
		Node* new = (Node*)malloc(sizeof(Node));
		new->key = keys[i];
		new->next = NULL;
		Node* cur = &table[index];
		if(cur->next!=NULL){
			new->next = cur->next;
			cur->next = new;
		} else{
			cur->next = new;
		}
	}
	for(int i=0; i<13; i++){
		printf("%d: ", i);
		Node* cur = &table[i];
		cur = cur->next;
		while(cur!=NULL){
			printf("%d ", cur->key);
			cur = cur->next;
		}
		printf("\n");
	}
	printf("\nafter deletion 1~10\n");
	for(int i=1; i<=10; i++){
		Node* cur = &table[hashfunc_a(i)];
		if(cur->next->key==i){
			cur->next = cur->next->next;
		} else{
			cur = cur->next;
			while(cur!=NULL && cur->key!=i){
				if(cur->next==NULL){
					cur = cur->next;
				}
				else{
					if(cur->next->key==i){
						cur->next = cur->next->next;
						break;
					} else{
						cur = cur->next;
					}
				}
			}
		}
	}

	for(int i=0; i<13; i++){
		printf("%d: ", i);
		Node* cur = &table[i];
		cur = cur->next;
		while(cur!=NULL){
			printf("%d ", cur->key);
			cur = cur->next;
		}
		printf("\n");
	}
	printf("\n\n");
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	bool check[50] = {false};
	int *keys = (int*)malloc(sizeof(int)*50);
	for(int i=0; i<50; i++){
		while(1){
			int candidate = rand()%100;
			if(check[candidate] == false){
				keys[i] = candidate;
				check[candidate] = true;
				break;
			} else{
				continue;
			}
		}
	}
	//construct table a
	table_a(keys);
	//construct table b
	table_b(keys);
	//construct table c
	table_c(keys);
	return 0;
}






