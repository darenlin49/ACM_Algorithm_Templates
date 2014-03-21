/*	POJ 3356
题目大意：给定字符串A和B。求A串转到B串所需的最少编辑操作次数。编辑操作包括：删除、添加一个字符、替换成任意字符。

思路：dp[i][j]，代表字符串1的前i子串和字符串2的前j子串的距离。初始化dp[0][0] = 0,dp[i][0] = i,dp[0][j] = j;

dp[i][j] = min {　　　dp[i][j-1] + 1     //添加(在i位置后面添加一个字符)

dp[i-1][j] + 1　　//删除(删除第i个字符)

dp[i-1][j-1] + (A[i] == B[i]?0:1)　　//替换　　　　}

*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>
#include <climits>
#define MID(x,y) ((x+y)>>1)
 
using namespace std;
 
typedef long long LL;    //max long long == 9223372036854775807LL
 
int f[1010][1010];
char s1[1010],s2[1010];
int main(){
    int l1,l2;
    while(cin>>l1){
        cin>>s1;
        cin>>l2;
        cin>>s2;
        for (int i = 0; i < 1010; i ++){
            for (int j = 0; j < 1010; j ++){
                f[i][j] = INT_MAX;
            }
        }
        for (int i = 0; i <= l1; i ++){
            f[i][0] = i;
        }
        for (int i = 0; i <= l2; i ++){
            f[0][i] = i;
        }
        for (int i = 1; i <= l1; i ++){
            for (int j = 1; j <= l2; j ++){
                f[i][j] = min(f[i-1][j-1] + (s1[i-1]==s2[j-1]?0:1), f[i][j-1] + 1);
                f[i][j] = min(f[i][j], f[i-1][j] + 1);
            }
        }
        cout<<f[l1][l2]<<endl;
    }
    return 0;
}