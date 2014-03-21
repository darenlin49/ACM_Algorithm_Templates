/*
    HDOJ 2966
    KD-Treeģ��
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>
#define MID(x, y) ( (x + y)>>1 )

using namespace std;
typedef long long LL;

//KD-Treeģ��
const int N=100005;
LL res;
struct Point
{
	int x, y;		//���Ƕ�ά�ģ���ʱ��2D-Tree
};

LL dist2(const Point &a, const Point &b)			//�����ƽ��
{
	return LL(a.x - b.x) * LL(a.x - b.x) + LL(a.y - b.y) * LL(a.y - b.y);
}

bool cmpX(const Point &a, const Point &b)
{
    return a.x < b.x;
}
bool cmpY(const Point &a, const Point &b)
{
    return a.y < b.y;
}

struct KDTree		//�ܳ����������Ľ���������~0.0~�ܳ����ǿ��------p�����Ѿ�������KD-Tree�ˣ�������������ȫʡ�ˣ�OOOOOrrz!!!����
{
	Point p[N];		//�ռ��ڵĵ�
	int Div[N];		//��¼�����ǰ�ʲô��ʽ���֣��ָ���ƽ����x�ỹ��y��, ==1ƽ��y����;==0ƽ��x���У�

    void build(int l, int r)		    //�ǵ��Ȱ�p����һ�¡�
	{
		if (l > r)	return;
		int mid=MID(l, r);
		int minX, minY, maxX, maxY;
        minX = min_element(p + l, p + r + 1, cmpX)->x;
        minY = min_element(p + l, p + r + 1, cmpY)->y;
        maxX = max_element(p + l, p + r + 1, cmpX)->x;
        maxY = max_element(p + l, p + r + 1, cmpY)->y;
        Div[mid] = (maxX - minX >= maxY - minY);
		nth_element(p + l, p + mid, p + r + 1, Div[mid] ? cmpX : cmpY);
		build(l, mid - 1);
		build(mid+1, r);
	}

	void find(int l, int r, Point a)				//����������ƽ������
	{
		if (l > r)	return;
		int mid = MID(l, r);
		LL dist = dist2(a, p[mid]);
		if (dist > 0)   //������ص㲻����ô�ж�
			res = min(res, dist);
		LL d = Div[mid] ? (a.x - p[mid].x) : (a.y - p[mid].y);
		int l1, l2, r1, r2;
		l1 = l , l2 = mid + 1;
		r1 = mid - 1, r2 = r;
		if (d > 0)
			swap(l1, l2), swap(r1, r2);
		find(l1, r1, a);
		if (d * d < res)
			find(l2, r2, a);
	}
};

Point pp[N];
KDTree kd;

int main()
{
    //freopen("data.txt","r+",stdin);
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d", &pp[i].x, &pp[i].y);
            kd.p[i] = pp[i];
        }
        kd.build(0, n-1);
        for (int i = 0; i < n; i++)
        {
            res = 9223372036854775807LL;
            kd.find(0, n - 1, pp[i]);
            printf("%I64d\n", res);
        }
    }
	return 0;
}
