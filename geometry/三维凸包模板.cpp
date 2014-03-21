﻿/*
  
* HDU 3662 3D Convex Hull
  * 
输入点数n (n <= 500),之后输入n个三维点,求面数
  
*/


const int maxn = 505;
typedef double db;
const db eps = 1e-8;
int sign( db x) 	{return x < -eps ? -1 : x > eps;}
db sqr(db x)		{return x * x;}

struct TPoint3
{
	db x, y, z;
	TPoint3(){}  
	TPoint3(db x, db y, db z): x(x), y(y), z(z){} 
	TPoint3 operator - (const TPoint3 p)	{return TPoint3(x - p.x, y - p.y, z - p.z);}
	TPoint3  X (TPoint3 p)	{return TPoint3(y*p.z-z*p.y, z*p.x-x*p.z, x*p.y-y*p.x);}
	db  O (TPoint3 p)	{return x*p.x+y*p.y+z*p.z;}
	db len()		{return sqrt(sqr(x) + sqr(y) + sqr(z));}
	bool operator == (TPoint3 p){
		return fabs(p.x -x) < eps && fabs(p.y - y) < eps && fabs(p.z - z) < eps;
	}
	void get()		{scanf("%lf%lf%lf", &x, &y, &z);}
};



struct Convex
{
    
	// 剖分出来的三角面的点逆时针存储...
    
	struct fac
	{
        
		int a, b, c;    
        
		bool ok;
    
	}add, F[maxn*4];
    
	
	TPoint3  P[maxn] ;
    
	int n, cnt, cou;
    
	int to[maxn][maxn];
    
	bool v[ maxn * 4];
    //请在使用前先初始化....
    
	
	void INIT()
	{
        
		cnt = cou = 0;
        
		memset(to ,0 ,sizeof to);
        
		memset(v, 0, sizeof v) ;
    
	}
    
	
	bool dotsInLine(TPoint3 p1,TPoint3 p2,TPoint3 p3)	{
        return (p2-p1).X(p3-p1).len() <eps;
    }
    
	db ptof(TPoint3 &p, fac &f)    
	{
        
		TPoint3 m = P[f.b]-P[f.a], n = P[f.c]-P[f.a], t = p-P[f.a];
        
		return m .X( n) .O(t); 
    
	}    

    
	void deal(int p, int a, int b)
	{
        
		int f = to[a][b];
        
		if (F[f].ok)
		{
            
			if (ptof(P[p], F[f]) > -eps) 
				dfs(p, f);
            
			else
			{
                
				add.a = b, add.b = a, add.c = p, add.ok = 1;
                
				to[p][b] = to[a][p] = to[b][a] = cnt;
                
				F[cnt++] = add;
            
			}
        
		}
    
	}

    
	void dfs(int p, int cur)
	{
        
		F[cur].ok = 0;
        
		deal(p, F[cur].b, F[cur].a);
        
		deal(p, F[cur].c, F[cur].b);
        
		deal(p, F[cur].a, F[cur].c);
    
	}

    
	void init()
	{
        
		int i;
        
		for(cou = i = 1; i < n; i++)
			switch(cou)
			{
                
				case 1:
                    
					if(P[0] == P[i]) 	break;
                    
					swap(P[cou++], P[i]);
	break;
                
				case 2:
                    
					if(dotsInLine(P[0], P[1], P[i]))	break;
                    
					swap(P[cou++], P[i]);
                    
					add.a = 0, add.b = 1, add.c = 2;
	break;
                
				case 3:
                    
					if( sign(ptof(P[i], add))==0 )	break;
                    
					swap(P[cou++], P[i]);
		break;
                
				default:	;
            
			}
    
	}

    
	void convex()
	{
        
		int i, j;
        
		init();
        
		
		if(cou < 4)
		{/*....deal...*/}
        
        
		
		for(cnt = i = 0; i < 4; i++)
		{
            
			add.a = (i+1)%4, add.b = (i+2)%4, add.c = (i+3)%4, add.ok = 1;
            
			if (ptof(P[i], add) > 0) swap(add.b, add.c);
            
			to[add.a][add.b] = to[add.b][add.c] = to[add.c][add.a] = cnt;
            
			F[cnt++] = add;
        
		}
        
		for (i = 4; i < n; i++)
            
			for (j = 0; j < cnt; j++)
                
				if (F[j].ok && ptof(P[i], F[j]) > eps)
				{
                    
					dfs(i, j);
                    
					break;
                
				}
        
		for(i = j = 0; i < cnt; i++) 
			if(F[i].ok)F[j++] = F[i]; cnt = j;
    
	}
    

	// 返回三维凸包表面积...
    
	db get_sur() 
	{
        
		db ans = 0.0;
        
		for(int i = 0; i < cnt; i++) 
			ans += fabs((P[F[i].b] - P[F[i].a]).X(P[F[i].c] - P[F[i].a]).len()) / 2.0 ;
        
		return ans ;
    
	}    
    
	vector<TPoint3> getvec(int x)
	{ 	//保证传入的为顺时针...
        
		vector< TPoint3> ret;
        
		ret.push_back(P [F[x] . c]) ;
        
		ret.push_back(P [F[x] . b]) ;
        
		ret.push_back(P [F[x] . a]) ;
        
		return ret;
    
	}
    
	db get_vol_f( vector<TPoint3> p) 
	{
        
		double vol = 0;
        
		for (int i = 0; i < p.size(); ++i) 
		{
            
			TPoint3 p1 = p[i] - p.front(), p2 = (i + 1 == p.size() ? p.front() : p[i + 1]) - p.front();
            
			vol += p1 .X( p2) .O( p.front() );
        
		}
        
		return vol / 6.0;
    
	}
    

	//返回三维凸包体积...
    
	db get_vol() 
	{
        
		double vol = 0;
        
		for (int i = 0; i < cnt; ++i)
            
			vol += get_vol_f( getvec(i) );
        
		return fabs(vol);
    
	}

    
	void show()
	{
        
		for(int i = 0; i < cnt; i++) 
			printf("%d %d %d\n",F[i].a, F[i].b, F[i].c); 
		//返回的是凸包上的三角形(点的编号) ...
    
	}
    

	void Read()
	{
        
		int i;
        
		for(i = 0; i < n; ++ i) 
			P[i].get() ;
    
	}
    
	
	bool same(int x, int y)
	{
        
		return sign(ptof(P[ F[x].a ], F[y])) == 0 &&
  sign(ptof(P[ F[x].b ], F[y])) == 0 && 
sign(ptof(P[ F[x].c ], F[y])) == 0 ;
    
	}
    

	// 获得面数...
    
	int get_fac_cnt()
	{
        
		int ans = 0;
        
		for (int i = 0; i < cnt; i++)
		{
            
			bool nb = 1;
            
			for (int j = 0; j < i; j++)
			{
                
				if (same(i, j))
				{
                    
					nb = 0;
                    
					break;
                
				}
            
			}
            
			ans += nb;
        
		}
        
		return ans;
    
	}    
	

};


Convex C;


int main()
{
    
	while(~ scanf("%d", &C.n)) 
	{
        
		C.INIT();
        
		C.Read();
        
		C.convex();
        
		printf("%d\n", C.get_fac_cnt() );
    
	}

    	return 0;

}