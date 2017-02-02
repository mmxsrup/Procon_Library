class DisjointSet{
    public:
        vector<int> rank, p;//rank:木の高さ p:親の頂点番号
        DisjointSet(){}
        DisjointSet(int size){//頂点の数
            rank.resize(size, 0);
            p.resize(size, 0);
            rep(i, size) makeSet(i);
        }
        void makeSet(int x){
            p[x] = x;
            rank[x] = 0;
        }
        //同じ木にあるか判定（今回使わない）
        bool same(int x, int y){
            return findSet(x) == findSet(y);
        }
        // 木どうしをくっつける
        void unite(int x, int y){
            link(findSet(x), findSet(y));
        }
        //木の高さを考慮して木どうしをくっつける
        void link(int x, int y){
            if(rank[x] > rank[y]){
                p[y] = x;
            }else{
                p[x] = y;
                if(rank[x] == rank[y]) rank[y]++;
            }
        }
        //親を探す（ルートまで）
        int findSet(int x){
            if(x != p[x]){
                p[x] = findSet(p[x]);
            }
            return p[x];
        }
};

/*
http://abc049.contest.atcoder.jp/tasks/arc065_b
*/