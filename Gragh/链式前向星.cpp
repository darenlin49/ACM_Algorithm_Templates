/* 
	head[i]��ʾ��iΪ���ĵ�һ������edge[]�е��±ꣻ
	edge[k]��ʾ�ߵ���Ϣ��edge[k].next��ʾ��������ͬ������һ���ߵ�λ�ã�edge[k].u��edge[k].v��edge[k].w�ֱ��ʾ�ߵ���㡢�յ㡢Ȩֵ��
*/

const int MAXE = 1000;
struct node{
	int u, v, w;
	int next;
}edge[MAXE];
int cnt, head[MAXE];

void add(int u, int v, int w){	//��ӱ�
	edge[cnt].u = u;
	edge[cnt].v = v;
	edge[cnt].w = w;
	edge[cnt].next = head[u];
	head[u] = cnt ++;
}