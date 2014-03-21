#include <iostream>
using namespace std;

/************************************************************************/
/* Name: GetExtendNext
/* Description: Get Next Array
/* Parameter List: mode - substring
/*                   next - array to get next[] of substring
/*                   strlen - string length of the substring
/************************************************************************/
void GetExtendNext(const char *mode, int *next, const int strlen)
{
    int a, p, j = -1;
    next[0] = 0;
    for (int i = 1; i < strlen; i++,j--)
    {
        if (j < 0 || i + next[i - a] >= p)
        {
            if (j < 0) j = 0, p = i;
            while (p < strlen && mode[p] == mode[j])
                ++p, ++j;
            next[i] = j, a = i;
        }
        else next[i] = next[i - a];
    }
}

/************************************************************************/
/* Name: GetExtend
/* Description: Get extend array
/* Parameter List: str - master string
/*                   strlen - master string length
/*                   extend - array to get extend array of str to mode
/*                   mode - substring
/*                   modeLen - substring length
/************************************************************************/
void GetExtend(const char *str, const int strlen, int *extend, const char *mode, const int modeLen)
{
    int *next = new int[modeLen];
    GetExtendNext(mode, next, modeLen);

    int a, p, j = -1; 
    for (int i = 0; i < strlen; i++,--j)
    {
        if (j < 0 || i + next[i - a] >= p)
        {
            if (j < 0) j = 0, p = i;
            while (p < strlen && j < modeLen && str[p] == mode[j])
                ++p, ++j;
            extend[i] = j, a = i;
        }
        else extend[i] = next[i - a];
    }
    delete []next;
}

int main()
{
    char *str = "abababccc";
    char *mode = "ababab";
    int extend[12];
    GetExtend(str, strlen(str), extend, mode, strlen(mode));
    return 0;
}