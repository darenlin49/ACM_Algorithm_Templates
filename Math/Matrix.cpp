/*
	类似整数快速幂模.
	几点注意事项：
		①矩阵乘法、快速幂是要注意保证乘法、加法不溢出(地方已标出)
		②一定要把每个矩阵的row,col都设置清楚……(这是模版比较挫的地方之一= =……)
*/


const int MAX = 30;
struct Mat{
    int row, col;
    LL mat[MAX][MAX];
};
//initialize square matrix to unit matrix
Mat unit(int n){
    Mat A;
    A.row = A.col = n;
    memset(A.mat, 0, sizeof(A.mat));
    for (int i = 0; i < n; i ++)
        A.mat[i][i] = 1;
    return A;
}
//return T(A)
Mat transpose(Mat A){
    Mat T;
    T.row = A.col;
    T.col = A.row;
    for (int i = 0; i < A.col; i ++)
        for (int j = 0; j < A.row; j ++)
            T.mat[i][j] = A.mat[j][i];
    return T;
}
//return (A+B)%mod
Mat add(Mat A, Mat B, int mod){
    Mat C = A;
    for (int i = 0; i < C.row; i ++)
        for (int j = 0; j < C.col; j ++)
            C.mat[i][j] = (A.mat[i][j] + B.mat[i][j]) % mod;
    return C;
}
//return (A-B)%mod
Mat dec(Mat A, Mat B, int mod){
    Mat C = A;
    for (int i = 0; i < C.row; i ++)
        for (int j = 0; j < C.col; j ++)
            C.mat[i][j] = (A.mat[i][j] - B.mat[i][j] + mod) % mod;
    return C;
}
//return A*B%mod
Mat mul(Mat A, Mat B, int mod){
    Mat C;
    C.row = A.row;
    C.col = B.col;
    for (int i = 0; i < A.row; i ++){
        for (int j = 0; j < B.col; j ++){
            C.mat[i][j] = 0;
            for (int k = 0; k < A.col; k ++)
                //注意这里要保证乘法不溢出，否则还需要设计特殊的乘法模
                C.mat[i][j] += A.mat[i][k] * B.mat[k][j];
            C.mat[i][j] %= mod;
        }
    }
    return C;
};
//return A^n%mod
Mat exp_mod(Mat A, int n, int mod){
    Mat res = unit(A.row);
    while(n){
        if (n & 1){
            res = mul(res, A, mod);
        }
        A = mul(A, A, mod);
        n >>= 1;
    }
    return res;
}
//return S = A^1 + A^2 + …… + A^n   (binary search)
Mat Sum(Mat A, int n, int mod){
    if (n == 0){
        Mat zero = A;
        memset(zero.mat, 0, sizeof(zero.mat));
        return zero;
    }
	if (n == 1)
        return A;
    if (n & 1){
        return add(Sum(A, n-1, mod), exp_mod(A, n, mod), mod);
    }
    else{
        return mul(Sum(A, n/2, mod), add(exp_mod(A, n/2, mod), unit(A.col), mod), mod);
    }
}