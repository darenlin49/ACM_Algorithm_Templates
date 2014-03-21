//�ɹ�ʽphi(i) = m(1-1/p1)(1-1/p2)����(1-1/pn) �󵥸�phi(i)
//ֻ��һ��phiֵ������2^50���ҵ�phiֵ 
long long phi(long long n){
    long long res = n;
    for (int i = 2; i * i <= n; i ++){
        if (n % i == 0){
            res = res / i * (i - 1);
            while(n % i == 0)
                n /= i;
        }
    }
    if (n > 1){
        res = res / n * (n - 1);
    }
    return res;
}

//�������Ҫ������phi(1)~phi(n)��ֵ�Ļ�����ķ������в�ͨ��
//����֪����m,n����ʱ��phi(mn) = phi(m)*phi(n) ��  phi(m) = phi(p1^q1) * phi(p2^q2) * ���� * phi(pn^qn)
//��ô��p����������m��Լ��ʱ��phi(m*pi) = ���� * phi(pr^(qr+1)) * ����  = phi(m) * pi
//
//�ܽ᣺p����������p��m��Լ�� phi(m*p) = phi(m)*p;  ��p����m��Լ�� phi(m*p) = phi(m)*phi(p) = phi(m)*(p-1)

/*----------��������ɸ������˼�������1~n��ŷ������-----------*/
int phi[MAX];
bool noprime[MAX];
vector <int> prime;
void Euler(int n){
    phi[1] = 0;
    for (int i = 2; i <= n; i ++){
        if (!noprime[i]){
            prime.push_back(i);
            phi[i] = i - 1;
        }
        for (int j = 0; j < (int)prime.size() && prime[j] * i <= n; j ++){
            noprime[prime[j]*i] = 1;
            if (i % prime[j] == 0){
                phi[prime[j]*i] = phi[i] * prime[j];
            }
            else{
                phi[prime[j]*i] = phi[i] * phi[prime[j]];
            }
        }
    }
}