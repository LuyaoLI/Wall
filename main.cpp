#include"DSAL1.h"
#include"DSAL2.h"

vector<int> DFSpanArc;
vector<int> BFSpanArc;

void Visit(char* v){
	for (int i = 0; v[i] != '\0'; i++){
		printf("%c", v[i]);
	}
	printf(" ");
}

int main(){
	ALGraph G;
	char* vexInfo = (char*)malloc(50 * sizeof(char));
	if (!vexInfo)
		exit(0);
	try{
		createGraph(&G, vexInfo);
		nonCurDFSTraverse(G, Visit);
		DFSTraverse(G, Visit);
		printf("\n相应生成树的边集为：");
		showDFSpanArc(G, DFSpanArc);
		printf("\n");
		BFSTraverse(G, Visit);
		printf("\n相应生成树的边集为：");
		showBFSpanArc(G, BFSpanArc);
		printf("\n");
		free(vexInfo);
		destroyGraph(&G);
	}
	catch (int a){
		if (a == 1)printf("\n\n顶点数为30以内的正整数！\n");
		if (a == 2)printf("\n\n您输入的边数无效！\n");
		if (a == 3)printf("\n\n您输入的结点数据有误，请重新检查后再输入！\n");
	}
	catch (exception e){
		printf("\n\n请按照程序提示重新进行输入！\n");
	}

	system("pause");
	return 0;
}