#include"DSAL1.h"
#include"DSAL2.h"

void initQueue(Queue *Q){ // ���г�ʼ��
	(*Q).front = (*Q).rear = (QueuePtr)malloc(sizeof(QNode));
	if (!(*Q).front)
		exit(OVERFLOW);
	(*Q).front->next = NULL;
}
void destroyQueue(Queue *Q){ // ���ٶ���
	while ((*Q).front){
		(*Q).rear = (*Q).front->next;
		free((*Q).front);
		(*Q).front = (*Q).rear;
	}
	(*Q).front = (*Q).rear = NULL;
}
bool isQueueEmpty(Queue Q){ // �ж϶���Q�Ƿ�Ϊ��
	if (Q.front->next == NULL)
		return TRUE;
	else
		return FALSE;
}
void enQueue(Queue *Q, QElemType e){ // ����β������Ԫ��e
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	(*Q).rear->next = p;
	(*Q).rear = p;
}
void deQueue(Queue *Q, QElemType *e){ // ɾ�����еĶ�ͷԪ�أ���e������ֵ
	QueuePtr p;
	if ((*Q).front == (*Q).rear)
		exit(OVERFLOW);
	p = (*Q).front->next;
	*e = p->data;
	(*Q).front->next = p->next;
	if ((*Q).rear == p) // ������ɾ����Ϊ��
		(*Q).rear = (*Q).front;
	free(p);
}