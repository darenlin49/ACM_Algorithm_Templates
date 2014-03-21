/*	POJ 2891

�������������ͬ�ڷ�����
x = a1 (mod m1)
x = a2 (mod m2)
����
x = ar (mod mr)
��m1 m2 ���� mr���ػ��أ� ������ֱ�����й�ʣ�ඨ���ɣ� ��


�ں���indeterminate_equation()��ⲻ������ax + by = c  ->  AX = C (mod B)

*/

#include <iostream>
#include <cmath>
using namespace std;
void ext_gcd(long long a, long long b, long long &x, long long &y){
    if (b == 0){
        x = 1;
        y = 0;
        return ;
    }
    ext_gcd(b, a%b, x, y);
    long long tmp = x;
    x = y;
    y = tmp - a/b * y;
    return ;
}
long long gcd(long long a, long long b){
    return b ? gcd(b, a % b) : a;
}
long long lcm(long long a, long long b){
    return a / gcd(a, b) * b;
}

//��ⲻ������ax + by = c  &&  ģ���Է��� AX = C (mod B)
bool indeterminate_equation(long long a, long long b, long long c, long long &x, long long &y){
    int g = gcd(a, b);
    if (c % g != 0){
        return false;
    }
    a /= g;
    b /= g;
    c /= g;
    ext_gcd(a, b, x, y);
    x *= c;
    y *= c;
    //�������������x ,y�� �����������x����С������ֵ
    long long tmp = abs(double(b));
    x = (x % tmp + tmp) % tmp;
	if (x == 0)			//���⴦��0���
		x += tmp;
    return true;
}

long long m[1010];
long long r[1010];
int main(){
    int k;
    while(cin >> k){
        long long mlcm = 1;
        int ok = 1;
        for (int i = 1; i <= k; i ++){
            cin >> m[i] >> r[i];
        }
        long long ans = r[1];
        for (int i = 2; i <= k; i ++){
            long long a = mlcm = lcm(mlcm, m[i-1]);
            long long b = m[i];
            long long c = r[i] - ans;
            long long x, y;
            if (indeterminate_equation(a, b, c, x, y)){
                ans = ans + x * mlcm;
            }
            else{
                cout << -1 << endl;
                ok = 0;
                break;
            }
        }
        if (ok)
            cout << ans << endl;
    }
    return 0;
}
