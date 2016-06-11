#ifndef DSAL1_H
#define DSAL1_H
#include"DSAL2.h"
#define TRUE 1
#define FALSE 0
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<exception>
using namespace std;

void initQueue(Queue *Q);
void destroyQueue(Queue *Q);
bool isQueueEmpty(Queue Q);
void enQueue(Queue *Q, QElemType e);
void deQueue(Queue *Q, QElemType *e);
void initStack(Stack *s);
void destroyStack(Stack *s);
void push(Stack *s, SElemType e);
void pop(Stack *s, SElemType *e);
bool isStackEmpty(Stack s);
int locateVex(ALGraph G, VertexType u);
char* getVexInfo(char *vexInfo, int index);
void createGraph(ALGraph *G, char* vexInfo);
void destroyGraph(ALGraph *G);
int FirstAdjVex(ALGraph G, VertexType v);
int NextAdjVex(ALGraph G, VertexType v, VertexType w);
void DFS(ALGraph G, int v, void(*Visit)(char*));
void DFSTraverse(ALGraph G, void(*Visit)(char*));
void BFSTraverse(ALGraph G, void(*Visit)(char*));
bool isConnected(ALGraph G, int v1, int v2);
void showDFSpanArc(ALGraph G, vector<int> intV);
void showBFSpanArc(ALGraph G, vector<int> intV);
void NonCurDFS(ALGraph G, int v, void(*Visit)(char*));
void nonCurDFSTraverse(ALGraph G, void(*Visit)(char*));
bool isNotFullVisited(ALGraph G, int v);

#endif