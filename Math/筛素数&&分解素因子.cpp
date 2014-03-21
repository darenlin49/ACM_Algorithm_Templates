/*
关于厄拉多塞筛法和线性筛法的选择：
	①如果只用bool型数组的1和0表示某个数是否是素数，因为厄拉多塞筛法可以把i的范围缩到sqrt(n)，效果会比较好.
	②如果需要把素数单独放到一个数组中使用，则因为两者都需要i从2~n，此时线性筛法效果会好很多.

------情况②下：
筛 [0, 3200000) 范围内的素数：
	第一种素数筛法 297 毫秒
	第二种素数筛法 109 毫秒
筛 [0, 6400000) 范围内的素数：
	第一种素数筛法 922 毫秒
	第二种素数筛法 266 毫秒
筛 [0, 12800000) 范围内的素数：
	第一种素数筛法 2187 毫秒
	第二种素数筛法 563 毫秒	
*/

/*-------------------厄拉多塞筛法-------------------*/
#define MAX 100000
bool noprime[MAX];
void Prime(int n){
    int k;
    noprime[0] = noprime[1] = 1;
    for (int i = 2; i * i <= n; i ++)
        if (!noprime[i]){
            k = i + i;
            while(k <= n){
				noprime[k]=1;
                k += i;
            }
        }
}

/*--------------------线性筛素数--------------------*/
bool noprime[MAX];
vector <int> prime;
void Prime(int n){
	noprime[0] = noprime[1] = 1;
    for (int i = 2; i <= n; i ++){
        if (!noprime[i]){
            prime.push_back(i);
        }
        for (int j = 0; j < prime.size() && prime[j] * i <= n; j ++){
            noprime[prime[j]*i] = 1;
            if (i % prime[j] == 0)  break;		//每个数只被他自身最小的素因子筛去
        }
    }
}

/*----------------试除法求n的素因子-------------------*/
vector <int> p;	
void find_prime_factor(int n)				
{
    for (int i = 2; i * i <= n; i ++){									//枚举到sqrt(n)即可
	//这里有一个优化就是可以预处理筛出素数，然后上面i只用枚举素数即可
        if (n % i == 0){
            p.push_back(i);
            while(n % i == 0){
                n = n / i;
            }
        }
	if (n == 1) break;
    }
    if (n > 1){					//只可能有一个大于sqrt(n)的素因子，留在最后就行
        p.push_back(n);
    }
    return;
}

/*----------------试除法求n的所有因子-------------------*/
vector <int> factor;
void Factor(int n){
    factor.clear();
    factor.push_back(1);
    factor.push_back(n);
    for (int i = 2; i * i <= n; i ++){
        if (n % i == 0){
            factor.push_back(i);
            factor.push_back(n / i);
        }
    }
}