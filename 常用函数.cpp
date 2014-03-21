/* ======================================================= 数值计算 ======================================================= */

/* 返回大于或者等于指定表达式的最小整数 */
double ceil(double x);


/* ======================================================= 字符串 ======================================================= */

/* 查找完全匹配的子字符串 */
extern char *strstr( char *str1, char *str2 );
size_t string::find( const string& str, size_t pos = 0 ) const;
size_t string::find( char c, size_t pos = 0 ) const;

/* 提取从某个位置开始, 长度为l的子串 */
string substr ( size_t pos = 0, size_t n = npos ) const;

/* 把字符串中的某个子串完全替换成另一个子串 */
string& replace ( size_t pos1, size_t n1, const string& str );		
														//用str替换this字符串从pos1位置开始的n1个字符
string& replace ( size_t pos1, size_t n1, const string& str, size_t pos2, size_t n2 ); 		
														//用str中pos2位置开始的n2个字符替换this字符串从pos1位置开始的n1个字符

