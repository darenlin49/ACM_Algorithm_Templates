/**
	（似乎模板有问题……BZOJ 3293 && 1045 快排AC这个超时……		2013.09.16）

	O(N)时间内求数列第K大数
	快速选择算法基于快速排序的过程，每个阶段我们选择一个数为基准，并把区间划分成小于这个数和大于这个数的两个子区间，此时便可以判断这个数是不是第k大项，如果比K大，则去左区间找，否则去右区间找。
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
