class DisjointSet{
public:
	vector<int> rank, p;//rank:木の高さ p:親の頂点番号
	DisjointSet(){}
	DisjointSet(int size){//頂点の数
		rank.resize(size, 0);
		p.resize(size, 0);
		rep(i, size) makeSet(i);
	}
	bool same(int x, int y){ //同じ木にあるか
		return findSet(x) == findSet(y);
	}
	void unite(int x, int y){ // 木どうしをくっつける
		link(findSet(x), findSet(y));
	}
private:
	void makeSet(int x){
		p[x] = x;
		rank[x] = 0;
	}
	int findSet(int x){ //親を探す（ルートまで）
		if(x != p[x]){
			p[x] = findSet(p[x]);
		}
		return p[x];
	}
	void link(int x, int y){ //木の高さを考慮して木どうしをくっつける
		if(rank[x] > rank[y]){
			p[y] = x;
		}else{
			p[x] = y;
			if(rank[x] == rank[y]) rank[y]++;
		}
	}
};

/*
http://abc049.contest.atcoder.jp/tasks/arc065_b
*/