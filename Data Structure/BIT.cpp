/**

**/
const int MAXN = 100005;
struct BIT{
    int t[MAXN<<1];
    int bound;
    inline void init(int n){
        bound = n;
        mem(t, 0);
    }
    //lowbit(x)：求2^q, q是x二进制最右边的1的位置.
    inline int lowbit(int x){
        return x & (-x);
    }
    inline void update(int x, int v){
        for (int i = x; i <= bound; i += lowbit(i))
            t[i] += v;
    }
    inline int sum(int x){
        int res = 0;
        for (int i = x; i >= 1; i -= lowbit(i))
            res += t[i];
        return res;
    }
}bit;