//Common Disjoint Sets
const int MAXN = 505;
struct Disjoint_Sets{
	struct Sets{
		int father, ranks;
	}S[MAXN];
	void Init(int n){
		for (int i = 0; i <= n; i ++)
			S[i].father = i, S[i].ranks = 0;
	}
	int Father(int x){
		if (S[x].father == x){
			return x;
		}
		else{
			S[x].father = Father(S[x].father);     		//Path compression
			return S[x].father;
		}
	}
	bool Union(int x, int y){
		int fx = Father(x), fy = Father(y);
		if (fx == fy){
			return false;
		}
		else{                                           //Rank merge
			if (S[fx].ranks > S[fy].ranks){
				S[fy].father = fx;
			}
			else{
				S[fx].father = fy;
				if (S[fx].ranks == S[fy].ranks){
					++ S[fy].ranks;
				}
			}
			return true;
		}
	}
}DS;
//���ಢ�鼯 

const int N=100005;

struct set
{
    int parent;  	//��¼���ڵ�
    int rank;    	//��¼���ϵĽڵ���
    int relation;	//�ڵ�����ڵ�Ĺ�ϵ
}elem[N];

int MAX;      //��󼯵�Ԫ�ظ���

void init()
{
    int i;
    for(i=0;i<=N;i++)
    {
        elem[i].parent=i;
        elem[i].rank=1;
        elem[i].relation=0;
    }
}

int Find(int x)
{
    int temp;
    if (elem[x].parent != x)                		//·��ѹ��
    {
        temp=elem[x].parent;
        elem[x].parent = Find(elem[x].parent);
        elem[x].relation=(elem[temp].relation + elem[x].relation)%3;
    }
    return elem[x].parent;
}

void Union(int d,int a,int b)                     	//�ϲ���������
{
    int x,y;
    x=Find(a);
    y=Find(b);
    elem[x].parent=y;
    elem[x].relation=(elem[b].relation-elem[a].relation+2+d)%3;
}