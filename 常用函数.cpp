/* ======================================================= ��ֵ���� ======================================================= */

/* ���ش��ڻ��ߵ���ָ�����ʽ����С���� */
double ceil(double x);


/* ======================================================= �ַ��� ======================================================= */

/* ������ȫƥ������ַ��� */
extern char *strstr( char *str1, char *str2 );
size_t string::find( const string& str, size_t pos = 0 ) const;
size_t string::find( char c, size_t pos = 0 ) const;

/* ��ȡ��ĳ��λ�ÿ�ʼ, ����Ϊl���Ӵ� */
string substr ( size_t pos = 0, size_t n = npos ) const;

/* ���ַ����е�ĳ���Ӵ���ȫ�滻����һ���Ӵ� */
string& replace ( size_t pos1, size_t n1, const string& str );		
														//��str�滻this�ַ�����pos1λ�ÿ�ʼ��n1���ַ�
string& replace ( size_t pos1, size_t n1, const string& str, size_t pos2, size_t n2 ); 		
														//��str��pos2λ�ÿ�ʼ��n2���ַ��滻this�ַ�����pos1λ�ÿ�ʼ��n1���ַ�

