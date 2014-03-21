//由公式phi(i) = m(1-1/p1)(1-1/p2)……(1-1/pn) 求单个phi(i)
//只用一个phi值可以求2^50左右的phi值 
long long phi(long long n){
    long long res = n;
    for (int i = 2; i * i <= n; i ++){
        if (n % i == 0){
            res = res / i * (i - 1);
            while(n % i == 0)
                n /= i;
        }
    }
    if (n > 1){
        res = res / n * (n - 1);
    }
    return res;
}

//但是如果要用所有phi(1)~phi(n)的值的话上面的方法就行不通了
//我们知道当m,n互素时，phi(mn) = phi(m)*phi(n) 且  phi(m) = phi(p1^q1) * phi(p2^q2) * …… * phi(pn^qn)
//那么当p是素数且是m的约数时，phi(m*pi) = …… * phi(pr^(qr+1)) * ……  = phi(m) * pi
//
//总结：p是素数：①p是m的约数 phi(m*p) = phi(m)*p;  ②p不是m的约数 phi(m*p) = phi(m)*phi(p) = phi(m)*(p-1)

/*----------利用线性筛素数的思想快速求1~n的欧拉函数-----------*/
int phi[MAX];
bool noprime[MAX];
vector <int> prime;
void Euler(int n){
    phi[1] = 0;
    for (int i = 2; i <= n; i ++){
        if (!noprime[i]){
            prime.push_back(i);
            phi[i] = i - 1;
        }
        for (int j = 0; j < (int)prime.size() && prime[j] * i <= n; j ++){
            noprime[prime[j]*i] = 1;
            if (i % prime[j] == 0){
                phi[prime[j]*i] = phi[i] * prime[j];
            }
            else{
                phi[prime[j]*i] = phi[i] * phi[prime[j]];
            }
        }
    }
}