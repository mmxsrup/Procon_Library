class strongly_connected_components{
public:
	int group_cnt; // sccの数
	vector<vector<int> > G, rG;
	vector<int> used, vs;
	vector<int> cmp; //cmp[v] := 頂点vが含まれる連結成分がどれなのかを示す番号
	strongly_connected_components(const vector<vector<int> > &g, const vector<vector<int> > &rg, int n): 
		G(g), rG(rg), cmp(2 * n), used(2 * n){
		//mainの処理
		fill(used.begin(), used.end(), 0);
		for (int i = 0; i < G.size(); ++i){
			if(!used[i]) dfs(i);
		}
		fill(used.begin(), used.end(), 0);
		int k = 0;
		for (int i = vs.size() - 1; i >= 0; --i){
			if(!used[vs[i]]) rdfs(vs[i], k++);
		}
		group_cnt = k;
	}
	int operator[](int i){//連結成分の番号を返す
        return cmp[i];
    }
private:
	void dfs(int curr){
		used[curr] = true;
		for(auto next : G[curr]){
			if(!used[next]) dfs(next);
		}
		vs.push_back(curr);
	}
	void rdfs(int curr, int k){
		used[curr] = true;
		cmp[curr] = k;//頂点vに対して、k番目と強連結成分であること入れる
		for(auto next : rG[curr]){
			if(!used[next]) rdfs(next, k);
		}
	}
};

class twosatisfiability{
public:
	int V;
    vector<int> res; // 1:= 0:=
    vector<vector<int> > g, rg;
    twosatisfiability(int n) : V(n), g(2 * n), rg(2 * n), res(n){}

    bool exec() {
        strongly_connected_components scc(g, rg, V);
        for (int i = 0; i < V; i++) {
            if (scc[i] == scc[i + V]) return false;
            res[i] = scc[i] > scc[i + V];
        }
        return true;
    }
    void add_edge(int a, int b){
        g[a].push_back(b);
        rg[b].push_back(a);
    }
    //0~V-1: x_i
    //V~2V-1: notx_i
    void add(int a, bool apos, int b, bool bpos){//a V b をグラフへ
        add_edge(a + (apos ? V : 0), b + (bpos ? 0 : V)); // not a -> b
        add_edge(b + (bpos ? V : 0), a + (apos ? 0 : V)); // not b -> a
    }
    bool operator[](int k){
        return res[k];
    }
};

/*
http://yukicoder.me/problems/no/470
*/