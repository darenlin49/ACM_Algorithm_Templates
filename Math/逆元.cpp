int inv(int x)    
{    
    return x <= 1 ? x : (MOD - MOD / x) * inv(MOD % x) % MOD;    
}   
// x = 0 ʱ����Ԫ 