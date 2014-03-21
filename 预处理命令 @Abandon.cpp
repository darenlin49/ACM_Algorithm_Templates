#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#define MID(x,y) ((x+y)/2)
#define MEM(a,b) memset(a,b,sizeof(a))
#define SIZE(Q) ( (int)Q.size() )
#define CLEAR(Q) while(!Q.empty())  Q.pop();
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;

typedef long long LL;
typedef vector <int> VI;
typedef set <int> SETI;
typedef queue <int> QI;
typedef stack <int> SI;
const int oo = 0x3fffffff;
const double doo = 1e18;
/** 浮点关系运算 **/
const double eps = 1e-8;
bool dy(double x,double y)  {   return x > y + eps;} 		// x > y
bool xy(double x,double y)  {   return x < y - eps;} 		// x < y
bool dyd(double x,double y) {   return x > y - eps;} 		// x >= y
bool xyd(double x,double y) {   return x < y + eps;}     	// x <= y
bool dd(double x,double y)  {   return fabs( x - y ) < eps;}    // x == y