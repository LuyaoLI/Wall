#include"DSAL1.h"
#include"DSAL2.h"

bool visited[MAX_VERTEX_NUM];

int locateVex(ALGraph G, VertexType u){ // 返回顶点u在图G中的序号
	for (int i = 0; i < G.vexnum; i++){
		if (strcmp(u, G.vertices[i].data) == 0)
			return i;
	}
	return -1;
}
char* getVexInfo(char *vexInfo, int index){ // 得到输入边对中指定下标中的顶点值
	char tmp[10];
	int end;
	if (index == 0){
		for (int i = 1, j = 0; vexInfo[i] != ',';i++, j++){
			tmp[j] = vexInfo[i];
			end = j;
		}
		tmp[end + 1] = '\0';
		char *rtmp = (char*)malloc((end + 1)*sizeof(char));  // 节省无用内存开支
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
void createGraph(ALGraph *G, char* vexInfo){ // 初始化并创建一个以邻接表方式存储的图
	char vexChar[10];
	ArcNode *tnode;
	printf("********************创建一个无向图********************");
	printf("\n图顶点个数为(请输入一个小于30的正整数) : "); // 对图进行初始化
	scanf("%d", &(*G).vexnum);
	if ((*G).vexnum <= 0 || (*G).vexnum > 30)
		throw 1;
	printf("图中边的条数为(请输入一个整数) : ");
	scanf("%d", &(*G).arcnum);
	if ((*G).arcnum < 0 || (*G).arcnum>((*G).vexnum * ((*G).vexnum - 1) / 2))
		throw 2;
	printf("\n\n*****************请输入图中顶点值********************");
	printf("\n");
	for (int i = 0; i < (*G).vexnum; i++){ // 初始化头结点表
		printf("第%d个顶点的值为 :", i + 1);
		scanf("%s", vexChar);
		strcpy((*G).vertices[i].data, vexChar);
		(*G).vertices[i].firstarc = NULL;
	}
	printf("\n\n************请输入图中边对(格式为（a, b))**************");
	getchar();
	printf("\n");
	for (int i = 0; i < (*G).arcnum; i++){
		printf("第%d条边对为 :", i + 1);
		gets(vexInfo);
		int arcIndex1 = locateVex(*G, getVexInfo(vexInfo, 0));
		int arcIndex2 = locateVex(*G, getVexInfo(vexInfo, 1));
		if (arcIndex1 == -1 || arcIndex2 == -1)
			throw 3;
		ArcNode *arcnode1 = (ArcNode*)malloc(sizeof(ArcNode));
		(*arcnode1).adjvex = arcIndex2;
		(*arcnode1).nextarc = NULL;
		if ((*G).vertices[arcIndex1].firstarc == NULL){ // 如果表头结点还未连接边表
			(*G).vertices[arcIndex1].firstarc = arcnode1;
		}
		else {  // 若已连接
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
void destroyGraph(ALGraph *G){ // 销毁一个以邻接表方式存储的图
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
	(*G).vexnum = 0; // 顶点数为0 
	(*G).arcnum = 0; // 边数为0 
}
int FirstAdjVex(ALGraph G, VertexType v){ // 返回邻接表中顶点v的第一个临接顶点的序号，若不存在，则返回-1
	int v1 = locateVex(G, v); // 找到顶点v在图中的序号 
	ArcNode* p = G.vertices[v1].firstarc;
	if (p)
		return p->adjvex;
	else
		return -1;
}
int NextAdjVex(ALGraph G, VertexType v, VertexType w){ // 返回顶点v的(相对于w的)下一个邻接顶点的序号
	                                                   // 若不存在（w是v的最后一个邻接点），则返回-1
	int v1 = locateVex(G, v);
	int v2 = locateVex(G, w);
	ArcNode *tnode = G.vertices[v1].firstarc;
	while (tnode && tnode->adjvex != v2){ // 令tnode指向顶点v的链表中邻接顶点为w的结点
		tnode = tnode->nextarc;
	}
	if (!tnode || !tnode->nextarc) // w没找到w或w是最后一个邻接点
		return -1;
	else
		return tnode->nextarc->adjvex; // 返回v的(相对于w的)下一个邻接顶点的序号
}
void DFS(ALGraph G, int v, void(*Visit)(char*)){ // 深度优先遍历算法（递归算法）
	extern vector<int> DFSpanArc;
	visited[v] = TRUE; 
	Visit(G.vertices[v].data);
	DFSpanArc.push_back(v);
	for (int w = FirstAdjVex(G, G.vertices[v].data); w >= 0; w = NextAdjVex(G, G.vertices[v].data, G.vertices[w].data))
		if (!visited[w]){
		DFS(G, w, Visit); // 对v的尚未访问的邻接点w递归调用DFS 
		}
}
void DFSTraverse(ALGraph G, void(*Visit)(char*)){ // 对整张图进行深度优先遍历（递归算法）
	extern vector<int> DFSpanArc;
	char u[10];
	DFSpanArc.clear();
	for (int v = 0; v<G.vexnum; v++) // 访问标志数组初始化
		visited[v] = FALSE;
	printf("\n\n*******************对图进行DFS遍历（递归）*******************\n请指定DFS开始的结点： ");
	scanf("%s", u);
	if (locateVex(G, u) == -1)
		throw 3;
	printf("当前DFS下结点访问序列为：");
	if (G.vexnum == 1)
		printf("%s", G.vertices[0].data);
	else {
		for (int v = locateVex(G, u); v < G.vexnum; v++)
			if (!visited[v])
				DFS(G, v, Visit);
		for (int v = 0; v<G.vexnum; v++) // 用户输入非完全连通图时对剩余结点的遍历
			if (!visited[v])
				DFS(G, v, Visit);
	}
}
bool isNotFullVisited(ALGraph G, int v){ // 用于利用栈进行非递归深度优先遍历时判断当前结点的所连结点是否已经完全访问完
	ArcNode * p = G.vertices[v].firstarc;
	while (p){
		if (!visited[p->adjvex]){
			return TRUE;
		}
		else p = p->nextarc;
	}
	return FALSE;
}
void nonCurDFSTraverse(ALGraph G, void(*Visit)(char*)){ // 对整张图进行深度优先遍历（非递归算法）
	int w, v;
	char u[10];
	Stack s;
	initStack(&s);
	for (int v = 0; v<G.vexnum; v++) // 访问标志数组初始化
		visited[v] = FALSE;
	printf("\n\n*******************对图进行DFS遍历（非递归）*******************\n请指定DFS开始的结点： ");
	scanf("%s", u);
	printf("当前DFS下结点访问序列为：");
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

void BFSTraverse(ALGraph G, void(*Visit)(char*)){ // 按广度优先非递归遍历图
	extern vector<int> BFSpanArc;
	int u;
	char w[10];
	Queue Q;
	initQueue(&Q);       // 初始化
	BFSpanArc.clear(); 
	for (int v = 0; v<G.vexnum; v++)
		visited[v] = FALSE;
	printf("\n\n*******************对图进行BFS遍历*******************\n请指定BFS开始的结点： ");
	scanf("%s", w);
	if (locateVex(G, w) == -1)
		throw 3;
	printf("当前BFS下结点访问序列为：");
	if (G.vexnum == 1)
		printf("%s", G.vertices[0].data);
	else{
		for (int v = locateVex(G, w); v < G.vexnum; v++){
			if (!visited[v]){
				visited[v] = TRUE;
				Visit(G.vertices[v].data);
				BFSpanArc.push_back(v);
				enQueue(&Q, v); // v入队列 
				while (!isQueueEmpty(Q)){ // 队列非空
					deQueue(&Q, &u); // 弹出队头元素
					for (int w = FirstAdjVex(G, G.vertices[u].data); w >= 0; w = NextAdjVex(G, G.vertices[u].data, G.vertices[w].data)){
						if (!visited[w]){
							visited[w] = TRUE;
							Visit(G.vertices[w].data);
							BFSpanArc.push_back(w);
							enQueue(&Q, w); // w入队列
						}
					}
				}
			}
		}
		for (int v = 0; v < G.vexnum; v++){ // 对用户所输入的不完全连通图的剩余结点的处理
			if (!visited[v]){
				visited[v] = TRUE;
				Visit(G.vertices[v].data);
				BFSpanArc.push_back(v);
				enQueue(&Q, v); // v入队列 
				while (!isQueueEmpty(Q)){ // 队列非空
					deQueue(&Q, &u); // 弹出队头元素
					for (int w = FirstAdjVex(G, G.vertices[u].data); w >= 0; w = NextAdjVex(G, G.vertices[u].data, G.vertices[w].data)){
						if (!visited[w]){
							visited[w] = TRUE;
							Visit(G.vertices[w].data);
							BFSpanArc.push_back(w);
							enQueue(&Q, w); // w入队列
						}
					}
				}
			}
		}
	}
}
bool isConnected(ALGraph G, int v1, int v2){ // 判断顶点序号为v1和v2的点是否有边相连
	ArcNode *tnode = G.vertices[v1].firstarc;
	while (tnode){
		if (tnode->adjvex == v2)
			return TRUE;
		else tnode = tnode->nextarc;
	}
	return FALSE;
}
void showDFSpanArc(ALGraph G, extern vector<int> intV){ // 打印出DFS生成树的边集
	if (G.vexnum == 1)printf("生成树为一个根节点%s\n", G.vertices[0].data);
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
void showBFSpanArc(ALGraph G, extern vector<int> intV){ // 打印出BFS生成树的边集
	if (G.vexnum == 1)printf("生成树为一个根节点%s\n", G.vertices[0].data);
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
