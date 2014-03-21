const double eps = 1e-5;
bool dy(double x,double y)  {   return x > y + eps;} 		// x > y
bool xy(double x,double y)  {   return x < y - eps;} 		// x < y
bool dyd(double x,double y) {   return x > y - eps;} 		// x >= y
bool xyd(double x,double y) {   return x < y + eps;}     	// x <= y
bool dd(double x,double y)  {   return fabs( x - y ) < eps;}    // x == y
/* ����ӦSimpson��ʽ */
double a;
double F(double x){     //��������,��ͬ��Ŀ�����趨
    return sqrt(1 + 4 * a *a * x * x);
}
double simpson(double a, double b){     //����simpson����
    double c = (a+b)/2;
    return (F(a) + 4*F(c) + F(b)) * (b-a) / 6;
}
double asr(double a, double b, double eps, double A){       //����Ӧsimpson��ʽ(�ݹ����)����֪��������[a,b]�ϵ�����simpsonֵA
    double c = (a+b)/2;
    double L = simpson(a, c), R = simpson(c, b);
    if (fabs(L+R-A) <= 15*eps)  return L+R+(L+R-A)/15.0;
    return asr(a, c, eps/2, L) + asr(c, b, eps/2, R);
}
double asr(double a, double b, double eps){        //����Ӧsimpson��ʽ(������), ��������[a,b], ����eps
    return asr(a, b, eps, simpson(a, b));
}
/* ����ӦSimpson��ʽ */