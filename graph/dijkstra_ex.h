int dist[110][30]; // tyouten time := cost
using tup = tuple<int, int, int>;
int dijkstra(int start, int goal, int limit){
    dist[start][0] = 0;
    rep(i, 110)rep(j, 30) dist[i][j] = INF;
    priority_queue<tup, vector<tup>, greater<tup>> que; // cost v time
    que.push(make_tuple(0, start, 0));
    while(!que.empty()) {
        int cost, u, time; tie(cost, u, time) = que.top(); que.pop();
        //cout << "cost u time " << cost << " " << u << " " << time << endl;
        if(u == goal) return cost;
        if(dist[u][time] < cost) continue;
        for(auto tmp : G[u]) {
            int v, nc, nt; tie(v, nc, nt) = tmp;
            int ncost = cost + nc;
            int ntime = time + nt;
            if(ntime > limit) continue;
            if(dist[v][ntime] > ncost) {
                dist[v][ntime] = ncost;
                que.push(make_tuple(ncost, v, ntime));
            }
        }
    }
    return INF; // -1
}

/*
aoj 2585
*/