/*
	Ӧ�ã�
		��ȡһ������ǰ��λ(double��������);
*/
//n��ԭ����������������ʵ���� _float�ǿ�ѧ��������С����_exp��10��ָ��
void scientific_notation(long long n, double &_float, int &_exp){
    double log10_n = log10(n);
    _exp = (int)log10_n;
    log10_n = log10_n - _exp;
    _float = pow(10, log10_n);
    return ;
}