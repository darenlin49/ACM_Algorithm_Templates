//���һ���⺯���Ķ��ε���>0(or <0)����ú���Ϊ͹����.

//����ģ��
const double eps = 1e-6;
bool dy(double x,double y)  {   return x > y + eps;} 		// x > y
bool xy(double x,double y)  {   return x < y - eps;} 		// x < y
bool dyd(double x,double y) {   return x > y - eps;} 		// x >= y
bool xyd(double x,double y) {   return x < y + eps;}     	// x <= y
bool dd(double x,double y)  {   return fabs( x - y ) < eps;}    // x == y

double cal(double pos){
    /* ������Ŀ����˼���� */
}

double solve(double left, double right){
    while(xy(left, right)){
        double mid = DMID(left, right);
        double midmid = DMID(mid, right);
        double mid_area = cal(mid);
        double midmid_area = cal(midmid);
        if (xyd(mid_area, midmid_area))     //��͹��������͹������dyd(mid_area, midmid_area)
            right = midmid;
        else
            left = mid;
    }
    return left;
}