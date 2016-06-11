#include"DSAL1.h"
#include"DSAL2.h"

void initStack(Stack *s){ // 初始化一个栈
	(*s).base = (SElemType*)malloc((STACK_INIT_SIZE)*sizeof(SElemType));
	if (!((*s).base))
		exit(OVERFLOW);
	(*s).top = (*s).base;
	(*s).stackSize = STACK_INIT_SIZE;
}
void destroyStack(Stack *s){ // 销毁一个栈
	free((*s).base);
	(*s).base = NULL;
	(*s).top = NULL;
	(*s).stackSize = 0;
}
void push(Stack *s, SElemType e){ // 向栈里压入元素
	if ((*s).top - (*s).base >= (*s).stackSize){ //若栈满
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
void pop(Stack *s, SElemType *e){ // 从栈里弹出一个元素，并用e返回
	if ((*s).base == (*s).top)
		exit(OVERFLOW);
	(*s).top--;
	*e = *((*s).top);
	return;
}
bool isStackEmpty(Stack s){ // 判断栈是否为空
	if (s.base == s.top)
		return TRUE;
	else return FALSE;
}