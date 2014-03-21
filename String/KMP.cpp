	/*
	KMP-Template by AbandonZHANG @ 2013.08.30
*/
const int maxlen = 1000005;
struct StringMatching{
    char s[maxlen], p[maxlen];
    int next[maxlen];
    vector <int> match;
    void get_next(){
        int len = strlen(p);
        next[0] = -1;
        int j = -1;
        for(int i = 1; i < len; i ++){
            while(j > -1 && p[i] != p[j+1])   j = next[j];
            if (p[i] == p[j+1])   j ++;
            next[i] = j;
        }
    }
    int solve(){
        int num = 0, j = -1;
        get_next();
        int len1 = strlen(s), len2 = strlen(p);
        match.clear();
        for (int i = 0; i < len1; i ++){
            while(j > -1 && s[i] != p[j+1]) j = next[j];
            if (s[i] == p[j+1]) j ++;
            if (j == len2 - 1){
                num ++;                 //∆•≈‰¥Œ ˝
                match.push_back(i);     //∆•≈‰Œª÷√
                j = next[j];
            }
        }
        return num;
    }
}kmp;

