/**
	二分图的带权匹配就是求出一个匹配集合，使得集合中边的权值之和最大或最小。并且二分图的最佳匹配一定是完备匹配。
	KM算法实现求二分图的最大权值匹配。
	【时间复杂度】O(N^3)
	【扩展】
		Ⅰ.求最小权值匹配只需将所有的边权值取其相反数，求最大权完备匹配，匹配的值再取相反数即可。
		Ⅱ.KM算法的运行要求是必须存在一个完备匹配，如果求一个最大权匹配(不一定完备)该如何办？依然很简单，把不存在的边权值赋为0。
		Ⅲ.KM算法求得的最大权匹配是边权值和最大，如果我想要边权之积最大，又怎样转化？还是不难办到，每条边权取自然对数，然后求最大和权匹配，求得的结果a再算出e^a就是最大积匹配。至于精度问题则没有更好的办法了。
**/
const int MAXV = 205;           //X or Y点集大小
const int oo = 0x3fffffff;
struct MaximumMatchingOfWeightedBipartiteGraph{
    int w[MAXV][MAXV];          //权值
    int sv, tv;                 //Perfect Matching, sv should equal to tv
    bool S[MAXV], T[MAXV];
    int lx[MAXV], ly[MAXV];       //X、Y点集可行顶标
    int left[MAXV];
    int slack[MAXV];
    void init(int v){
        sv = tv = v;
        MEM(w, 0);
    }
    void add_uedge(int u, int v, int _w){
        w[u][v] = _w;
    }
    bool cross_path(int u){
        S[u] = true;
        for (int v = 1; v <= tv; v ++){
            if(T[v]) continue;
            int t = lx[u] + ly[v] - w[u][v];
            if (t == 0){
                T[v] = true;
                if (left[v] == 0 || cross_path(left[v])){
                    left[v] = u;
                    return true;
                }
            }
            else{
                slack[v] = min(slack[v], t);
            }
        }
        return false;
    }
    int solve(){
        //Init
        MEM(lx, 0); MEM(ly, 0);
        MEM(left, 0);
        for (int i = 1; i <= sv; i ++)
            for (int j = 1; j <= tv; j ++)
                lx[i] = max(lx[i], w[i][j]);
        //Main
        for (int i = 1; i <= sv; i ++){
            for (int j = 1; j <= tv; j ++)  slack[j] = oo;
            while(1){
                MEM(S, false);  MEM(T, false);
                if (cross_path(i)){
                    break;
                }
                else{
                    int d = oo;
                    for (int j = 1; j <= tv; j ++)
                        if (!T[j])  d = min(d, slack[j]);
                    for (int j = 1; j <= sv; j ++)
                        if (S[j])   lx[j] -= d;
                    for (int j = 1; j <= tv; j ++){
                        if (T[j])   ly[j] += d;
                        else    slack[j] -= d;
                        //匈牙利树中T集点ly不变,S集点lx减小,更新slack值
                    }
                }
            }
        }
        int res = 0;
        for(int i = 1; i <= sv; i ++)   res += lx[i];
        for(int i = 1; i <= tv; i ++)   res += ly[i];
        return res;
    }
}km;