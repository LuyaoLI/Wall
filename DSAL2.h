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

typedef struct ArcNode{ // �߱��� 
	int adjvex; 
	struct ArcNode *nextarc;
}ArcNode; 

typedef struct{ // ͷ��� 
	VertexType data;
	ArcNode *firstarc; 
}VNode, AdjList[MAX_VERTEX_NUM]; 

typedef struct{ // ���ڽӱ�ʽ�洢��ͼ
	AdjList vertices;
	int vexnum;
	int arcnum;
}ALGraph;

typedef struct QNode{ // �����еĽ��
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct{ // ������
	QueuePtr front, rear;
}Queue;

typedef struct Stack{ // ջ
	SElemType *base;
	SElemType *top;
	int stackSize;
}Stack;
#endif