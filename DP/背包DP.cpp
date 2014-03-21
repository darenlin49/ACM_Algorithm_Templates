//01���� --- O(VN)
void zero_one_pack(int cost, int weight){
	for (int v = V; v >= cost; v --){
		f[v] = max(f[v], f[v-cost] + weight);
	}
}

for (int i = 1; i <= N; i ++)
	zero_one_pack(c[i], w[i]);
	
	
//��ȫ���� --- O(VN)
void complete_pack(int cost, int weight){
	for (int v = cost; v <= V; v ++){
		f[v] = max(f[v], f[v-cost] + weight);
	}
}

for (int i = 1; i <= N; i ++)
	complete_pack(c[i], w[i]);


//���ر��� --- O(VNlogni)
void multiple_pack(int cost, int weight, int amount){
	if (cost * amount >= V){
		complete(cost, weight);
		return ;
	}
	int k = 1;
	while(k < amount){
		zero_one_pack(k*cost, k*weight);
		amount -= k;
		k <<= 1;
	}
	zero_one_pack(amount*cost, amount*weight);
}


//��ϱ���

for (int i = 1; i <= N; i ++){
	if ��i����Ʒ����01����
		zero_one_pack(c[i], w[i]);
	else if ��i����Ʒ������ȫ����
		complete_pack(c[i], w[i]);
	else if ��i����Ʒ���ڶ��ر���
		multiple_pack(c[i], w[i], n[i]);
}


//�����Ա���(bool�ͱ���)��f[0] = 1.
void zero_one_pack(int V, int cost){
    for (int v = V; v >= cost; v --){
        if (f[v-cost])
            f[v] = 1;
    }
    return ;
}
void complete_pack(int V, int cost){
    for (int v = cost; v <= V; v ++){
        if (f[v-cost])
            f[v] = 1;
    }
}
void multiple_pack(int V, int cost, int amount){
    if (cost*amount >= V){
        complete_pack(V, cost);
        return ;
    }
    int k = 1;
    while(k < amount){
        zero_one_pack(V, k*cost);
        amount -= k;
        k <<= 1;
    }
    zero_one_pack(V, amount*cost);
    return ;
}


//���鱳����ÿ��ֻ��ѡһ����
for (int k = 1; k <= K; k ++)
	for (int v = V; v >= 0; v --)		//һάʱ���뵹�ţ���ά����ν
		for (i����k)
			dp[k][v] = max(dp[k][v], dp[k-1][v-cost[i]] + value[i]);		//����ʡ����һά

			
//���鱳�����Σ�ÿ������ѡһ����
for (int k = 1; k <= K; k ++)
	for (i����k)
		for (int v = V; v >= 0; v --){		//��ά��ֱ�Ӽ򵥣�һά��Ҫ���ǲ��ܴ�k-1�̳�״̬�����뵹��
			dp[k][v] = max(dp[k][v], dp[k][v-price[i]] + value[i]);		//����1��
			dp[k][v] = max(dp[k][v], dp[k-1][v-price[i]] + value[i]);	//ѡ��1��������ע��˳����Ϊprice����Ϊ0
		}