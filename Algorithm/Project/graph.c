#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUM 100
#define QMAX 100000

int selectable_path[MAXNUM][MAXNUM];//-> selectable[number][0] is the length of path (careful!!)

typedef struct list_node *list_ptr;
typedef struct list_node {//node about graph
   int city;
   int distance;
   int cost;
   int time;
   list_ptr next;
}list_node;

list_ptr graph[15] = { 0 };

typedef struct p_node {//node for BFS
   int num;
   int len;
   int path[MAXNUM];
   int visited[MAXNUM];
}p_node;

p_node queue[QMAX];
int first, last;

void graphadd(list_ptr *graph, int city, int distance, int cost, int time);
void BFS(int v, int des, list_ptr* graph);

//Functions
void graphadd(list_ptr *graph, int city, int distance, int cost, int time) {//insert graph

   list_ptr newNode = (list_ptr)malloc(sizeof(list_node));
   newNode->city = city;
   newNode->cost = cost;
   newNode->distance = distance;
   newNode->time = time;

   if (*graph != NULL) {
      newNode->next = *graph;
      *graph = newNode;
   }
   else {
      newNode->next = NULL;
      *graph = newNode;
   }
}

void BFS(int v, int des, list_ptr* graph) {//find route using BFS

   int y, sta = 0;
   p_node p;
   list_ptr w;

   //enqueue
   queue[first].num = v;
   queue[first].len = 1;
   queue[first].visited[v] = 1;
   queue[first++].path[0] = v;

   while (first != last)
   {
      //dequeue
      p = queue[last++];

      if (p.num != des)
      {
         for (w = graph[p.num]; w != NULL; w = w->next) {
            if (p.visited[w->city] == 0) {
               //enqueue
               queue[first].num = w->city;
               queue[first].len = p.len + 1;
               //copy current state
               for (y = 0; y < MAXNUM; y++)
               {
                  queue[first].visited[y] = p.visited[y];
                  queue[first].path[y] = p.path[y];
               }
               queue[first].visited[w->city] = 1;
               queue[first++].path[p.len] = w->city;
            }
         }
      }
      else
      {
         //insert in selectable_path
         selectable_path[sta][0] = p.len;
         for (y = 0; y < p.len; y++) {
            selectable_path[sta][y + 1] = p.path[y];
         }
         sta++;
      }

   }

}

void PrintBFS() {
   int number = 0, j;
   while (selectable_path[number][0] != 0)
   {
      int len = selectable_path[number][0], i;
      for (i = 1; i < len; i++)
         printf("%d -> ", selectable_path[number][i]);
      printf("%d\n", selectable_path[number][i]);
      number++;
   }

      for (int i = 0;i < MAXNUM;i++) {
         for (j = 0; j < MAXNUM; j++) {
            selectable_path[i][j] = 0;
         }
      }
}

int main(void) {

   /*graphadd(&graph[0], 1, 280, 308, 84);
   graphadd(&graph[0], 14, 775, 852.5, 232.5);
   graphadd(&graph[0], 2, 400, 440, 120);

   graphadd(&graph[1], 0, 280, 308, 84);
   graphadd(&graph[1], 2, 215, 236.5, 64.5);

   graphadd(&graph[2], 0, 400, 440, 120);
   graphadd(&graph[2], 1, 215, 236.5, 64.5);
   graphadd(&graph[2], 3, 380, 418, 114);

   graphadd(&graph[3], 2, 380, 418, 114);
   graphadd(&graph[3], 4, 475, 522.5, 142.5);
   graphadd(&graph[3], 5, 690, 759, 207);

   graphadd(&graph[4], 3, 475, 522.5, 142.5);
   graphadd(&graph[4], 5, 310, 341, 93);

   graphadd(&graph[5], 4, 310, 341, 93);
   graphadd(&graph[5], 3, 690, 759, 207);
   graphadd(&graph[5], 6, 750, 825, 225);

   graphadd(&graph[6], 5, 750, 825, 225);
   graphadd(&graph[6], 7, 420, 462, 126);
   graphadd(&graph[6], 8, 890, 979, 267);

   graphadd(&graph[7], 6, 420, 462, 126);
   graphadd(&graph[7], 8, 575, 632.5, 172.5);

   graphadd(&graph[8], 6, 890, 979, 267);
   graphadd(&graph[8], 7, 575, 632.5, 172.5);
   graphadd(&graph[8], 9, 465, 511.5, 139.5);

   graphadd(&graph[9], 8, 465, 511.5, 139.5);
   graphadd(&graph[9], 10, 480, 528, 144);
   graphadd(&graph[9], 11, 615, 676.5, 184.5);

   graphadd(&graph[10], 9, 480, 528, 144);
   graphadd(&graph[10], 11, 250, 275, 75);

   graphadd(&graph[11], 9, 615, 676.5, 184.5);
   graphadd(&graph[11], 10, 250, 275, 75);
   graphadd(&graph[11], 12, 870, 957, 261);

   graphadd(&graph[12], 11, 870, 957, 261);
   graphadd(&graph[12], 13, 350, 385, 105);
   graphadd(&graph[12], 14, 725, 797.5, 217.5);

   graphadd(&graph[13], 12, 350, 385, 105);
   graphadd(&graph[13], 14, 450, 495, 135);

   graphadd(&graph[14], 12, 725, 797.5, 217.5);
   graphadd(&graph[14], 13, 450, 495, 135);
   graphadd(&graph[14], 0, 775, 232.5, 852.5);*/


   graphadd(&graph[0], 1, 1, 1, 1);
   graphadd(&graph[0], 2, 1, 1, 1);
   graphadd(&graph[0], 3, 1, 1, 1);

   graphadd(&graph[1], 2, 1, 1, 1);

   graphadd(&graph[2], 3, 1, 1, 1);
   

   BFS(0, 3, graph);

   PrintBFS();

   return 0;
}