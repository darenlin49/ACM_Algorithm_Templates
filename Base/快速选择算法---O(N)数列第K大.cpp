/**
	���ƺ�ģ�������⡭��BZOJ 3293 && 1045 ����AC�����ʱ����		2013.09.16��

	O(N)ʱ���������е�K����
	����ѡ���㷨���ڿ�������Ĺ��̣�ÿ���׶�����ѡ��һ����Ϊ��׼���������仮�ֳ�С��������ʹ�������������������䣬��ʱ������ж�������ǲ��ǵ�k��������K����ȥ�������ң�����ȥ�������ҡ�
**/
template <class doubleORint>
doubleORint QuickSelect(doubleORint A[], int head, int tail, int k){
    int i = head, j = tail;
    doubleORint x = A[head];
    while(i < j){
        while(A[j] > x) j --;
        swap(A[i], A[j]);
        while(A[i] < x) i ++;
        swap(A[i], A[j]);
    }
    if (i - head == k){
        return A[i];
    }
    else if (i - head > k){
        return QuickSelect(A, head, i-1, k);
    }
    else{
        return QuickSelect(A, i+1, tail, k - (i - head + 1));
    }
}
int a[10005];
int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++){
        scanf("%d", &a[i]);
    }
    printf("%d", QuickSelect(a, 0, n-1, n/2));
    return 0;
}
