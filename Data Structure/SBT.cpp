const int maxn= 100010;

class SBT{
public:
    void Clear(){
        memset(K,0,sizeof(K));
        memset(L,0,sizeof(L));
        memset(R,0,sizeof(R));
        memset(S,0,sizeof(S));
        RT= SZ= 0;
    }
    void MLR()  { printf("----------------\n"); MLR(RT);}	//前序遍历SBTree，每行输出（当前子树的根，~左子树，~右子树------输出方式可自己更改）
    void Insert(int key)    {Insert(RT,key);}			//在SBTree中插入键值为v的结点
    int Delete(int key)     {return Delete(RT,key);}		//在SBTree中删除键值为v的结点
    int Succ(int key)       {return Succ(RT,key);}		//返回SBTree中比v大的最小的键值	
    int Pred(int key)       {return Pred(RT,key);}		//返回SBTree中比v小的最大的键值
    int Rank(int key)       {return Rank(RT,key);}		//返回SBTree中键值v的排名。也就是树中键值比v小的结点数+1
    int Find(int key)       {return Find(RT,key);}		//在SBTree中查找键值为v的结点
    int Select(int key)     {return Select(RT,key);}		//返回SBTree中排名为k的结点的值。同时该操作能够实现Get-min,Get-max,因为Get-min等于Select(1),Get-max等于Select(s[t])
    
private:
    int K[maxn];		//键值
    int L[maxn];		//左子树结点
    int R[maxn];		//右子树结点
    int S[maxn];		//子树结点个数
    int RT, SZ;
    void LeftRotate(int &x){
        int k= R[x];
        R[x]= L[k];
        L[k]=  x;
        S[k]= S[x];
        S[x]= S[L[x]]+S[R[x]]+1;
        x= k;
    }
    void RightRotate(int &x){
        int k= L[x];
        L[x]= R[k];
        R[k]= x;
        S[k]= S[x];
        S[x]= S[L[x]]+S[R[x]]+1;
        x= k;
    }
     void MaintainFat(int &t){
        if (S[L[L[t]]]>S[R[t]]){
            RightRotate(t);
            MaintainFat(R[t]);
            MaintainFat(t);
            return;
        }
        if (S[R[L[t]]]>S[R[t]]){
            LeftRotate(L[t]);
            RightRotate(t);
            MaintainFat(L[t]);
            MaintainFat(R[t]);
            MaintainFat(t);
            return;
        }
        if (S[R[R[t]]]>S[L[t]]){
            LeftRotate(t);
            MaintainFat(L[t]);
            MaintainFat(t);
            return;
        }
        if (S[L[R[t]]]>S[L[t]]){
            RightRotate(R[t]);
            LeftRotate(t);
            MaintainFat(L[t]);
            MaintainFat(R[t]);
            MaintainFat(t);
            return;
        }

    }
    void Maintain(int &t, int flag){
        if (!flag){
            if (S[L[L[t]]] >S[R[t]])
                RightRotate(t);
            else if (S[R[L[t]]] >S[R[t]]){
                LeftRotate(L[t]);
                RightRotate(t);
            }
            else
                return;
        }
        else{
            if (S[R[R[t]]] >S[L[t]])
                LeftRotate(t);
            else if (S[L[R[t]]] >S[L[t]]){
                RightRotate(R[t]);
                LeftRotate(t);
            }
            else
                return;
        }
        Maintain(L[t], false);
        Maintain(R[t], true);
        Maintain(t, true);
        Maintain(t, false);
    }
    void Insert(int &t, int key){
        if (t==0){
            t= ++SZ;
            K[t]= key;
            S[t]= 1;
            return;
        }
        S[t]++;
        if (key<K[t])
            Insert(L[t],key);
        else
            Insert(R[t],key);
        Maintain(t,key>K[t]);

    }
    int Delete(int &t, int key){
        S[t]--;
        if ((key==K[t])||(key<K[t]&&L[t]==0)||(key>K[t]&&R[t]==0)){
            int ret= K[t];
            if (L[t]==0 || R[t]==0)
                t= L[t]+R[t];       // T change to his Leftson or Rightson
            else
                K[t]= Delete(L[t], K[t]+1); // Not find then delete the last find Point
            return ret;
        }
        else{
            if (key<K[t])
                return Delete(L[t],key);
            else
                return Delete(R[t],key);
        }

    }
    int Find(int t, int key){     //return root point
        if (t==0 || key==K[t])
            return t;
        if (key<K[t])
            return Find(L[t],key);
        else
            return Find(R[t],key);

    }
    int Select(int t, int k){       // return K-th int tree
        int num= S[L[t]]+1;
        if (k==num)
            return K[t];
        else if (k<num)
            return Select(L[t],k);
        else
            return Select(R[t],k-num);

    }
    int Succ(int t, int key){
        if (t==0)
            return key;
        if (key>=K[t])                 //
            return Succ(R[t], key);
        else{
            int r= Succ(L[t], key);
            if (r==key)
                return K[t];
            else
                return r;
        }

    }
    int Pred(int t, int key){
        if (t==0)
            return key;
        if (key<=K[t])                 //
            return Pred(L[t], key);
        else {
            int r= Pred(R[t], key);
            if (r==key)
                return K[t];
            else
                return r;
        }

    }
    int Rank(int t, int key){
        if (t==0)
            return 1;
        if (key<=K[t])           //
            return Rank(L[t], key);
        else if (key>K[t])
            return S[L[t]]+1+Rank(R[t],key);

    }
    void MLR(int t){
        if (t==0)   return;
        printf(" %d  % d  %d\n", K[t], K[L[t]], K[R[t]] );
        MLR(L[t]);
        MLR(R[t]);
    }


};