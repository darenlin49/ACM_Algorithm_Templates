void manacher(int *p,char *str,int n)			//p数组记录以每个字符为中心的最长回文半径，str是字符数组，为了把奇数偶数一块考虑，如果原数组是aabb，则str为$#a#a#b#b#,  n为str数组的长度
{
    int i;
    int mx = 0;
    int id;
    for(i=1; i<n; i++){
        if( mx > i )
            p[i] = min( p[2*id-i], mx-i );
        else
            p[i] = 1;
        for(; str[i+p[i]] == str[i-p[i]]; p[i]++);
        if( p[i] + i > mx ){
            mx = p[i] + i;
            id = i;
        }
    }
}