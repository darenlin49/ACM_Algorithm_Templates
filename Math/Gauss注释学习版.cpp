/*
	Ⅰ.(我们设方程组中方程的个数为equ，变元的个数为var，注意：一般情况下是n个方程，n个变元，但是有些题目就故意让方程数与变元数不同)

	1. 把方程组转换成增广矩阵。
	
	2. 利用初等行变换来把增广矩阵转换成行阶梯阵。
	枚举k从0到equ–1，当前处理的列为col(初始为0)，每次找第k行以下(包括第k行)，col列中元素绝对值最大的列与第k行交换。如果col列中的元素全为0，那么则处理col + 1列，k不变。
	
	3. 转换为行阶梯阵，判断解的情况。
	① 无解
	当方程中出现(0, 0, …, 0, a)的形式，且a != 0时，说明是无解的。
	② 唯一解
	条件是k = equ，即行阶梯阵形成了严格的上三角阵。利用回代逐一求出解集。
	③ 无穷解。
	条件是k < equ，即不能形成严格的上三角形，自由变元的个数即为equ – k，但有些题目要求判断哪些变元是不缺定的。
	这里单独介绍下这种解法：
	首先，自由变元有var-k个，即不确定的变元至少有var-k个（注意不确定变元和自由变元的区别！）。我们先把所有的变元视为不确定的。在每个方程中判断不确定变元的个数，如果大于1个，则该方程无法求解。如果只有1个变元，那么该变元即可求出，即为确定变元。

	Ⅱ.解异或方程也可以套用高斯消元法，只须将原来的加减操作替换成异或操作就可以了，两个方程的左边异或之后，它们的公共项就没有了。
具体的操作方法是这样的：对于k=0..N-1，找到一个M[i][k]不为0的行i，把它与第k行交换，用第k行去异或下面所有M[i][j]不为0的行i，消去它们的第k个系数，这样就将原矩阵化成了上三角矩阵；最后一行只有一个未知数，这个未知数就已经求出来了，用它跟上面所有含有这个未知数的方程异或，就消去了所有的着个未知数，此时倒数第二行也只有一个未知数，它就被求出来了，用这样的方法可以自下而上求出所有未知数。

*/


