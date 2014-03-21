/*
���ڶ�������ɸ��������ɸ����ѡ��
	�����ֻ��bool�������1��0��ʾĳ�����Ƿ�����������Ϊ��������ɸ�����԰�i�ķ�Χ����sqrt(n)��Ч����ȽϺ�.
	�������Ҫ�����������ŵ�һ��������ʹ�ã�����Ϊ���߶���Ҫi��2~n����ʱ����ɸ��Ч����úܶ�.

------������£�
ɸ [0, 3200000) ��Χ�ڵ�������
	��һ������ɸ�� 297 ����
	�ڶ�������ɸ�� 109 ����
ɸ [0, 6400000) ��Χ�ڵ�������
	��һ������ɸ�� 922 ����
	�ڶ�������ɸ�� 266 ����
ɸ [0, 12800000) ��Χ�ڵ�������
	��һ������ɸ�� 2187 ����
	�ڶ�������ɸ�� 563 ����	
*/

/*-------------------��������ɸ��-------------------*/
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

/*--------------------����ɸ����--------------------*/
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
            if (i % prime[j] == 0)  break;		//ÿ����ֻ����������С��������ɸȥ
        }
    }
}

/*----------------�Գ�����n��������-------------------*/
vector <int> p;	
void find_prime_factor(int n)				
{
    for (int i = 2; i * i <= n; i ++){									//ö�ٵ�sqrt(n)����
	//������һ���Ż����ǿ���Ԥ����ɸ��������Ȼ������iֻ��ö����������
        if (n % i == 0){
            p.push_back(i);
            while(n % i == 0){
                n = n / i;
            }
        }
	if (n == 1) break;
    }
    if (n > 1){					//ֻ������һ������sqrt(n)�������ӣ�����������
        p.push_back(n);
    }
    return;
}

/*----------------�Գ�����n����������-------------------*/
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