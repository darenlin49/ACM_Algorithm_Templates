//POJ1811 �ж�һ�����ǲ�������������Ǻ����������С�ķ�ƽ�����ӣ���1�Ǳ�������ӣ�
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

//return a * b % m
unsigned long long mul_mod(unsigned long long a, unsigned long long b, unsigned long long m){
    //Ϊ�˷�ֹlong long��a * b�������ʱ��Ҫ�ѳ˷���ӷ�
    //����Ϊ�����ӷ��ᳬʱҪʹ�ö��ֿ��ٳ˷�ģ��ģ�¶��ֿ�����ģ������
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
            //���m��int��Χ��ֱ������һʽ�˾Ϳ��ԣ�������Ҫ���¶�ʽ�ѳ˷����ӷ����ÿ��ٳ˷�ģ
            //res = (res * t) % m;
            res = mul_mod(res, tmp, m);
        }
        //ͬ��
        //t = t * t % m;
        tmp = mul_mod(tmp, tmp, m);

        b >>= 1;
    }
    return res;
}

/*-------------Miller-Rabin �������� ����(�õ�����mul_mod��exp_mod   ����return true)--------------*/
bool Miller_Rabin(long long n){
    int a[5] = {2, 3, 7, 61, 24251};
    //һ��Miller_Rabin�������������ѡ��100��a,�����Ĵ�����Ϊ0.25^100
    //����OI&&ACM�У�����ʹ������һ��a������������£�10^16��Ψһ��ǿα����Ϊ46,856,248,255,981

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
/*-------------Miller-Rabin �������� ����--------------*/

/*-------------pollard-rho ������n���ӷֽ� ����(�õ�mul_mod()��Miller-Rabin����)--------------*/
long long factor[100];      //��n��������
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
    //��ʱ��RP���� or n̫С(����n==4���Բ���������)�������pollard_rhoûŪ����������ö�����⴦��һ��
    long long d = 2;
    while(n % d != 0 && d * d <= n)
        d ++;
    pollard_rho(d);
    pollard_rho(n/d);
}
/*-------------pollard-rho ������n���ӷֽ� ����--------------*/


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
