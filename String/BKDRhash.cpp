unsigned int BKDRHash(char *str){
    unsigned int seed = 31; 		// 31��131��1313��13131��etc��
    unsigned int hash = 0;
    while (*str)	hash = hash * seed + (*str++);
    return (hash & (0x7FFFFFFF));
}
//��Ҫ��ͻ����vectorģ��������