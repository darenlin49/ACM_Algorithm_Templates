/*
FZU 1752 (a,b,c <= 2^63 - 1)
由于m也很大，还需要快速乘法模，而且递归形式慢过不了此题……
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

//return a * b % m
unsigned long long quick_add_mod(unsigned long long a, unsigned long long b, unsigned long long m){
    //为了防止long long型a * b溢出，有时需要把乘法变加法
    //且因为暴力加法会超时要使用二分快速乘法模（模仿二分快速幂模……）
    unsigned long long res = 0, tmp = a % m;
    while(b){
        if (b & 1)
        {
            res = res + tmp;
            res = (res >= m ? res - m : res);			//用减法比用mod快
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
            //res = (res * tmp) % m;
            res = quick_add_mod(res, tmp, m);
			
        }
		
        //同上
        //tmp = tmp * tmp % m;
        tmp = quick_add_mod(tmp, tmp, m);

        b >>= 1;
    }
    return res;
}
int main(){
    long long a,b,c;
    while(scanf("%I64d%I64d%I64d", &a, &b, &c) != EOF){
        printf("%I64d\n", exp_mod(a,b,c));
    }
    return 0;
}
