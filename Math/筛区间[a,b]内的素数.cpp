//POJ 2689
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

bool noprime[1000100];		//区间[a,b]长度，数用i-a表示，表示该数是不是素数
vector <int> prime;			//区间[a,b]内的素数

bool vis[50010];
vector <int> pvis;
void init(int n){
    for (int i = 2; i <= n; i ++){
        if (!vis[i]){
            pvis.push_back(i);
            int p = i + i;
            while(p <= n){
                vis[p] = 1;
                p += i;
            }
        }
    }
    return;
}
void go(int a, int b){
    for (size_t k = 0; k < pvis.size(); k ++){
        if (pvis[k] > b)
            break;
        long long i = pvis[k];
        long long p = max(i+i, a/i * i);
        while(p <= b){
            if (p >= a){
                noprime[p - a] = 1;
            }
            p += i;
        }
    }
    for (long long i = a; i <= b; i ++){
        if (!noprime[i - a] && i != 1){
            prime.push_back(i);
        }
    }
}
int main(){
    int a,b;
    init(50000);
    while(cin >> a >> b){
        prime.clear();
        memset(noprime, 0, sizeof(noprime));
        go(a,b);
        long long minn = 20000000000, mina, minb, maxn = 0, maxa, maxb;
        if (prime.size() <= 1){
            cout<<"There are no adjacent primes."<<endl;
            continue;
        }
        for (size_t i = 0; i < prime.size() - 1; i ++){
            if (prime[i+1] - prime[i] > maxn){
                maxn = prime[i+1] - prime[i];
                maxa = prime[i];
                maxb = prime[i+1];
            }
            if (prime[i+1] - prime[i] < minn){
                minn = prime[i+1] - prime[i];
                mina = prime[i];
                minb = prime[i+1];
            }
        }
        cout<<mina<<","<<minb<<" are closest, "<<maxa<<","<<maxb<<" are most distant.\n";
    }

    return 0;
}