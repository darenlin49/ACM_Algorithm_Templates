/*
	应用：
		①取一个数的前几位(double精度以内);
*/
//n是原数，可以是整数或实数； _float是科学计数法的小数，_exp是10的指数
void scientific_notation(long long n, double &_float, int &_exp){
    double log10_n = log10(n);
    _exp = (int)log10_n;
    log10_n = log10_n - _exp;
    _float = pow(10, log10_n);
    return ;
}