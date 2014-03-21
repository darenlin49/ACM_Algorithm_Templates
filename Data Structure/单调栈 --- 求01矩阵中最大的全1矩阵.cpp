//POJ 3494 --- ��01����������ȫ1����
//�ο�09����Ҷ��쳿�����ġ��������ݽṹ����Ϣѧ�����е�Ӧ�á�

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <climits>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>
#define MID(x,y) ((x+y)>>1)
using namespace std;
typedef long long LL;
int height[2005], a[2005][2005];	//height[]Ϊ����
int left[2005];						//��������չ
stack <int> S;
int main(){
    int n, m;
    while(scanf("%d %d", &n, &m) != EOF){
        int res = 0;
        memset(height, 0, sizeof(height));
        for (int i = 0; i < n; i ++)
            for (int j = 0; j < m; j ++)
                scanf("%d", &a[i][j]);
        for (int i = 0; i < n; i ++){
            while(!S.empty())
                S.pop();
            for (int j = 0; j <= m; j ++){
                if (j == m){
                    height[j] = -1;
                }
                else{
                    if (a[i][j] == 0)
                        height[j] = 0;
                    else
                        height[j] ++;
                }

                if (S.empty() || height[S.top()] < height[j]){
                    if (S.empty())
                        left[j] = -1;
                    else    left[j] = S.top();
                    S.push(j);
                }
                else{
                    int ok = 0;
                    while(!S.empty() && height[S.top()] >= height[j]){
                        if (height[S.top()] == height[j]){
                            left[j] = left[S.top()];
                            S.top() = j;
                            ok = 1;
                            break;
                        }
                        while(!S.empty() && height[S.top()] > height[j]){
                            res = max(res, height[S.top()] * (j - left[S.top()] - 1));
                            S.pop();
                        }
                        if (!ok){
                            if (S.empty())
                                left[j] = -1;
                            else    left[j] = S.top();
                            S.push(j);
                        }
                    }
                }
            }
        }
        printf("%d\n", res);
    }
	return 0;
}