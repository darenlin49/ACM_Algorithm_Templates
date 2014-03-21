/*
题目大意：给定一个数列，找到两个不相交的子序列，使他们的和最大。

思路：因为求两个不相交的子序列，所以就是找到一个i，使得他左区间最大连续子段和+右区间最大连续子段和最大。考虑求一边的就可以了，即经典的一维最大连续子段和问题。dp[i]表示[0..i]区间的最大连续子段和，b[i]表示以i结尾的最大连续子段和。

状态转移方程：b[i] = max{b[i-1] + a[i] , a[i]}，　　dp[i] = max{b[j] (j = 0..i) }

时间复杂度：O(N)DP预处理+O(N)查询
*/


#include <cstdio>
#include <cstdlib>
#include <climits>
using namespace std;

const int N = 100010;
int dp1[N],dp2[N],b1[N],b2[N],a[N];

void go_dp(int n){
	//left
	b1[0] = a[0];
	dp1[0] = b1[0];
	int max = dp1[0];
	for (int i = 1; i < n; i ++){
		if (b1[i-1] > 0){
			b1[i] = b1[i-1] + a[i];
		}
		else{
			b1[i] = a[i];
		}
		if (b1[i] > max){
			max = b1[i];
		}
		dp1[i] = max;
	}
	//right
	b2[n-1] = a[n-1];
	dp2[n-1] = b2[n-1];
	max = dp2[n-1];
	for (int i = n - 2; i >= 0; i --){
		if (b2[i+1] > 0){
			b2[i] = b2[i+1] + a[i];
		}
		else{
			b2[i] = a[i];
		}
		if (b2[i] > max){
			max = b2[i];
		}
		dp2[i] = max;
	}
}

int ff(int n){
	int max = INT_MIN;
	for (int i = 0; i < n - 1; i ++){
		if (dp1[i] + dp2[i+1] > max){
			max = dp1[i] + dp2[i+1]; 
		}
	}
	return max;
}

int main(){
	int n;
	while(scanf("%d",&n),n){
		for (int i = 0; i < n; i ++){
			scanf("%d",&a[i]);
		}
		go_dp(n);
		printf("%d\n",ff(n));
	}
	//system("pause");
	return 0;
}