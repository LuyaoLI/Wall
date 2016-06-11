#include"DSAL1.h"
#include"DSAL2.h"

void initStack(Stack *s){ // ��ʼ��һ��ջ
	(*s).base = (SElemType*)malloc((STACK_INIT_SIZE)*sizeof(SElemType));
	if (!((*s).base))
		exit(OVERFLOW);
	(*s).top = (*s).base;
	(*s).stackSize = STACK_INIT_SIZE;
}
void destroyStack(Stack *s){ // ����һ��ջ
	free((*s).base);
	(*s).base = NULL;
	(*s).top = NULL;
	(*s).stackSize = 0;
}
void push(Stack *s, SElemType e){ // ��ջ��ѹ��Ԫ��
	if ((*s).top - (*s).base >= (*s).stackSize){ //��ջ��
		(*s).base = (SElemType*)realloc((*s).base, ((*s).stackSize + STACK_INCREMENT)*sizeof(SElemType));
		if (!((*s).base))
			exit(OVERFLOW);
		(*s).top = (*s).base + (*s).stackSize;
		(*s).stackSize += STACK_INCREMENT;
	}
	*((*s).top) = e;
	(*s).top++;
	return;
}
void pop(Stack *s, SElemType *e){ // ��ջ�ﵯ��һ��Ԫ�أ�����e����
	if ((*s).base == (*s).top)
		exit(OVERFLOW);
	(*s).top--;
	*e = *((*s).top);
	return;
}
bool isStackEmpty(Stack s){ // �ж�ջ�Ƿ�Ϊ��
	if (s.base == s.top)
		return TRUE;
	else return FALSE;
}