struct Point{
    double x, y;
    Point() {}
    Point(double _x, double _y){
        x = _x, y = _y;
    }
    Point(const Point &p){
        x = p.x, y = p.y;
    }
    Point operator -(const Point &b)const{
        return Point(x - b.x, y - b.y);
    }
    double operator *(const Point &b)const{
        return x * b.y - y * b.x;
    }
    double operator &(const Point &b)const{
        return x * b.x + y * b.y;
    }
};
/** 两点间距离平方 **/
double dist2(Point a, Point b){
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

struct Line{
    Point s, e;
    double k;   //Slope
    Line() {}
    Line(Point _s, Point _e){
        s = _s, e = _e;
        k = atan2(e.y - s.y, e.x - s.x);
    }
    Line(double _sx, double _sy, double _ex, double _ey){
        s = Point(_sx, _sy), e = Point(_ex, _ey);
        k = atan2(_ey - _sy, _ex - _sx);
    }
};
/** 线段相交,相交返回true **/
bool intersection(Line l1,Line l2){
    return (max(l1.s.x,l1.e.x) >= min(l2.s.x,l2.e.x) &&
            max(l2.s.x,l2.e.x) >= min(l1.s.x,l1.e.x) &&
            max(l1.s.y,l1.e.y) >= min(l2.s.y,l2.e.y) &&
            max(l2.s.y,l2.e.y) >= min(l1.s.y,l1.e.y) &&
            ((l2.s-l1.s)*(l1.e-l1.s))*((l2.e-l1.s)*(l1.e-l1.s)) <= 0 &&			
            ((l1.s-l2.s)*(l2.e-l2.s))*((l1.e-l2.s)*(l2.e-l2.s)) <= 0);			//若端点不算相交则两个<=改为<即可
}