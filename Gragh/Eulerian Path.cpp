//求欧拉回路或欧拉路,邻接阵形式,复杂度O(n^2)
//返回路径长度,path返回路径(有向图时得到的是反向路径)
//传入图的大小n和邻接阵mat,不相邻点边权0
//可以有自环与重边,分为无向图和有向图

#define MAXN 100

void find_path_u(int n,int mat[][MAXN],int now,int& step,int* path){
	int i;
	for (i=n-1;i>=0;i--)
		while (mat[now][i]){
			mat[now][i]--,mat[i][now]--;
			find_path_u(n,mat,i,step,path);
		}
	path[step++]=now;
}

void find_path_d(int n,int mat[][MAXN],int now,int& step,int* path){
	int i;
	for (i=n-1;i>=0;i--)
		while (mat[now][i]){
			mat[now][i]--;
			find_path_d(n,mat,i,step,path);
		}
	path[step++]=now;
}

int euclid_path(int n,int mat[][MAXN],int start,int* path){
	int ret=0;
	find_path_u(n,mat,start,ret,path);
//	find_path_d(n,mat,start,ret,path);
	return ret;
}
