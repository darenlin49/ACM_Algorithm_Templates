/**
	����ͼ�Ĵ�Ȩƥ��������һ��ƥ�伯�ϣ�ʹ�ü����бߵ�Ȩֵ֮��������С�����Ҷ���ͼ�����ƥ��һ�����걸ƥ�䡣
	KM�㷨ʵ�������ͼ�����Ȩֵƥ�䡣
	��ʱ�临�Ӷȡ�O(N^3)
	����չ��
		��.����СȨֵƥ��ֻ�轫���еı�Ȩֵȡ���෴���������Ȩ�걸ƥ�䣬ƥ���ֵ��ȡ�෴�����ɡ�
		��.KM�㷨������Ҫ���Ǳ������һ���걸ƥ�䣬�����һ�����Ȩƥ��(��һ���걸)����ΰ죿��Ȼ�ܼ򵥣��Ѳ����ڵı�Ȩֵ��Ϊ0��
		��.KM�㷨��õ����Ȩƥ���Ǳ�Ȩֵ������������Ҫ��Ȩ֮�����������ת�������ǲ��Ѱ쵽��ÿ����Ȩȡ��Ȼ������Ȼ��������Ȩƥ�䣬��õĽ��a�����e^a��������ƥ�䡣���ھ���������û�и��õİ취�ˡ�
**/
const int MAXV = 205;           //X or Y�㼯��С
const int oo = 0x3fffffff;
struct MaximumMatchingOfWeightedBipartiteGraph{
    int w[MAXV][MAXV];          //Ȩֵ
    int sv, tv;                 //Perfect Matching, sv should equal to tv
    bool S[MAXV], T[MAXV];
    int lx[MAXV], ly[MAXV];       //X��Y�㼯���ж���
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
                        //����������T����ly����,S����lx��С,����slackֵ
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