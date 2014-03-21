/*	CodeForces #150 div1 A

��Ŀ���⣺����һ������{a1,a2,...,an}������f[l,r] = al | al+1 | al+2 | ... | ar ��ͳ������f[l,r]�Ĳ�ͬ�����

˼·������dp[i][j]Ϊ��iΪ�����䣬���䳤��Ϊj��f[]����dp[i][j] = f[i - j, i]����ô�з���dp[i][] = dp[i-1][] | a[i].��ʱ�临�ӶȻ�ﵽO(n^2)���޷����ܡ����������������set���Զ���ǰ���״̬ȥ�������ٲ���Ҫ�Ĳ���������set <int> dp[i]Ϊ��iΪ�����������f[*, i]��setȥ�ص�ǿ�󰡣�~ֱ�Ӱ������Ǻ��Է������������ʵĹ����ˡ�

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