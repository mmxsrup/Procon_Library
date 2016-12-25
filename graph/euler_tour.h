class Euler_Tour{
public:
	vector<vector<int> > g;
	//begin[v],end[v]はそれぞれvがオイラーツアー上で最初と最後に現れるインデックス
	//[begin[v], end[v])がvを根とする部分木
	vector<int> euler_tour, begin, end;
	Euler_Tour(int n) : g(n), begin(2 * n), end(2 * n){};//nは頂点数
	int k = 0, root = 0;
	void dfs(int curr, int par){//現在　parent
		begin[curr] = k;
		euler_tour.push_back(curr);
		k++;
		for(auto next : g[curr]){
			if(next == par) continue;
			dfs(next, curr);
			euler_tour.push_back(curr);
			k++;
		}
		end[curr] = k;
	}
};