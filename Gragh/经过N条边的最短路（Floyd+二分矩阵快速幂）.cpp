/*
��������������侭��N���ߵ�·���������ƣ�������֪�������ͼ���ڽӾ���A�洢ͼ�Ļ������־��������A^N��Ϊ����·�������þ���˷�������Ϊ����״̬�������ú;���˷�һ������dp[i][j][p]��ʾi��j�㾭��p���ߵ�·��������dp[i][j][p] = sigma(dp[i][k][p-1]*dp[k][j][1])����A=B*C����dp[p]����A��dp[p-1]����B��������

����Ȼ���·�ķ��̲��������ġ�����Floyd�ķ�����Ӧ����dp[i][j] = min(dp[i][j], dp[i][k]+dp[k][j])��

�������ķ���������������ķ�����ô�����ǿ϶��ģ�ֻҪ�޸�һ�¡��˷������ɡ���Ȼ��ֻҪ����������Ͻ���ɣ���ô�������ö��־��������������������Floyd���̷��Ͻ���ʵ�֤�����Ừ�̵����ġ�����˷�����Ϣѧ�е�Ӧ�á���֤����������ǰ�����û����������

��ôֻҪ�������¶����¾��󡰳˷���Ϊ��C[i][j] = min(C[i][j], A[i][k]+B[k][j])������ӭ�ж��⡣

����������ͼ���ڽӾ���ΪVE��������Ķ��壬VE * VE ��Ȼ�������㵽�ﾭ������������Ҫ�����·����Ȼ��ͬ��VE ^ N���ǵ��ﾭ��N��������Ҫ�����·����Ϊʲô���������Floyd��ʽ�����������ȷ���˾�����������̾��룿��Ϊ������º�Floyd��ͬ���Ǹ��µ�һ���µľ�����ȥ�˶�����ֱ����Floyd���Լ������Լ���������һ����ʱ����������Լ��ո��µ�ֵ�����������¡�
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>
#define MID(x,y) ((x+y)>>1)
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
 
typedef long long LL;
const int sup = 0x7fffffff;
const int inf = -0x7fffffff;
 
int hash[1000003], cnt;
struct mat{
    long long map[200][200];
    void init(){
        mem(map, -1);
    }
    void make_head(){
        mem(map, -1);
        for (int i = 0; i < cnt; i ++)
            map[i][i] = 0;
    }
}A;
int n, t, s, e;
mat floyd(mat &A, mat &B){
    mat res;
    res.init();
    for (int k = 0; k < cnt; k ++){
        for (int i = 0; i < cnt; i ++){
            if (A.map[i][k] != -1){
                for (int j = 0; j < cnt; j ++){
                    if(B.map[k][j] != -1){
                        if (res.map[i][j] == -1){
                            res.map[i][j] = A.map[i][k] + B.map[k][j];
                        }
                        else{
                            res.map[i][j] = min(res.map[i][j], A.map[i][k] + B.map[k][j]);
                        }
                    }
                }
            }
        }
    }
    return res;
}
long long work(mat &A, int n){
    mat res;
    res.make_head();
    while(n){
        if (n & 1){
            res = floyd(res, A);
        }
        n >>= 1;
        A = floyd(A, A);
    }
    return res.map[hash[s]][hash[e]];
}
int main(){
    mem(hash, -1);
    A.init();
    cnt = 0;
    scanf("%d %d %d %d", &n, &t, &s, &e);
    if (hash[s] == -1)
        hash[s] = cnt ++;
    if (hash[e] == -1)
        hash[e] = cnt ++;
    for (int i = 0; i < t; i ++){
        int l, a, b;
        scanf("%d %d %d", &l, &a, &b);
        if (hash[a] == -1)
            hash[a] = cnt ++;
        if (hash[b] == -1)
            hash[b] = cnt ++;
        A.map[hash[a]][hash[b]] = l;
        A.map[hash[b]][hash[a]] = l;
    }
    printf("%I64d\n", work(A, n));
	return 0;
}