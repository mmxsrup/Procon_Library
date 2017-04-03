const int MAX_N = 200010;
vector<pair<int, ll> > G[MAX_N];
vector<ll> dijkstra(int start){
	vector<ll> dist(MAX_N, INFF);
	dist[start] = 0;//dist[i] :=　start->iまでの最短距離
	priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > >  que;
	que.push(make_pair(0, start));
	while(!que.empty()){
		ll cost; int u;//今までにかかった時間 現在の頂点
		cost = que.top().first, u = que.top().second;
		que.pop();
		if(dist[u] < cost) continue;
		for (auto tmp : G[u]){
			int v = tmp.first; ll time = tmp.second;//隣接する頂点 その頂点まで行く時間
			if(dist[v] > dist[u] + time){//u->v
				dist[v] = dist[u] + time;
				que.push(make_pair(dist[v], v));
			}
		}
	}
	return dist;
}

/*
http://joi2016yo.contest.atcoder.jp/tasks/joi2016yo_e
(http://joi2016yo.contest.atcoder.jp/submissions/1201083)
*/
