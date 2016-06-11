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
		printf("\n��Ӧ�������ı߼�Ϊ��");
		showDFSpanArc(G, DFSpanArc);
		printf("\n");
		BFSTraverse(G, Visit);
		printf("\n��Ӧ�������ı߼�Ϊ��");
		showBFSpanArc(G, BFSpanArc);
		printf("\n");
		free(vexInfo);
		destroyGraph(&G);
	}
	catch (int a){
		if (a == 1)printf("\n\n������Ϊ30���ڵ���������\n");
		if (a == 2)printf("\n\n������ı�����Ч��\n");
		if (a == 3)printf("\n\n������Ľ���������������¼��������룡\n");
	}
	catch (exception e){
		printf("\n\n�밴�ճ�����ʾ���½������룡\n");
	}

	system("pause");
	return 0;
}