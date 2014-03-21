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
    void MLR()  { printf("----------------\n"); MLR(RT);}	//ǰ�����SBTree��ÿ���������ǰ�����ĸ���~��������~������------�����ʽ���Լ����ģ�
    void Insert(int key)    {Insert(RT,key);}			//��SBTree�в����ֵΪv�Ľ��
    int Delete(int key)     {return Delete(RT,key);}		//��SBTree��ɾ����ֵΪv�Ľ��
    int Succ(int key)       {return Succ(RT,key);}		//����SBTree�б�v�����С�ļ�ֵ	
    int Pred(int key)       {return Pred(RT,key);}		//����SBTree�б�vС�����ļ�ֵ
    int Rank(int key)       {return Rank(RT,key);}		//����SBTree�м�ֵv��������Ҳ�������м�ֵ��vС�Ľ����+1
    int Find(int key)       {return Find(RT,key);}		//��SBTree�в��Ҽ�ֵΪv�Ľ��
    int Select(int key)     {return Select(RT,key);}		//����SBTree������Ϊk�Ľ���ֵ��ͬʱ�ò����ܹ�ʵ��Get-min,Get-max,��ΪGet-min����Select(1),Get-max����Select(s[t])
    
private:
    int K[maxn];		//��ֵ
    int L[maxn];		//���������
    int R[maxn];		//���������
    int S[maxn];		//����������
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