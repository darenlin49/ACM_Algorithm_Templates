//相交：意为有公共区域
//T为矩形类，(x1, y1)为左上角，(x2, y2)右上角，(可以忽略maxn……)

const int N = 1002;
struct T{
    int x1, y1, x2, y2, maxn;
}t[N];

bool cross(T n1, T n2){		//n1、n2为判断的两个矩形
    if (n1.y2 <= n2.y1)
        return false;
    if (n1.x2 <= n2.x1)
        return false;
    if (n1.x1 >= n2.x2)
        return false;
    if (n1.y1 >= n2.y2)
        return false;
    return true;
}