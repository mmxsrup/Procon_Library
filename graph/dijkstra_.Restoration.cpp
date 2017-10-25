const int MAX_N = 110;
using TYPE = double; // 距離の型を入れる
vector<pair<int, TYPE> > G[MAX_N];
 
pair<vector<TYPE>, vector<int>> dijkstra(int start, int goal){//スタートとゴールを逆に
    vector<TYPE> dist(MAX_N, INFF);
    vector<int> pre(MAX_N, -1);//pre[i] := iの前の頂点
    dist[start] = 0;//dist[i] :=　start->iまでの最短距離
    priority_queue<pair<TYPE, int>, vector<pair<TYPE, int> >, greater<pair<TYPE, int> > > que;
    que.push(make_pair(0, start));
    while(!que.empty()){
        TYPE cost; int u;//今までにかかった時間 現在の頂点
        cost = que.top().first, u = que.top().second;
        que.pop();
        if(dist[u] < cost) continue;
        for (auto tmp : G[u]){
            int v = tmp.first; TYPE time = tmp.second;//隣接する頂点 その頂点まで行く時間
            if(dist[v] > dist[u] + time){//u->v
                dist[v] = dist[u] + time;
                pre[v] = u;
                que.push(make_pair(dist[v], v));
            }
        }
    }
    if(dist[goal] == INFF) return make_pair(dist, vector<int>(1, -1)); // start->goalに経路がない場合
    //経路復元
    vector<int> path;
    int s = start, t = goal;
    for (; t != s; t = pre[t]) path.push_back(t);
    
    path.push_back(s);
    reverse(path.begin(), path.end());
    return make_pair(dist, path); //start-> * -> goal startからgoalまでの最短経路
}

/*
http://yukicoder.me/problems/no/160 (辞書順最小)
(https://yukicoder.me/submissions/142920) (goalからstartへ向かって)
http://arc011.contest.atcoder.jp/tasks/arc011_3
*/