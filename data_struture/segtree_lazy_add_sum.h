//(1)区間に一様加算 (2)区間の合計値
struct segtree{
public:
    const int SIZE = 1 << 18;
    //seg:区間の合計値 lazy:区間に対して、加える値でまだ遅延しているもの
    vector<ll> seg, lazy;//segは欲しい情報 lazyは区間に対する一様な処理を示すもの
    segtree():seg(SIZE * 2), lazy(SIZE * 2){}
    void lazy_evaluate(int k, int l, int r){//遅延情報の適用方法
        if(lazy[k] != 0){
            seg[k] += lazy[k];//区間[l,r)にすべて同じ値を追加することになっていて、segには合計値が入っているので、加える値を足す
            if(r  - l > 1){
                lazy[k * 2 + 1] += lazy[k];//遅延を左の子に伝搬
                lazy[k * 2 + 2] += lazy[k];//遅延を右の子に伝搬
            }
            lazy[k] = 0;//ノードkは伝搬完了
        }
    }
    void update(int a, int b, int k, int l, int r, int x){
        lazy_evaluate(k, l, r);
        if(r <= a || b <= l) return;
        if(a <= l && r <= b){
            lazy[k] += x; //加える
            lazy_evaluate(k, l, r);
        }else{
            update(a, b, k * 2 + 1, l, (l + r) / 2, x);
            update(a, b, k * 2 + 2, (l + r) / 2, r, x);
            seg[k] = seg[k * 2 + 1] + seg[k * 2 + 2]; //区間の合計
        }
    }  
    ll query(int a, int b, int k, int l, int r){
        lazy_evaluate(k, l, r);
        if(r <= a || b <= l) return 0;//合計に影響のないもの
        if(a <= l && r <= b) return seg[k];
        ll x = query(a, b, k * 2 + 1, l, (l + r) / 2);
        ll y = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return x + y; //左右の合計を
    }
    //update(a,b,x) := [a,b)を全てxを加える
    void update(int a, int b, int x){update(a, b, 0, 0, SIZE, x);}
    //query(a,b) := [a,b)に対する合計値を求める
    ll query(int a, int b){return query(a, b, 0, 0, SIZE);}
};