//�ཻ����Ϊ�й�������
//TΪ�����࣬(x1, y1)Ϊ���Ͻǣ�(x2, y2)���Ͻǣ�(���Ժ���maxn����)

const int N = 1002;
struct T{
    int x1, y1, x2, y2, maxn;
}t[N];

bool cross(T n1, T n2){		//n1��n2Ϊ�жϵ���������
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