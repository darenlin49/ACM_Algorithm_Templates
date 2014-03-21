/*
	①找出n!的素因子是很容易的，显然就是1~n的素数。
	②关键在于怎么求出素因子的个数：
	
	以素因子2为例：
	N！	=1*2*3*4*5……N
		=(2*4*6……) * (1*3*5……)		//因为有N/2个偶数，所以偶数部分可以提出N/2个2，
		=2^(N/2) * (1*2*3*……N/2) * (1*3*5*……)
		=2^(N/2) * (N/2)! * (1*3*5*……)
		
	于是有递推公式 f(n,2) = f(n/2,2) + n/2，表示n！中2的个数。
	用同样的方法可以推出 f(n,p) = f(n/p,p) + n/p，表示n！中素数p的个数。
*/


/*-----------  n!中素因子p的个数：f(n,p) = f(n/p, p) + n/p ：O(log(p)(n)) ------------*/
long long f(int n, int p){
    long long res = 0;
    while(n){
        res += n/p;
        n /= p;
    }
    return res;
}


/*---- n!分解素因子: 复杂度O(n)（预先筛好素数O(p*logn)）,(n <= 10^6)----*/

vector <pair<int, long long> > prime;     //n!的素因子就是1~n中的素数,第一个记录素因子,第二个记录个数
bool noprime[1000010];
void factor(int n){
    prime.clear();
	//筛素数，要使用多次时可以放函数外预处理来优化时间
    for (int i = 2; i <= n; i ++){
        if (!noprime[i]){
            prime.push_back(make_pair(i, 0));
        }
        for (int j = 0; j < prime.size() && prime[j].first*i <= n; j ++){
            noprime[prime[j].first*i] = 1;
            if (i % prime[j].first == 0)
                break;
        }
    }
	//n!分解质因子过程，要用到上面的f(n, p)
    for (int i = 0; i < prime.size(); i ++){
        int p = prime[i].first;
        prime[i].second = f(n, p);
    }
}


/*---- 组合数分解素因子: C(n,k) = n!/(k!(n-k)!) ------*/
vector <pair<int, long long> > prime;     //组合数素因子表,第一个记录素因子,第二个记录个数
long long factor(int n, int k){
	
	prime.clear();
	//筛素数，要使用多次时可以放函数外预处理来优化时间
    for (int i = 2; i <= n; i ++){
        if (!noprime[i]){
            prime.push_back(make_pair(i, 0));
            for (int j = i; j <= n; j ++)
                ff[j][i] = f(j, i);
        }
        for (int j = 0; j < prime.size() && prime[j].first*i <= n; j ++){
            noprime[prime[j].first*i] = 1;
            if (i % prime[j].first == 0)
                break;
        }
    }
	//组合数分解素因子过程，要用到上面的f(n, p)
    long long res = 1;
    for (int i = 0; i < prime.size(); i ++){
        if (prime[i].first > n)
            break;
        int p = prime[i].first;
        prime[i].second = f(n, p);
        if (p <= k)
            prime[i].second -= f(k, p);
        if (p <= (n - k))
            prime[i].second -= f(n-k, p);
        res *= (prime[i].second + 1);
    }
    return res;
}
