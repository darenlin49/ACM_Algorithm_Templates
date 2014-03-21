int solve(int r,int n){
    int res = 0;
    vector <int> p;
    for (int i = 2; i * i <= n; i ++){
        if (n % i == 0){
            p.push_back(i);
            while(n % i == 0){
                n = n / i;
            }
        }
    }
    if (n > 1){
        p.push_back(n);
    }
    for (int msk = 1; msk < (1 << p.size()); msk ++){
        int mult = 1, bit = 0;
        for (int i = 0; i < p.size(); i ++){
            if (msk & (1 << i)){
                ++bit;
                mult *= p[i];
            }
        }
        int cur = r / mult;
        if (bit % 2 == 1){
            res += cur;
        }
        else    res -= cur;
    }
    return r - res;
}