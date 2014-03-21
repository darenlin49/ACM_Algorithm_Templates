/*

	k路归并：即给定N个有序的序列，要求把这N个有序的序列合并成一个有序的序列。
	分析:
		数据很大，但是只要求求出前N个，所以可以想到用堆优化
		每个表的元素都是从左到右移入新表
		把每个表的当前元素放入二叉堆中, 每次删除最小值并放入新表中, 然后加入此序列的下一个元素
		每次操作需要logk时间, 因此总共需要nlogk的时间
		可以把这些和看成n个有序表:
		A[1]+B[1] <= A[1]+B[2] <= A[1]+B[3] <=…
		A[2]+B[1] <= A[2]+B[2] <= A[2]+B[3] <=…
		…
		A[n]+B[1] <= A[n]+B[2] <= A[n]+B[3] <=…

	综上所述，可以采用K路归并：
	
	POJ 2442 将M个列表合并取新表前N个元素
	方法：将M个列表不断的用两个列表K路归并的方法求。
	
*/

int m,n;
int a[2005], b[2005], tm[2005];

struct condition{
    int a, b;   //表示当前key是由A[a] + B[b]得来
    int key;
    friend bool operator < (condition n1, condition n2){
        return n2.key < n1.key;
    }
};

void k_merge(int A[], int B[], int n){      //K路归并,筛出前n个小的元素放回A[],A[]、B[]也只留n个即可
    priority_queue <condition , vector <condition> > Q;
    for (int i = 0; i < n; i ++){
        condition tmp;
        tmp.key = A[i] + B[0];
        tmp.a = i;
        tmp.b = 0;
        Q.push(tmp);
    }
    mem(tm, 0);
    for (int i = 0; i < n; i ++){
        condition t = Q.top();
        tm[i] = t.key;
        Q.pop();
        t.b ++;
        t.key = A[t.a] + B[t.b];
        Q.push(t);
    }
    for (int i = 0; i < n; i ++)
        A[i] = tm[i];
}

int main(){
    int t;
    scanf("%d", &t);
    while(t --){
        scanf("%d %d", &m, &n);
        for (int i = 0; i < n; i ++)
            scanf("%d", &a[i]);
        sort(a, a+n);
        for (int i = 1; i < m; i ++){
            for (int j = 0; j < n; j ++)
                scanf("%d", &b[j]);
            sort(b, b+n);
            k_merge(a, b, n);
        }
        for (int i = 0; i < n - 1; i ++)
            printf("%d ", a[i]);
        printf("%d\n", a[n-1]);
    }

    return 0;
}
