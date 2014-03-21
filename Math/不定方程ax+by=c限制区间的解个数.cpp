/*
	sgu106: 给定a,b,c,x1,x2,y1,y2，求满足a*x+b*y+c = 0的解x满足x1<=x<=x2,y满足y1<=y<=y2.求满足条件的解的个数。
	
	我们先令c = -c，转化为我们熟悉的线性方程ax + by = c.然后：

	①用扩展欧几里德找到一组解(x0,y0)，这个很简单。但也有需要注意的地方，比如a,b,c=0的情况需要特殊注意一下，虽然扩展欧几里德可以解出a,b,c为任何值的一组解，但是这些情况在寻求解的个数的时候还是和一般方程不太一样的。

	②我们也知道方程的通解为：           x = x0 + kb'  (1);        y = y0 - ka' (2) ;    (b' = b/gcd(a,b),   a' = a / gcd(a,b) ).

	那么sgu 106就是求在范围内k能取几个：

	③将x1,x2带入上面(1)方程求出k1,k2 (k1 < k2); 同理将y1, y2带入上面(2)方程求出k3, k4 (k3 < k4).则 ans = min(k2, k4) - max(k1, k3).(这个min,max,等式一时半会儿也不好解释清楚，最好还是在纸上比划比划验证一下……).  而且，注意到我们是没把x0,y0解算进去的，于是当x0,y0也在范围内时，ans+1.

	④细节：边界问题：例如，如果x0 = 3, x1 = 5, x2 =7, b = 2,   那么k2 - k1 = 2 - 1 = 1，实际上[x1..x2]内是可以取到两个k的~~应该看出什么了，当xo < x1 < x2时，计算k1时要把x1-1，同理当x1 < x2 < x0时，计算k2时要把x2+1；对y0, y1, y2同理。
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
    long long xx1 = x1, xx2 = x2, yy1 = y1, yy2 = y2;   //保留区间，最后判断x0,y0是否在区间内需要

    //边界处理：
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
    c *= -1;    //把c移到等式右边构成ax+by=c

    //特殊处理a=b=0,a=0 b!=0,a!=0 b=0的情况
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

    //一般情况：
    long long x0, y0, flagx = 1, flagy = 1, g = gcd(a, b);
    if (c % g != 0)
        return 0;
    a /= g;
    if (a < 0)
        a = -1*a, flagx = -1;   //把a,b都变正数(不过感觉不变也行……囧)
    b /= g;
    if (b < 0)
        b = -1*b, flagy = -1;
    c /= g;
    ext_gcd(a, b, x0, y0);

    x0 *= (c * flagx);      //解出了一组特殊解x0, y0
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
