#include"DSAL1.h"
#include"DSAL2.h"

bool visited[MAX_VERTEX_NUM];

int locateVex(ALGraph G, VertexType u){ // ���ض���u��ͼG�е����
	for (int i = 0; i < G.vexnum; i++){
		if (strcmp(u, G.vertices[i].data) == 0)
			return i;
	}
	return -1;
}
char* getVexInfo(char *vexInfo, int index){ // �õ�����߶���ָ���±��еĶ���ֵ
	char tmp[10];
	int end;
	if (index == 0){
		for (int i = 1, j = 0; vexInfo[i] != ',';i++, j++){
			tmp[j] = vexInfo[i];
			end = j;
		}
		tmp[end + 1] = '\0';
		char *rtmp = (char*)malloc((end + 1)*sizeof(char));  // ��ʡ�����ڴ濪֧
		strcpy(rtmp, tmp);
		return rtmp;
	}
	else {
		int colnum = 0;
		while (vexInfo[colnum] != ',')
			colnum++;
		for (int i = colnum + 1, j = 0; vexInfo[i] != ')'; i++, j++){
			tmp[j] = vexInfo[i];
			end = j;
		}
		tmp[end + 1] = '\0';
		char *rtmp = (char*)malloc((end + 1)*sizeof(char));
		strcpy(rtmp, tmp);
		return rtmp;
	}
}
void createGraph(ALGraph *G, char* vexInfo){ // ��ʼ��������һ�����ڽӱ�ʽ�洢��ͼ
	char vexChar[10];
	ArcNode *tnode;
	printf("********************����һ������ͼ********************");
	printf("\nͼ�������Ϊ(������һ��С��30��������) : "); // ��ͼ���г�ʼ��
	scanf("%d", &(*G).vexnum);
	if ((*G).vexnum <= 0 || (*G).vexnum > 30)
		throw 1;
	printf("ͼ�бߵ�����Ϊ(������һ������) : ");
	scanf("%d", &(*G).arcnum);
	if ((*G).arcnum < 0 || (*G).arcnum>((*G).vexnum * ((*G).vexnum - 1) / 2))
		throw 2;
	printf("\n\n*****************������ͼ�ж���ֵ********************");
	printf("\n");
	for (int i = 0; i < (*G).vexnum; i++){ // ��ʼ��ͷ����
		printf("��%d�������ֵΪ :", i + 1);
		scanf("%s", vexChar);
		strcpy((*G).vertices[i].data, vexChar);
		(*G).vertices[i].firstarc = NULL;
	}
	printf("\n\n************������ͼ�б߶�(��ʽΪ��a, b))**************");
	getchar();
	printf("\n");
	for (int i = 0; i < (*G).arcnum; i++){
		printf("��%d���߶�Ϊ :", i + 1);
		gets(vexInfo);
		int arcIndex1 = locateVex(*G, getVexInfo(vexInfo, 0));
		int arcIndex2 = locateVex(*G, getVexInfo(vexInfo, 1));
		if (arcIndex1 == -1 || arcIndex2 == -1)
			throw 3;
		ArcNode *arcnode1 = (ArcNode*)malloc(sizeof(ArcNode));
		(*arcnode1).adjvex = arcIndex2;
		(*arcnode1).nextarc = NULL;
		if ((*G).vertices[arcIndex1].firstarc == NULL){ // �����ͷ��㻹δ���ӱ߱�
			(*G).vertices[arcIndex1].firstarc = arcnode1;
		}
		else {  // ��������
			tnode = (*G).vertices[arcIndex1].firstarc;
			while (tnode->nextarc){
				tnode = tnode->nextarc;
			}
			tnode->nextarc = arcnode1;
		}
		ArcNode *arcnode2 = (ArcNode*)malloc(sizeof(ArcNode));
		(*arcnode2).adjvex = arcIndex1;
		(*arcnode2).nextarc = NULL;
		if ((*G).vertices[arcIndex2].firstarc == NULL){
			(*G).vertices[arcIndex2].firstarc = arcnode2;
		}
		else {
			tnode = (*G).vertices[arcIndex2].firstarc;
			while (tnode->nextarc){
				tnode = tnode->nextarc;
			}
			tnode->nextarc = arcnode2;
		}
	}
}
void destroyGraph(ALGraph *G){ // ����һ�����ڽӱ�ʽ�洢��ͼ
	ArcNode *tnode, *tdnode;
	for (int i = 0; i < (*G).vexnum; ++i){
		tnode = (*G).vertices[i].firstarc;
		while (tnode){
			while (tnode ->nextarc){
				tdnode = tnode;
				tnode = tnode->nextarc;
				free(tdnode);
			}
			free(tnode);
			(*G).vertices[i].firstarc = NULL;
			break;
		}
	}
	(*G).vexnum = 0; // ������Ϊ0 
	(*G).arcnum = 0; // ����Ϊ0 
}
int FirstAdjVex(ALGraph G, VertexType v){ // �����ڽӱ��ж���v�ĵ�һ���ٽӶ������ţ��������ڣ��򷵻�-1
	int v1 = locateVex(G, v); // �ҵ�����v��ͼ�е���� 
	ArcNode* p = G.vertices[v1].firstarc;
	if (p)
		return p->adjvex;
	else
		return -1;
}
int NextAdjVex(ALGraph G, VertexType v, VertexType w){ // ���ض���v��(�����w��)��һ���ڽӶ�������
	                                                   // �������ڣ�w��v�����һ���ڽӵ㣩���򷵻�-1
	int v1 = locateVex(G, v);
	int v2 = locateVex(G, w);
	ArcNode *tnode = G.vertices[v1].firstarc;
	while (tnode && tnode->adjvex != v2){ // ��tnodeָ�򶥵�v���������ڽӶ���Ϊw�Ľ��
		tnode = tnode->nextarc;
	}
	if (!tnode || !tnode->nextarc) // wû�ҵ�w��w�����һ���ڽӵ�
		return -1;
	else
		return tnode->nextarc->adjvex; // ����v��(�����w��)��һ���ڽӶ�������
}
void DFS(ALGraph G, int v, void(*Visit)(char*)){ // ������ȱ����㷨���ݹ��㷨��
	extern vector<int> DFSpanArc;
	visited[v] = TRUE; 
	Visit(G.vertices[v].data);
	DFSpanArc.push_back(v);
	for (int w = FirstAdjVex(G, G.vertices[v].data); w >= 0; w = NextAdjVex(G, G.vertices[v].data, G.vertices[w].data))
		if (!visited[w]){
		DFS(G, w, Visit); // ��v����δ���ʵ��ڽӵ�w�ݹ����DFS 
		}
}
void DFSTraverse(ALGraph G, void(*Visit)(char*)){ // ������ͼ����������ȱ������ݹ��㷨��
	extern vector<int> DFSpanArc;
	char u[10];
	DFSpanArc.clear();
	for (int v = 0; v<G.vexnum; v++) // ���ʱ�־�����ʼ��
		visited[v] = FALSE;
	printf("\n\n*******************��ͼ����DFS�������ݹ飩*******************\n��ָ��DFS��ʼ�Ľ�㣺 ");
	scanf("%s", u);
	if (locateVex(G, u) == -1)
		throw 3;
	printf("��ǰDFS�½���������Ϊ��");
	if (G.vexnum == 1)
		printf("%s", G.vertices[0].data);
	else {
		for (int v = locateVex(G, u); v < G.vexnum; v++)
			if (!visited[v])
				DFS(G, v, Visit);
		for (int v = 0; v<G.vexnum; v++) // �û��������ȫ��ͨͼʱ��ʣ����ı���
			if (!visited[v])
				DFS(G, v, Visit);
	}
}
bool isNotFullVisited(ALGraph G, int v){ // ��������ջ���зǵݹ�������ȱ���ʱ�жϵ�ǰ������������Ƿ��Ѿ���ȫ������
	ArcNode * p = G.vertices[v].firstarc;
	while (p){
		if (!visited[p->adjvex]){
			return TRUE;
		}
		else p = p->nextarc;
	}
	return FALSE;
}
void nonCurDFSTraverse(ALGraph G, void(*Visit)(char*)){ // ������ͼ����������ȱ������ǵݹ��㷨��
	int w, v;
	char u[10];
	Stack s;
	initStack(&s);
	for (int v = 0; v<G.vexnum; v++) // ���ʱ�־�����ʼ��
		visited[v] = FALSE;
	printf("\n\n*******************��ͼ����DFS�������ǵݹ飩*******************\n��ָ��DFS��ʼ�Ľ�㣺 ");
	scanf("%s", u);
	printf("��ǰDFS�½���������Ϊ��");
	v = locateVex(G, u);
	if (v == -1)
		throw 3;
	if (G.vexnum == 1)
		printf("%s", G.vertices[0].data);
	else{
		visited[v] = TRUE;
		Visit(G.vertices[v].data);
		push(&s, v);
		while (!isStackEmpty(s)){
			pop(&s, &v);
			if (isNotFullVisited(G, v)){
				w = FirstAdjVex(G, G.vertices[v].data);
				while (visited[w]){
					ArcNode *p = G.vertices[v].firstarc;
					p = p->nextarc;
					w = p->adjvex;
				}
				Visit(G.vertices[w].data);
				push(&s, v);
				push(&s, w);
			}
		}
	}
}

