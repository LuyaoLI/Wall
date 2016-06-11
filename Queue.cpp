#include"DSAL1.h"
#include"DSAL2.h"

void initQueue(Queue *Q){ // 队列初始化
	(*Q).front = (*Q).rear = (QueuePtr)malloc(sizeof(QNode));
	if (!(*Q).front)
		exit(OVERFLOW);
	(*Q).front->next = NULL;
}
void destroyQueue(Queue *Q){ // 销毁队列
	while ((*Q).front){
		(*Q).rear = (*Q).front->next;
		free((*Q).front);
		(*Q).front = (*Q).rear;
	}
	(*Q).front = (*Q).rear = NULL;
}
bool isQueueEmpty(Queue Q){ // 判断队列Q是否为空
	if (Q.front->next == NULL)
		return TRUE;
	else
		return FALSE;
}
void enQueue(Queue *Q, QElemType e){ // 队列尾部插入元素e
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	(*Q).rear->next = p;
	(*Q).rear = p;
}
void deQueue(Queue *Q, QElemType *e){ // 删除队列的队头元素，用e返回其值
	QueuePtr p;
	if ((*Q).front == (*Q).rear)
		exit(OVERFLOW);
	p = (*Q).front->next;
	*e = p->data;
	(*Q).front->next = p->next;
	if ((*Q).rear == p) // 若队列删除后为空
		(*Q).rear = (*Q).front;
	free(p);
}