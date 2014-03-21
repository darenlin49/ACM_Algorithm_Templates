//POJ1811 判断一个数是不是素数，如果是合数，求出最小的非平凡因子（非1非本身的因子）
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

//return a * b % m
unsigned long long mul_mod(unsigned long long a, unsigned long long b, unsigned long long m){
    //为了防止long long型a * b溢出，有时需要把乘法变加法
    //且因为暴力加法会超时要使用二分快速乘法模（模仿二分快速幂模……）
    unsigned long long res = 0, tmp = a % m;
    while(b){
        if (b & 1)
        {
            res = res + tmp;
            res = (res >= m ? res - m : res);
        }
        b >>= 1;
        tmp <<= 1;
        tmp = (tmp >= m ? tmp - m : tmp);
    }
    return res;
}

//return a ^ b % m
long long exp_mod(long long a, long long b, long long m){
    long long res = 1 % m, tmp = a % m;
    while(b){
        if (b & 1){
            //如果m在int范围内直接用下一式乘就可以，否则需要用下二式把乘法化加法，用快速乘法模
            //res = (res * t) % m;
            res = mul_mod(res, tmp, m);
        }
        //同上
        //t = t * t % m;
        tmp = mul_mod(tmp, tmp, m);

        b >>= 1;
    }
    return res;
}

/*-------------Miller-Rabin 素数测试 部分(用到上面mul_mod和exp_mod   素数return true)--------------*/
bool Miller_Rabin(long long n){
    int a[5] = {2, 3, 7, 61, 24251};
    //一般Miller_Rabin素数测试是随机选择100个a,这样的错误率为0.25^100
    //但在OI&&ACM中，可以使用上面一组a，在这组底数下，10^16内唯一的强伪素数为46,856,248,255,981

    if (n == 2)
        return true;
    if (n == 1 || (n & 1) == 0)
        return false;

    long long b = n - 1;
    for (int i = 0; i < 5; i ++){
        if (a[i] >= n)
            break;
        while((b & 1) == 0)    b >>= 1;
        long long t = exp_mod(a[i], b, n);
        while(b != n - 1 && t != 1 && t != n - 1){
            t = mul_mod(t, t, n);
            b <<= 1;
        }
        if (t == n - 1 || (b & 1))
            continue;
        else
            return false;
    }
    return true;
}
/*-------------Miller-Rabin 素数测试 部分--------------*/

/*-------------pollard-rho 大整数n因子分解 部分(用到mul_mod()和Miller-Rabin测试)--------------*/
long long factor[100];      //存n的素因子
long long nfactor, minfactor;

long long gcd(long long a, long long b){
    return b ? gcd(b, a%b) : a;
}
void Factor(long long n);
void pollard_rho(long long n){
    if (n <= 1)
        return ;
    if (Miller_Rabin(n)){
        factor[nfactor ++] = n;
        if (n < minfactor)
            minfactor = n;
        return ;
    }
    long long x = 2 % n, y = x, k = 2, i = 1;
    long long d = 1;
    while(true){
        i ++;
        x = (mul_mod(x, x, n) + 1) % n;
        d = gcd((y - x + n) % n, n);
        if (d > 1 && d < n){
            pollard_rho(d);
            pollard_rho(n/d);
            return ;
        }
        if (y == x){
            Factor(n);
            return ;
        }
        if (i == k){
            y = x;
            k <<= 1;
        }
    }
}
void Factor(long long n){
    //有时候RP不好 or n太小(比如n==4就试不出来……)用下面的pollard_rho没弄出来，则暴力枚举特殊处理一下
    long long d = 2;
    while(n % d != 0 && d * d <= n)
        d ++;
    pollard_rho(d);
    pollard_rho(n/d);
}
/*-------------pollard-rho 大整数n因子分解 部分--------------*/


int main(){
    //srand(time(0));
    int t;
    cin >> t;
    for (int i = 0; i < t; i ++){
        nfactor = 0;
        minfactor = (1L << 63);
        long long n;
        cin >> n;
        pollard_rho(n);
        if (nfactor == 1 && factor[0] == n){
            cout << "Prime\n";
            continue;
        }
        sort(factor, factor+nfactor);
        cout << factor[0] << endl;
    }
    return 0;
}
