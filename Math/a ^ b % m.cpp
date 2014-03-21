/*
FZU 1752 (a,b,c <= 2^63 - 1)
����mҲ�ܴ󣬻���Ҫ���ٳ˷�ģ�����ҵݹ���ʽ�������˴��⡭��
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

//return a * b % m
unsigned long long quick_add_mod(unsigned long long a, unsigned long long b, unsigned long long m){
    //Ϊ�˷�ֹlong long��a * b�������ʱ��Ҫ�ѳ˷���ӷ�
    //����Ϊ�����ӷ��ᳬʱҪʹ�ö��ֿ��ٳ˷�ģ��ģ�¶��ֿ�����ģ������
    unsigned long long res = 0, tmp = a % m;
    while(b){
        if (b & 1)
        {
            res = res + tmp;
            res = (res >= m ? res - m : res);			//�ü�������mod��
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
            
			//���m��int��Χ��ֱ������һʽ�˾Ϳ��ԣ�������Ҫ���¶�ʽ�ѳ˷����ӷ����ÿ��ٳ˷�ģ
            //res = (res * tmp) % m;
            res = quick_add_mod(res, tmp, m);
			
        }
		
        //ͬ��
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
