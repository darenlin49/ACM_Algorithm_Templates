//01背包 --- O(VN)
void zero_one_pack(int cost, int weight){
	for (int v = V; v >= cost; v --){
		f[v] = max(f[v], f[v-cost] + weight);
	}
}

for (int i = 1; i <= N; i ++)
	zero_one_pack(c[i], w[i]);
	
	
//完全背包 --- O(VN)
void complete_pack(int cost, int weight){
	for (int v = cost; v <= V; v ++){
		f[v] = max(f[v], f[v-cost] + weight);
	}
}

for (int i = 1; i <= N; i ++)
	complete_pack(c[i], w[i]);


//多重背包 --- O(VNlogni)
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


//混合背包

for (int i = 1; i <= N; i ++){
	if 第i件物品属于01背包
		zero_one_pack(c[i], w[i]);
	else if 第i件物品属于完全背包
		complete_pack(c[i], w[i]);
	else if 第i件物品属于多重背包
		multiple_pack(c[i], w[i], n[i]);
}


//可行性背包(bool型背包)，f[0] = 1.
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


//分组背包（每组只能选一个）
for (int k = 1; k <= K; k ++)
	for (int v = V; v >= 0; v --)		//一维时必须倒着，二维无所谓
		for (i属于k)
			dp[k][v] = max(dp[k][v], dp[k-1][v-cost[i]] + value[i]);		//可以省掉第一维

			
//分组背包变形（每组至少选一个）
for (int k = 1; k <= K; k ++)
	for (i属于k)
		for (int v = V; v >= 0; v --){		//二维更直接简单，一维还要考虑不能从k-1继承状态，必须倒着
			dp[k][v] = max(dp[k][v], dp[k][v-price[i]] + value[i]);		//大于1个
			dp[k][v] = max(dp[k][v], dp[k-1][v-price[i]] + value[i]);	//选择1个，并且注意顺序，因为price可能为0
		}