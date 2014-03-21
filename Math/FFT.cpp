/**
	快速傅立叶变换(FFT):
		1.O(NlogN)时间计算多项式乘法 A\B = ∑(ai*x^i), C = ∑(cj*x^j), cj = ∑(a[i]+b[j-i])
		2.O(NlogN)时间计算卷积：r(k) = ∑(a[i]*b[i-k])
	（输入输出均为系数向量形式）
**/

/* ============================ FFT 递归算法 =============================== */
const double eps = 1e-8;
const double pi = acos(-1.0);
typedef complex <double> cp;     //include header <complex>
struct FastFourierTransform{
    inline int dcmp(double a){if (a<-eps) return -1; return (a>eps); }

    void fft(cp *x, int n, cp *y, int bInv){        //y = Wx,  w[j,k] = e^ijk
        if (n == 1){ y[0] = x[0]; return; }
        cp *xeven = new cp[n/2], *xodd = new cp[n/2], w(1, 0),
            *yeven = new cp[n/2], *yodd = new cp[n/2], wn;
        if (bInv)   wn = cp( cos(-2*pi/n), sin(-2*pi/n) );
        else    wn = cp( cos(2*pi/n), sin(2*pi/n) );
        for (int i = 0; i < n/2; i ++){
            xeven[i] = x[i*2];
            xodd[i] = x[i*2+1];
        }
        fft(xeven, n/2, yeven, bInv);
        fft(xodd, n/2, yodd, bInv);
        for (int i = 0; i < n/2; i ++){             //蝴蝶操作
            y[i] = yeven[i] + w*yodd[i];
            y[i+n/2] = yeven[i] - w*yodd[i];
            w *= wn;
        }
        delete xeven;   delete xodd;    delete yeven;   delete yodd;
    }
    //O(nlogn) PolyMulti
    void PolyMulti(double *a, int na, double *b, int nb, double *c, int &nc){
        int n = (na > nb) ? na : nb;
        n = 1 << ((int)ceil(log(2.0*n)/log(2.0)-eps));
        cp *x = new cp[n], *ya = new cp[n], *yb = new cp[n], *yc = new cp[n];
        for (int i = 0; i < n; i ++)    x[i] = (i<na)?a[i]:0;   fft(x, n, ya, 0);
        for (int i = 0; i < n; i ++)    x[i] = (i<nb)?b[i]:0;   fft(x, n, yb, 0);
        for (int i = 0; i < n; i ++)    yc[i] = ya[i]*yb[i];    fft(yc, n, x, 1);
        for (int i = 0; i < n; i ++)    c[i] = x[i].real()/n;
        for (nc = n; nc > 0 && dcmp(c[nc-1]) == 0; nc--);
        delete x;   delete ya;  delete yb;  delete yc;
    }
	//Convolution: r(k) = sigma(a[i]*b[i-k]){i=0~n-1}
    //N must be power of 2
    void Convolution(int *a, int *b, int *c, int n){
        cp *x = new cp[n], *ya = new cp[n], *yb = new cp[n], *yc = new cp[n];
        x[0] = b[0];
        for (int i = 1; i < n; i ++)    x[i] = (i<n)?b[n-i]:0;  fft(x, n, yb, 0);
        for (int i = 0; i < n; i ++)    x[i] = (i<n)?a[i]:0;    fft(x, n, ya, 0);
        for (int i = 0; i < n; i ++)    yc[i] = ya[i] * yb[i];  fft(yc, n, x, 1);
        for (int i = 0; i < n; i ++)    c[i] = int(x[i].real()/n+0.5);
        delete x;   delete ya;  delete yb;  delete yc;
    }
}FFT;

/* ============================ FFT 迭代算法 （省时省空间） =============================== */
const double eps = 1e-8;
const double Pi = acos(-1.0);
struct complex{
    double r,i;
    complex(double _r = 0,double _i = 0){
        r = _r; i = _i;
    }
    complex operator +(const complex &b){
        return complex(r+b.r,i+b.i);
    }
    complex operator -(const complex &b){
        return complex(r-b.r,i-b.i);
    }
    complex operator *(const complex &b){
        return complex(r*b.r-i*b.i,r*b.i+i*b.r);
    }
};
struct FastFourierTransform{
    inline int dcmp(double a){  if (a<-eps) return -1; return (a>eps);  }
    void ReverseBits(complex *y, int len){
        int i,j,k;
        for(i = 1, j = len>>1; i < len-1; i ++){
            if(i < j)   swap(y[i], y[j]);
            k = len >> 1;
            while(j >= k){
                j -= k;
                k >>= 1;
            }
            if(j < k)   j += k;
        }
    }
	//系数表示法和点值表示法的转换
    void fft(complex *y, int len, bool bInv){
        ReverseBits(y,len);
        for(int h = 2; h <= len; h <<= 1){                  // 控制层数
            int on = bInv ? 1 : -1 ;
            complex wn( cos(-on*2*Pi/h),sin(-on*2*Pi/h) );
            for(int j = 0; j < len; j += h){
                complex w(1,0);
                for(int k = j; k < j+h/2; k++){
                    complex u = y[k];
                    complex t = w*y[k+h/2];
                    y[k] = u+t;
                    y[k+h/2] = u-t;
                    w = w*wn;
                }
            }
        }
        if(bInv == true)
            for(int i = 0;i < len;i++)
                y[i].r /= len;
    }
    //O(nlogn) PolyMulti.	a,b,c是多项式的系数向量
    void PolyMulti(int *a, int na, int *b, int nb, long long *c, int &nc){
        int n = (na > nb) ? na : nb;
        nc = 1;
        while(nc < (2*n))   nc <<= 1;
        complex *ya = new complex[nc], *yb = new complex[nc], *yc = new complex[nc];
        for (int i = 0; i < na; i ++)    ya[i] = complex(a[i], 0);  fft(ya, nc, false);
        for (int i = 0; i < nb; i ++)    yb[i] = complex(b[i], 0);  fft(yb, nc, false);
        for (int i = 0; i < nc; i ++)    yc[i] = ya[i]*yb[i];       fft(yc, nc, true);
        for (int i = 0; i < nc; i ++)    c[i] = (long long)(yc[i].r+0.5);

        // for (; nc > 0 && dcmp(c[nc-1]) == 0; nc--);
        // 这句加上时间还多了，不知道算不算优化……
        delete ya;  delete yb;  delete yc;
    }
    //Convolution: r(k) = sigma(a[i]*b[i-k]){i=0~n-1}
    void Convolution(int *a, int *b, int *r, int n){
        complex *d1 = new complex[n], *d2 = new complex[n], *y = new complex[n];
        d1[0] = b[0];
        int nc = 1;		
		// nc must be power of 2
        while(nc < (2 * n)) nc <<= 1;
        for (int i = 1; i < n; i ++)    d1[i] = b[n-i];         fft(d1, nc, false);
        for (int i = 0; i < n; i ++)    d2[i] = a[i];           fft(d2, nc, false);
        for (int i = 0; i < n; i ++)    y[i] = d1[i] * d2[i];   fft(y, nc, true);
        for (int i = 0; i < n; i ++)    r[i] = int(y[i].r+0.5);
        delete d1;  delete d2;  delete y;
    }
}FFT;