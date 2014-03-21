//如果一个解函数的二次导恒>0(or <0)，则该函数为凸函数.

//精度模板
const double eps = 1e-6;
bool dy(double x,double y)  {   return x > y + eps;} 		// x > y
bool xy(double x,double y)  {   return x < y - eps;} 		// x < y
bool dyd(double x,double y) {   return x > y - eps;} 		// x >= y
bool xyd(double x,double y) {   return x < y + eps;}     	// x <= y
bool dd(double x,double y)  {   return fabs( x - y ) < eps;}    // x == y

double cal(double pos){
    /* 根据题目的意思计算 */
}

double solve(double left, double right){
    while(xy(left, right)){
        double mid = DMID(left, right);
        double midmid = DMID(mid, right);
        double mid_area = cal(mid);
        double midmid_area = cal(midmid);
        if (xyd(mid_area, midmid_area))     //下凸函数，上凸函数用dyd(mid_area, midmid_area)
            right = midmid;
        else
            left = mid;
    }
    return left;
}