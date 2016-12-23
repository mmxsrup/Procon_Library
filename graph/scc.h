///強連結成分分解 (Kosaraju)///
#define MAX_V 10000//頂点数

int V;
vector<int> G[MAX_V], rG[MAX_V];
vector<int> vs;
bool used[MAX_V];
//cmp[v] = cmp[U]なら、頂点u, vは同じ強連結成分
//cmpに入っている番号は連結しているグラフごとに、トポロジカルソートされていて、ループ部分は同じ番号になっている。
int cmp[MAX_V];//cmp[v] := 頂点vが含まれる連結成分がどれなのかを示す番号
//隣接リストを作る
void add_edge(int from, int to){//0origin
	G[from].push_back(to);//与えられた有向グラフの隣接リスト
  	rG[to].push_back(from);//与えられたグラフの矢印を逆した有向グラフの隣接リスト
}
//一度目のdfs
void dfs(int v){
	used[v] = true;
	for (int i = 0; i < G[v].size(); ++i){
		if(!used[G[v][i]]) dfs(G[v][i]);
	}
	vs.push_back(v);//これ以上進めなくなったものから順にvsに頂点番号を入れていく
}
//2度目のdfs
void rdfs(int v, int k){
	used[v] = true;
	cmp[v] = k;//頂点vに対して、k番目と強連結成分であること入れる
	for (int i = 0; i < rG[v].size(); ++i){
		if(!used[rG[v][i]]) rdfs(rG[v][i], k);
	}
}
int scc(){
	memset(used, 0, sizeof(used));//0(使ってない)で初期化
	vs.clear();//初期化
	for (int v = 0; v < V; ++v){
		if(!used[v]) dfs(v);
	}
	memset(used, 0 , sizeof(used));
	int k = 0;//強連結成分を分ける番号
	for (int i = vs.size() - 1; i >= 0; --i){//vsに入っている後ろのものからdfs
		if(!used[vs[i]]){
			rdfs(vs[i], k); k++;
		}
	}
	return k;//強連結成分の数
}