#include <iostream>
#include <string>
#include <cmath>
using namespace std;
const int maxn = 105;
int equ, var; 	// 有equ个方程，var个变元。增广阵行数为equ, 分别为0到equ - 1，列数为var + 1，分别为0到var.
int a[maxn][maxn];
int x[maxn]; 	// 解集.
bool free_x[maxn]; 	// 判断是否是不确定的变元.
int free_num;
void Debug(void)
{
    int i, j;
    for (i = 0; i < equ; i++)
    {
        for (j = 0; j < var + 1; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
inline int gcd(int a, int b)
{
    int t;
    while (b != 0)
    {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}
inline int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}
//高斯消元法解方程组(Gauss-Jordanelimination).(-2表示有浮点数解，但无整数解，-1表示无解，0表示唯一解，大于0表示无穷解，并返回自由变元的个数)
int Gauss(void)
{
    int i, j, k;
	int max_r; 		// 当前这列绝对值最大的行.
	int col; 		// 当前处理的列.
    int ta, tb;
    int LCM;
    int temp;
    int free_x_num;
    int free_index;
    // 转换为阶梯阵.
    col = 0; // 当前处理的列.
    for (k = 0; k < equ && col < var; k++, col++)
    { // 枚举当前处理的行.
        // 找到该col列元素绝对值最大的那行与第k行交换.(为了在除法时减小误差)
        max_r = k;
        for (i = k + 1; i < equ; i++)
        {
            if (abs(a[i][col]) > abs(a[max_r][col])) max_r = i;
        }
        if (max_r != k)
        { // 与第k行交换.
            for (j = k; j < var + 1; j++) swap(a[k][j], a[max_r][j]);
        }
        if (a[k][col] == 0)
        { // 说明该col列第k行以下全是0了，则处理当前行的下一列.
            k--; 		
			continue;
        }
        for (i = k + 1; i < equ; i++)
        { // 枚举要删去的行.
            if (a[i][col] != 0)
			{
                LCM = lcm(abs(a[i][col]), abs(a[k][col]));
                ta = LCM / abs(a[i][col]), tb = LCM / abs(a[k][col]);
                if (a[i][col] * a[k][col] < 0) tb = -tb; // 异号的情况是两个数相加.
                for (j = col; j < var + 1; j++)
                {
                    a[i][j] = a[i][j] * ta - a[k][j] * tb;
                }
			}
        }
    }
    Debug();
    // 1. 无解的情况: 化简的增广阵中存在(0, 0, ..., a)这样的行(a != 0).
    for (i = k; i < equ; i++)
    { 	// 对于无穷解来说，如果要判断哪些是自由变元，那么初等行变换中的交换就会影响，则要记录交换.
        if (a[i][col] != 0) return -1;
    }
    // 2. 无穷解的情况: 在var * (var + 1)的增广阵中出现(0, 0, ..., 0)这样的行，即说明没有形成严格的上三角阵.
    // 且出现的行数即为自由变元的个数.
	// 这里只是计算出了确定变元，对于多解的计算，需要枚举自由变元的状态或者其他方法求解.
    if (k < var)
    {
        // 首先，自由变元有var - k个，即不确定的变元至少有var - k个.（注意 不确定变元 和 自由变元 的区别！）
        for (i = k - 1; i >= 0; i--)
        {
            // 第i行一定不会是(0, 0, ..., 0)的情况，因为这样的行是在第k行到第equ行.
            // 同样，第i行一定不会是(0, 0, ..., a), a != 0的情况，这样的无解的.
            free_x_num = 0; // 用于判断该行中的不确定的变元的个数，如果超过1个，则无法求解，它们仍然为不确定的变元.
            for (j = 0; j < var; j++)
            {
                if (a[i][j] != 0 && free_x[j]) free_x_num++, free_index = j;
            }
            if (free_x_num > 1) continue; // 无法求解出确定的变元.
            // 说明就只有一个不确定的变元free_index，那么可以求解出该变元，且该变元是确定的.
            temp = a[i][var];
            for (j = 0; j < var; j++)
            {
                if (a[i][j] != 0 && j != free_index) temp -= a[i][j] * x[j];
            }
            x[free_index] = temp / a[i][free_index]; // 求出该变元.
            free_x[free_index] = 0; // 该变元是确定的.
        }
        return var - k; // 自由变元有var - k个.
    }
    // 3. 唯一解的情况: 在var * (var + 1)的增广阵中形成严格的上三角阵.
    // 计算出Xn-1, Xn-2 ... X0.
    for (i = var - 1; i >= 0; i--)
    {
        temp = a[i][var];
        for (j = i + 1; j < var; j++)
        {
            if (a[i][j] != 0) temp -= a[i][j] * x[j];
        }
        if (temp % a[i][i] != 0) return -2; // 说明有浮点数解，但无整数解.
        x[i] = temp / a[i][i];
    }
	return 0;
}
int main(void)
{
    freopen("Input.txt", "r", stdin);
    int i, j;
    while (scanf("%d %d", &equ, &var) != EOF)
    {
        memset(a, 0, sizeof(a));
		memset(x, 0, sizeof(x));
		memset(free_x, 1, sizeof(free_x)); // 一开始全是不确定的变元.
        for (i = 0; i < equ; i++)
        {
            for (j = 0; j < var + 1; j++)
            {
                scanf("%d", &a[i][j]);
            }
        }
//        Debug();
        free_num = Gauss();
        if (free_num == -1) printf("无解!\n");
	else if (free_num == -2) printf("有浮点数解，无整数解!\n");
        else if (free_num > 0)
        {
            printf("无穷多解! 自由变元个数为%d\n", free_num);
            for (i = 0; i < var; i++)
            {
                if (free_x[i]) printf("x%d 是不确定的\n", i + 1);
                else printf("x%d: %d\n", i + 1, x[i]);
            }
        }
        else
        {
            for (i = 0; i < var; i++)
            {
                printf("x%d: %d\n", i + 1, x[i]);
            }
        }
        printf("\n");
    }
    return 0;
}