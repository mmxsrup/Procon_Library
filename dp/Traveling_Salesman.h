const int MAX_N = 20;
vector<pair<int, int> > G[MAX_N]; /* G[u][v] := u->v's weight */
int dp[(1 << MAX_N)][MAX_N];
int pre[(1 << MAX_N)][MAX_N];
int Traveling_Salesman(int n){ /* n := Number of vertices */
	rep(i, (1 << n))rep(j, n)dp[i][j] = INF; /* Initialization */
	dp[0][0] = 0;
	for (int mask = 0; mask < (1 << n); ++mask){
		for (int u = 0; u < n; ++u){ /* Current vertex */
			for(auto p : G[u]){ /* Next vertex */
				int v = p.first, w = p.second;
				if((mask & (1 << v)) == 0){
					if(dp[mask | (1 << v)][v] > dp[mask][u] + w){
						dp[mask | (1 << v)][v] = dp[mask][u] + w;
						pre[mask | (1 << v)][v] = u;
					}
				}
			}
		}
	}
	return dp[(1 << n) - 1][0];
}
vector<int> Restoration(int n){
	vector<int> root;
	int mask = (1 << n) - 1, v = 0;
	root.push_back(v);
	while(mask != 0){
		int u = pre[mask][v]; /* u -> v */
		root.push_back(u);
		mask ^= (1 << v);
		v = u;
	}
	reverse(root.begin(), root.end());
	return root;	
}

/*
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_2_A
経路復元は検証していない
*/