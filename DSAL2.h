#ifndef DSAL2_H
#define DSAL2_H
#include"DSAL2.h"
typedef int InfoType;
typedef int QElemType;
typedef int SElemType;
typedef char VertexType[10];
#define MAX_VERTEX_NUM 30
#define STACK_INIT_SIZE 20
#define STACK_INCREMENT 5

typedef struct ArcNode{ // 边表结点 
	int adjvex; 
	struct ArcNode *nextarc;
}ArcNode; 

typedef struct{ // 头结点 
	VertexType data;
	ArcNode *firstarc; 
}VNode, AdjList[MAX_VERTEX_NUM]; 

typedef struct{ // 以邻接表方式存储的图
	AdjList vertices;
	int vexnum;
	int arcnum;
}ALGraph;

typedef struct QNode{ // 链队列的结点
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct{ // 链队列
	QueuePtr front, rear;
}Queue;

typedef struct Stack{ // 栈
	SElemType *base;
	SElemType *top;
	int stackSize;
}Stack;
#endif