void manacher(int *p,char *str,int n)			//p�����¼��ÿ���ַ�Ϊ���ĵ�����İ뾶��str���ַ����飬Ϊ�˰�����ż��һ�鿼�ǣ����ԭ������aabb����strΪ$#a#a#b#b#,  nΪstr����ĳ���
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