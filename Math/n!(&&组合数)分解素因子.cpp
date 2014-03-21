/*
	���ҳ�n!���������Ǻ����׵ģ���Ȼ����1~n��������
	�ڹؼ�������ô��������ӵĸ�����
	
	��������2Ϊ����
	N��	=1*2*3*4*5����N
		=(2*4*6����) * (1*3*5����)		//��Ϊ��N/2��ż��������ż�����ֿ������N/2��2��
		=2^(N/2) * (1*2*3*����N/2) * (1*3*5*����)
		=2^(N/2) * (N/2)! * (1*3*5*����)
		
	�����е��ƹ�ʽ f(n,2) = f(n/2,2) + n/2����ʾn����2�ĸ�����
	��ͬ���ķ��������Ƴ� f(n,p) = f(n/p,p) + n/p����ʾn��������p�ĸ�����
*/


/*-----------  n!��������p�ĸ�����f(n,p) = f(n/p, p) + n/p ��O(log(p)(n)) ------------*/
long long f(int n, int p){
    long long res = 0;
    while(n){
        res += n/p;
        n /= p;
    }
    return res;
}


/*---- n!�ֽ�������: ���Ӷ�O(n)��Ԥ��ɸ������O(p*logn)��,(n <= 10^6)----*/

vector <pair<int, long long> > prime;     //n!�������Ӿ���1~n�е�����,��һ����¼������,�ڶ�����¼����
bool noprime[1000010];
void factor(int n){
    prime.clear();
	//ɸ������Ҫʹ�ö��ʱ���Էź�����Ԥ�������Ż�ʱ��
    for (int i = 2; i <= n; i ++){
        if (!noprime[i]){
            prime.push_back(make_pair(i, 0));
        }
        for (int j = 0; j < prime.size() && prime[j].first*i <= n; j ++){
            noprime[prime[j].first*i] = 1;
            if (i % prime[j].first == 0)
                break;
        }
    }
	//n!�ֽ������ӹ��̣�Ҫ�õ������f(n, p)
    for (int i = 0; i < prime.size(); i ++){
        int p = prime[i].first;
        prime[i].second = f(n, p);
    }
}


/*---- ������ֽ�������: C(n,k) = n!/(k!(n-k)!) ------*/
vector <pair<int, long long> > prime;     //����������ӱ�,��һ����¼������,�ڶ�����¼����
long long factor(int n, int k){
	
	prime.clear();
	//ɸ������Ҫʹ�ö��ʱ���Էź�����Ԥ�������Ż�ʱ��
    for (int i = 2; i <= n; i ++){
        if (!noprime[i]){
            prime.push_back(make_pair(i, 0));
            for (int j = i; j <= n; j ++)
                ff[j][i] = f(j, i);
        }
        for (int j = 0; j < prime.size() && prime[j].first*i <= n; j ++){
            noprime[prime[j].first*i] = 1;
            if (i % prime[j].first == 0)
                break;
        }
    }
	//������ֽ������ӹ��̣�Ҫ�õ������f(n, p)
    long long res = 1;
    for (int i = 0; i < prime.size(); i ++){
        if (prime[i].first > n)
            break;
        int p = prime[i].first;
        prime[i].second = f(n, p);
        if (p <= k)
            prime[i].second -= f(k, p);
        if (p <= (n - k))
            prime[i].second -= f(n-k, p);
        res *= (prime[i].second + 1);
    }
    return res;
}
