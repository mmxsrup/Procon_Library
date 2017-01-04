const int MAX_N = 210;
vector<pair<int, int> > G[MAX_N];
vector<int> dijkstra(int start, int goal){//スタートとゴールを逆に
	vector<long long> dist(MAX_N, INF);
	vector<int> pre(MAX_N, -1);//pre[i] := iの前の頂点
    dist[start] = 0;//dist[i] :=　start->iまでの最短距離
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > que;
    que.push(make_pair(0, start));
    while(!que.empty()){
        int cost, u, t;//今までにかかった時間 現在の頂点
        cost = que.top().first, u = que.top().second;
        que.pop();
        if(dist[u] < cost) continue;
        for (auto tmp : G[u]){
            int v = tmp.first, time = tmp.second;//隣接する頂点 その頂点まで行く時間
            if(dist[v] > dist[u] + time){//u->v
            	dist[v] = dist[u] + time;
            	pre[v] = u;
            	que.push(make_pair(dist[v], v));
            }else if(dist[v] == dist[u] + time){//辞書順最小
            	pre[v] = min(pre[v], u);
            }
        }
    }
    //経路復元
    vector<int> path;
    int s = start, t = goal;
	for (; t != s; t = pre[t]) path.push_back(t);
	path.push_back(s);
	return path; //start-> * -> goal startからgoalまでの最短経路(辞書順最小)
}

/*
http://yukicoder.me/problems/no/160
*/