/* 
	head[i]表示以i为起点的第一条边在edge[]中的下标；
	edge[k]表示边的信息：edge[k].next表示与这条边同起点的下一条边的位置；edge[k].u、edge[k].v、edge[k].w分别表示边的起点、终点、权值。
*/

const int MAXE = 1000;
struct node{
	int u, v, w;
	int next;
}edge[MAXE];
int cnt, head[MAXE];

void add(int u, int v, int w){	//添加边
	edge[cnt].u = u;
	edge[cnt].v = v;
	edge[cnt].w = w;
	edge[cnt].next = head[u];
	head[u] = cnt ++;
}