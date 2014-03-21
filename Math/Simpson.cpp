const double eps = 1e-5;
bool dy(double x,double y)  {   return x > y + eps;} 		// x > y
bool xy(double x,double y)  {   return x < y - eps;} 		// x < y
bool dyd(double x,double y) {   return x > y - eps;} 		// x >= y
bool xyd(double x,double y) {   return x < y + eps;}     	// x <= y
bool dd(double x,double y)  {   return fabs( x - y ) < eps;}    // x == y
/* 自适应Simpson公式 */
double a;
double F(double x){     //被积函数,不同题目具体设定
    return sqrt(1 + 4 * a *a * x * x);
}
double simpson(double a, double b){     //三点simpson法。
    double c = (a+b)/2;
    return (F(a) + 4*F(c) + F(b)) * (b-a) / 6;
}
double asr(double a, double b, double eps, double A){       //自适应simpson公式(递归过程)。已知整个区间[a,b]上的三点simpson值A
    double c = (a+b)/2;
    double L = simpson(a, c), R = simpson(c, b);
    if (fabs(L+R-A) <= 15*eps)  return L+R+(L+R-A)/15.0;
    return asr(a, c, eps/2, L) + asr(c, b, eps/2, R);
}
double asr(double a, double b, double eps){        //自适应simpson公式(主过程), 积分区间[a,b], 精度eps
    return asr(a, b, eps, simpson(a, b));
}
/* 自适应Simpson公式 */