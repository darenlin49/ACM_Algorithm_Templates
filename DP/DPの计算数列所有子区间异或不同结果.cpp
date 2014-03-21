/*	CodeForces #150 div1 A

题目大意：给定一个数列{a1,a2,...,an}，定义f[l,r] = al | al+1 | al+2 | ... | ar 。统计所有f[l,r]的不同结果。

思路：　设dp[i][j]为以i为右区间，区间长度为j的f[]，即dp[i][j] = f[i - j, i]。那么有方程dp[i][] = dp[i-1][] | a[i].但时间复杂度会达到O(n^2)，无法承受。这里我们巧妙的用set来自动把前面的状态去重来减少不必要的操作，即设set <int> dp[i]为以i为右区间的所有f[*, i]。set去重的强大啊！~直接帮助我们忽略分析或运算性质的过程了。

*/

#include <iostream>
#include <set>
using namespace std;
const int N = 100010;
 
set <int> dp[N],ans;
int a[N];
 
int main(){
    int n;
    cin>>n;
    for (int i = 0; i < n; i ++){
        cin>>a[i];
        dp[i].clear();
    }
    ans.clear();
    for (int i = 0; i < n; i ++){
        dp[i].insert(a[i]);
        ans.insert(a[i]);
        if (i != 0){
            set <int> ::iterator it;
            for (it = dp[i-1].begin(); it != dp[i-1].end(); it ++){
                dp[i].insert(*it | a[i]);
            }
            for (it = dp[i].begin(); it != dp[i].end(); it ++){
                ans.insert(*it);
            }
        }
    }
    cout<<ans.size()<<endl;
    return 0;
}