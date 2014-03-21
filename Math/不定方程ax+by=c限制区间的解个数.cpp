/*
	sgu106: ����a,b,c,x1,x2,y1,y2��������a*x+b*y+c = 0�Ľ�x����x1<=x<=x2,y����y1<=y<=y2.�����������Ľ�ĸ�����
	
	��������c = -c��ת��Ϊ������Ϥ�����Է���ax + by = c.Ȼ��

	������չŷ������ҵ�һ���(x0,y0)������ܼ򵥡���Ҳ����Ҫע��ĵط�������a,b,c=0�������Ҫ����ע��һ�£���Ȼ��չŷ����¿��Խ��a,b,cΪ�κ�ֵ��һ��⣬������Щ�����Ѱ���ĸ�����ʱ���Ǻ�һ�㷽�̲�̫һ���ġ�

	������Ҳ֪�����̵�ͨ��Ϊ��           x = x0 + kb'  (1);        y = y0 - ka' (2) ;    (b' = b/gcd(a,b),   a' = a / gcd(a,b) ).

	��ôsgu 106�������ڷ�Χ��k��ȡ������

	�۽�x1,x2��������(1)�������k1,k2 (k1 < k2); ͬ��y1, y2��������(2)�������k3, k4 (k3 < k4).�� ans = min(k2, k4) - max(k1, k3).(���min,max,��ʽһʱ����Ҳ���ý����������û�����ֽ�ϱȻ��Ȼ���֤һ�¡���).  ���ң�ע�⵽������û��x0,y0�����ȥ�ģ����ǵ�x0,y0Ҳ�ڷ�Χ��ʱ��ans+1.

	��ϸ�ڣ��߽����⣺���磬���x0 = 3, x1 = 5, x2 =7, b = 2,   ��ôk2 - k1 = 2 - 1 = 1��ʵ����[x1..x2]���ǿ���ȡ������k��~~Ӧ�ÿ���ʲô�ˣ���xo < x1 < x2ʱ������k1ʱҪ��x1-1��ͬ��x1 < x2 < x0ʱ������k2ʱҪ��x2+1����y0, y1, y2ͬ��
*/


#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
long long gcd(long long a, long long b){
    if (b == 0)
        return a;
    return gcd(b, a%b);
}
void ext_gcd(long long a, long long b, long long &x, long long &y){
    if (b == 0){
        x = 1;
        y = 0;
        return ;
    }
    ext_gcd(b, a%b, x, y);
    long long tmp = x;
    x = y;
    y = tmp - a / b * y;
    return ;
}
long long num_of_equation(long long x0, long long y0, long long x1, long long y1, long long x2, long long y2, long long a, long long b){
    long long xx1 = x1, xx2 = x2, yy1 = y1, yy2 = y2;   //�������䣬����ж�x0,y0�Ƿ�����������Ҫ

    //�߽紦��
    if (x0 > x2) x2 ++;
    if (x0 < x1) x1 --;
    if (y0 > y2) y2 ++;
    if (y0 < y1) y1 --;

    long long k1 = (x1 - x0)/b;
    long long k2 = (x2 - x0)/b;
    if (k1 > k2){
        long long tmp = k1;
        k1 = k2;
        k2 = tmp;
    }
    long long k3 = (y1 - y0)/-a;
    long long k4 = (y2 - y0)/-a;
    if (k3 > k4){
        long long tmp = k3;
        k3 = k4;
        k4 = tmp;
    }
    long long res = min(k2, k4) - max(k1, k3);
    if (x0 >= xx1 && x0 <= xx2 && y0 >= yy1 && y0 <= yy2)   res ++;
    return res < 0 ? 0 : res;
}
long long f(long long a, long long b, long long c, long long x1, long long x2, long long y1, long long y2){
    c *= -1;    //��c�Ƶ���ʽ�ұ߹���ax+by=c

    //���⴦��a=b=0,a=0 b!=0,a!=0 b=0�����
    if (a == 0 && b == 0){
        if (c == 0)
            return (x2 - x1 + 1) * (y2 - y1 + 1);
        else
            return 0;
    }
    if (a == 0){
        if (c % b == 0)
            if (c/b >= y1 && c/b <= y2)
                return (x2 - x1 + 1);
            else
                return 0;
        else
            return 0;
    }
    if (b == 0){
        if (c % a == 0)
            if (c/a >= x1 && c/a <= x2)
                return (y2 - y1 + 1);
            else
                return 0;
        else
            return 0;
    }

    //һ�������
    long long x0, y0, flagx = 1, flagy = 1, g = gcd(a, b);
    if (c % g != 0)
        return 0;
    a /= g;
    if (a < 0)
        a = -1*a, flagx = -1;   //��a,b��������(�����о�����Ҳ�С�����)
    b /= g;
    if (b < 0)
        b = -1*b, flagy = -1;
    c /= g;
    ext_gcd(a, b, x0, y0);

    x0 *= (c * flagx);      //�����һ�������x0, y0
    y0 *= (c * flagy);

    a *= flagx;
    b *= flagy;
    return num_of_equation(x0, y0, x1, y1, x2, y2, a, b);
}
int main(){
    long long a, b, c, x1, x2, y1, y2;
    cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
    cout << f(a, b, c, x1, x2, y1, y2) << endl;
    return 0;
}
