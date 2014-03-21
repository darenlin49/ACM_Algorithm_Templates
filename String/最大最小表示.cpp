/**
	【最大最小表示法】就是将字符串不断旋转，得到字典序最大或者最小的.
	min_max_express()函数：返回字典序最大\最小时的起始位置.
**/

#define MIN_EXPRESS 1	//flag值
#define MAX_EXPRESS 0
int min_max_express(char *s, bool flag){
    int len = strlen(s);
    int i = 0, j = 1, k = 0;
    while(i < len && j < len && k < len){
        int t = s[(j+k)%len] - s[(i+k)%len];
        if (t == 0) k ++;
        else{
            if (t > 0){
                if (flag){
                    j += k + 1;
                }
                else{
                    i += k + 1;
                }
            }
            else{
                if (flag){
                    i += k + 1;
                }
                else{
                    j += k + 1;
                }
            }
            if (i == j) j ++;
            k = 0;
        }
    }
    return min(i, j);
}