void BFSTraverse(ALGraph G, void(*Visit)(char*)){ // ��������ȷǵݹ����ͼ
	extern vector<int> BFSpanArc;
	int u;
	char w[10];
	Queue Q;
	initQueue(&Q);       // ��ʼ��
	BFSpanArc.clear(); 
	for (int v = 0; v<G.vexnum; v++)
		visited[v] = FALSE;
	printf("\n\n*******************��ͼ����BFS����*******************\n��ָ��BFS��ʼ�Ľ�㣺 ");
	scanf("%s", w);
	if (locateVex(G, w) == -1)
		throw 3;
	printf("��ǰBFS�½���������Ϊ��");
	if (G.vexnum == 1)
		printf("%s", G.vertices[0].data);
	else{
		for (int v = locateVex(G, w); v < G.vexnum; v++){
			if (!visited[v]){
				visited[v] = TRUE;
				Visit(G.vertices[v].data);
				BFSpanArc.push_back(v);
				enQueue(&Q, v); // v����� 
				while (!isQueueEmpty(Q)){ // ���зǿ�
					deQueue(&Q, &u); // ������ͷԪ��
					for (int w = FirstAdjVex(G, G.vertices[u].data); w >= 0; w = NextAdjVex(G, G.vertices[u].data, G.vertices[w].data)){
						if (!visited[w]){
							visited[w] = TRUE;
							Visit(G.vertices[w].data);
							BFSpanArc.push_back(w);
							enQueue(&Q, w); // w�����
						}
					}
				}
			}
		}
		for (int v = 0; v < G.vexnum; v++){ // ���û�������Ĳ���ȫ��ͨͼ��ʣ����Ĵ���
			if (!visited[v]){
				visited[v] = TRUE;
				Visit(G.vertices[v].data);
				BFSpanArc.push_back(v);
				enQueue(&Q, v); // v����� 
				while (!isQueueEmpty(Q)){ // ���зǿ�
					deQueue(&Q, &u); // ������ͷԪ��
					for (int w = FirstAdjVex(G, G.vertices[u].data); w >= 0; w = NextAdjVex(G, G.vertices[u].data, G.vertices[w].data)){
						if (!visited[w]){
							visited[w] = TRUE;
							Visit(G.vertices[w].data);
							BFSpanArc.push_back(w);
							enQueue(&Q, w); // w�����
						}
					}
				}
			}
		}
	}
}
bool isConnected(ALGraph G, int v1, int v2){ // �ж϶������Ϊv1��v2�ĵ��Ƿ��б�����
	ArcNode *tnode = G.vertices[v1].firstarc;
	while (tnode){
		if (tnode->adjvex == v2)
			return TRUE;
		else tnode = tnode->nextarc;
	}
	return FALSE;
}
void showDFSpanArc(ALGraph G, extern vector<int> intV){ // ��ӡ��DFS�������ı߼�
	if (G.vexnum == 1)printf("������Ϊһ�����ڵ�%s\n", G.vertices[0].data);
	else{
		printf("(%s, %s)", G.vertices[intV.at(0)].data, G.vertices[intV.at(1)].data);
		for (int i = 2; i < intV.size(); i++){
			int k = i - 1;
			while (!isConnected(G, intV.at(k), intV.at(i))){
				k = k - 1;
			}
			printf("(%s, %s)", G.vertices[intV.at(k)].data, G.vertices[intV.at(i)].data);
		}
	}
}
void showBFSpanArc(ALGraph G, extern vector<int> intV){ // ��ӡ��BFS�������ı߼�
	if (G.vexnum == 1)printf("������Ϊһ�����ڵ�%s\n", G.vertices[0].data);
	else {
		int k = 0;
		for (int i = 1; i < intV.size(); i++){
			if (isConnected(G, intV.at(k), intV.at(i))){
				printf("(%s, %s)", G.vertices[intV.at(k)].data, G.vertices[intV.at(i)].data);
			}
			else {
				while (!isConnected(G, intV.at(k), intV.at(i)))
					k++;
				i--;
			}
		}
	}
}
