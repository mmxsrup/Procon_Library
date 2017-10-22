##################################################
################# ./template.cpp #################
##################################################

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vint;
typedef pair<int,int> pint;
typedef vector<pint> vpint;
#define rep(i,n) for(int i=0;i<(n);i++)
#define REP(i,n) for(int i=n-1;i>=(0);i--)
#define reps(i,f,n) for(int i=(f);i<(n);i++)
#define each(it,v) for(__typeof((v).begin()) it=(v).begin();it!=(v).end();it++)
#define all(v) (v).begin(),(v).end()
#define eall(v) unique(all(v), v.end())
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define chmax(a, b) a = (((a)<(b)) ? (b) : (a))
#define chmin(a, b) a = (((a)>(b)) ? (b) : (a))
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll INFF = 1e18;

int main(void){
	return 0;
}

##################################################
########### ./data_struture/imos_one.h ###########
##################################################

vector<int> imos_one(vector<int> baseimos){
    int basesize = baseimos.size();
    vector<int> imos(basesize, 0); 
    imos[0] = baseimos[0];
    for(int i = 1; i < basesize; ++i){
        imos[i] = imos[i - 1] + baseimos[i];
    }
    return imos;
}

##################################################
#### ./data_struture/segtree_lazy_add_min.cpp ####
##################################################

//(1)区間に一様加算 (2)区間の最小値
struct segtree{
public:
    const int SIZE = 1 << 18;
    //seg:区間の最小値 lazy:区間に対して、加える値でまだ遅延しているもの
    vector<ll> seg, lazy;//segは欲しい情報 lazyは区間に対する一様な処理を示すもの
    segtree():seg(SIZE * 2), lazy(SIZE * 2){}
    void lazy_evaluate(int k, int l, int r){//遅延情報の適用方法
        if(lazy[k] != 0){
            seg[k] += lazy[k];//区間[l,r)にすべて同じ値を追加することになっていて、segには最小値が入っているので、加える値を足す
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
            seg[k] = min(seg[k * 2 + 1], seg[k * 2 + 2]); //区間のmin
        }
    }  
    ll query(int a, int b, int k, int l, int r){
        lazy_evaluate(k, l, r);
        if(r <= a || b <= l) return INF;//minの影響のないもの
        if(a <= l && r <= b) return seg[k];
        ll x = query(a, b, k * 2 + 1, l, (l + r) / 2);
        ll y = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return min(x, y); //左右のminを
    }
    //update(a,b,x) := [a,b)を全てxを加える
    void update(int a, int b, int x){update(a, b, 0, 0, SIZE, x);}
    //query(a,b) := [a,b)に対する最小値を求める
    ll query(int a, int b){return query(a, b, 0, 0, SIZE);}
};

/*
//(1)区間に一様加算 (2)区間の最小値
const int MAX_N = 1 << 19;
struct segtree{
public:
	int SIZE;
	int seg[MAX_N * 2], lazy[MAX_N * 2];//segは欲しい情報 lazyは区間に対する一様な処理を示すもの
    //seg:区間の最小値 lazy:区間に対して、加える値でまだ遅延しているもの
    segtree(int n){
        SIZE = 1;
        while(SIZE < n) SIZE *= 2;//要素数を2のべき乗に
        for (int i = 0; i < 2 * SIZE - 1; ++i) seg[i] = lazy[i] = 0;//0は遅延しているものがないことを示す
    }
    void lazy_evaluate(int k, int l, int r){//遅延情報の適用方法
        if(lazy[k] != 0){
            seg[k] += lazy[k];//区間[l,r)にすべて同じ値を追加することになっていて、segには最小値が入っているので、加える値を足す
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
            seg[k] = min(seg[k * 2 + 1], seg[k * 2 + 2]); //区間のmin
        }
    }  
    ll query(int a, int b, int k, int l, int r){
        lazy_evaluate(k, l, r);
        if(r <= a || b <= l) return INF;//minの影響のないもの
        if(a <= l && r <= b) return seg[k];
        ll x = query(a, b, k * 2 + 1, l, (l + r) / 2);
        ll y = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return min(x, y); //左右のminを
    }
    //update(a,b,x) := [a,b)を全てxを加える
    void update(int a, int b, int x){update(a, b, 0, 0, SIZE, x);}
    //query(a,b) := [a,b)に対する最小値を求める
    ll query(int a, int b){return query(a, b, 0, 0, SIZE);}
};
*/

/*
http://tenka1-2016-qualb.contest.atcoder.jp/tasks/tenka1_2016_qualB_d
*/


##################################################
##### ./data_struture/segtree_lazy_add_min.h #####
##################################################

//(1)区間に一様加算 (2)区間の最小値
struct segtree{
public:
    const int SIZE = 1 << 18;
    //seg:区間の最小値 lazy:区間に対して、加える値でまだ遅延しているもの
    vector<ll> seg, lazy;//segは欲しい情報 lazyは区間に対する一様な処理を示すもの
    segtree():seg(SIZE * 2), lazy(SIZE * 2){}
    void lazy_evaluate(int k, int l, int r){//遅延情報の適用方法
        if(lazy[k] != 0){
            seg[k] += lazy[k];//区間[l,r)にすべて同じ値を追加することになっていて、segには最小値が入っているので、加える値を足す
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
            seg[k] = min(seg[k * 2 + 1], seg[k * 2 + 2]); //区間のmin
        }
    }  
    ll query(int a, int b, int k, int l, int r){
        lazy_evaluate(k, l, r);
        if(r <= a || b <= l) return INF;//minの影響のないもの
        if(a <= l && r <= b) return seg[k];
        ll x = query(a, b, k * 2 + 1, l, (l + r) / 2);
        ll y = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return min(x, y); //左右のminを
    }
    //update(a,b,x) := [a,b)を全てxを加える
    void update(int a, int b, int x){update(a, b, 0, 0, SIZE, x);}
    //query(a,b) := [a,b)に対する最小値を求める
    ll query(int a, int b){return query(a, b, 0, 0, SIZE);}
};

/*
//(1)区間に一様加算 (2)区間の最小値
const int MAX_N = 1 << 19;
struct segtree{
public:
	int SIZE;
	int seg[MAX_N * 2], lazy[MAX_N * 2];//segは欲しい情報 lazyは区間に対する一様な処理を示すもの
    //seg:区間の最小値 lazy:区間に対して、加える値でまだ遅延しているもの
    segtree(int n){
        SIZE = 1;
        while(SIZE < n) SIZE *= 2;//要素数を2のべき乗に
        for (int i = 0; i < 2 * SIZE - 1; ++i) seg[i] = lazy[i] = 0;//0は遅延しているものがないことを示す
    }
    void lazy_evaluate(int k, int l, int r){//遅延情報の適用方法
        if(lazy[k] != 0){
            seg[k] += lazy[k];//区間[l,r)にすべて同じ値を追加することになっていて、segには最小値が入っているので、加える値を足す
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
            seg[k] = min(seg[k * 2 + 1], seg[k * 2 + 2]); //区間のmin
        }
    }  
    ll query(int a, int b, int k, int l, int r){
        lazy_evaluate(k, l, r);
        if(r <= a || b <= l) return INF;//minの影響のないもの
        if(a <= l && r <= b) return seg[k];
        ll x = query(a, b, k * 2 + 1, l, (l + r) / 2);
        ll y = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return min(x, y); //左右のminを
    }
    //update(a,b,x) := [a,b)を全てxを加える
    void update(int a, int b, int x){update(a, b, 0, 0, SIZE, x);}
    //query(a,b) := [a,b)に対する最小値を求める
    ll query(int a, int b){return query(a, b, 0, 0, SIZE);}
};
*/

/*
http://tenka1-2016-qualb.contest.atcoder.jp/tasks/tenka1_2016_qualB_d
*/


##################################################
##### ./data_struture/segtree_lazy_add_sum.h #####
##################################################

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

##################################################
######## ./data_struture/segtree_max.hpp #########
##################################################

/*
 呼びだし方
 segtree<int> seg(n); // int型の要素で nは要素の数
*/

template <class T> //T : dat[]の中身の型
class segtree{
public:
	int n;
	vector<T> dat;
	segtree(int n_): n(n_){ //n_要素数
		n = 1;
		while(n < n_) n *= 2;
		dat.resize(n * 2, 0); //(1) 初期値を最小に -INFかも
	}
	void update(int k, T val){ // k番目の値(0-indexed)を val に変更
		for (dat[k += n] = val; k > 0; k >>= 1){ // kを含む区間のインデックスを下から順に列挙
			dat[k>>1] = max(dat[k], dat[k ^ 1]); // (2) 区間の最大値で更新
		}
	}
	T query(int l, int r){ //[l, r)の区間
		T ret = 0; //(3) 最大値に関係ない値 -INFかも
		for (l += n, r += n; l < r; l >>= 1, r >>= 1){
			if(l & 1) ret = max(ret, dat[l++]); //(4) 区間の最大値で更新
			if(r & 1) ret = max(ret, dat[--r]); //(4) 区間の最大値で更新
		}
		return ret;
	}
};


/*
segtree すこし高速化
更新: 1 点
クエリ: 区間の最小値
note: (1)~(4)を変えることで対応可能
http://codeforces.com/contest/777/problem/E
(http://codeforces.com/contest/777/submission/25346678)
この問題では差はない

http://codeforces.com/contest/689/problem/D
(http://codeforces.com/contest/689/submission/25354957)
この問題ではsegtree_max_slow.hppと比べて大きな差が出ている
*/


##################################################
###### ./data_struture/segtree_max_idx.cpp #######
##################################################

template <class T> //T : dat[]の中身の型
class segtree{
public:
	int n;
	T neutral;
	vector<T> dat;
	T func(T l, T r){ //区間をマージする関数
		return max(l, r); /* ここを変える */
	}
	segtree(int n_, T val): n(n_), neutral(val){ //n_:要素数 val:単位元
		n = 1;
		while(n < n_) n *= 2;
		dat.resize(n * 2, neutral); //初期値
	}
	void update(int k, T val){ // k番目の値(0-indexed)を val に変更
		for (dat[k += n] = val; k > 0; k >>= 1){ // kを含む区間のインデックスを下から順に列挙
			dat[k>>1] = func(dat[k], dat[k ^ 1]);
		}
	}
	T query(int l, int r){ //[l, r)の区間
		T ret = neutral;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1){
			if(l & 1) ret = func(ret, dat[l++]);
			if(r & 1) ret = func(ret, dat[--r]);
		}
		return ret;
	}
};

int main(void){
	cin >> n >> d >> k;
	rep(i, n) cin >> x[i];
	segtree<pair<ll, int>> seg(n, make_pair(0, 0));
	rep(i, n) seg.update(i, {x[i], -i}); //辞書順最小のためマイナス
	return 0;
}

/*
http://yukicoder.me/problems/no/489
(http://yukicoder.me/submissions/156443)
*/


##################################################
###### ./data_struture/segtree_max_slow.hpp ######
##################################################

/*
 呼びだし方
 segtree<int> seg(n); // int型の要素で nは要素の数
*/

template <class T> //T : dat[]の中身の型
class segtree{
public:
	int n;
	vector<T> dat;
	segtree(int n_): n(n_){ //n_要素数
		n = 1;
		while(n < n_) n *= 2;
		dat.resize(n * 2, 0); //(1) 初期値を最小に -INFかも
	}
	void update(int k, T val){ // k番目の値(0-indexed)を val に変更
		k += n - 1; //葉の節点
		dat[k] = val;
		while(k > 0){
			k = (k - 1) / 2;
			dat[k] = max(dat[k * 2 + 1], dat[k * 2 + 2]); // (2) 区間の最大値で更新
		}
	}
	T query(int a, int b, int k, int l, int r){ //[a, b)の最大値を求める
		if(r <= a || b <= l) return 0; //(3) 最大値に関係ない値で更新 -INFかも
		if(a <= l && r <= b) return dat[k];
		else{
			T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
			T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return max(vl, vr); //(4) 区間の最大値で更新
		}
	}
	T query(int a, int b){
		return query(a, b, 0, 0, n);
	}
};

/*
segtree
更新: 1 点
クエリ: 区間の最大値
note: (1)~(4)を変えることで対応可能

http://codeforces.com/contest/777/problem/E
(http://codeforces.com/contest/777/submission/25143272)
*/


##################################################
######## ./data_struture/segtree_min.hpp #########
##################################################

/*
 呼びだし方
 segtree<int> seg(n); // int型の要素で nは要素の数
*/

template <class T> //T : dat[]の中身の型
class segtree{
public:
	int n;
	vector<T> dat;
	segtree(int n_): n(n_){ //n_要素数
		n = 1;
		while(n < n_) n *= 2;
		dat.resize(n * 2, INF); //(1) 初期値を最大に
	}
	void update(int k, T val){ // k番目の値(0-indexed)を val に変更
		for (dat[k += n] = val; k > 0; k >>= 1){ // kを含む区間のインデックスを下から順に列挙
			dat[k>>1] = min(dat[k], dat[k ^ 1]); // (2) 区間の最大値で更新
		}
	}
	T query(int l, int r){ //[l, r)の区間
		T ret = INF; //(3) 最小値に関係ない値
		for (l += n, r += n; l < r; l >>= 1, r >>= 1){
			if(l & 1) ret = min(ret, dat[l++]); //(4) 区間の最小値で更新
			if(r & 1) ret = min(ret, dat[--r]); //(4) 区間の最小値で更新
		}
		return ret;
	}
};


/*
segtree すこし高速化
更新: 1 点
クエリ: 区間の最小値
note: (1)~(4)を変えることで対応可能
http://arc045.contest.atcoder.jp/tasks/arc045_b
(http://arc045.contest.atcoder.jp/submissions/1151765)

http://codeforces.com/contest/689/problem/D
(http://codeforces.com/contest/689/submission/25354957)
*/


##################################################
###### ./data_struture/segtree_min_slow.hpp ######
##################################################

/*
 呼びだし方
 segtree<int> seg(n); // int型の要素で nは要素の数
*/


template <class T> //T : dat[]の中身の型
class segtree{
public:
	int n;
	vector<T> dat;
	segtree(int n_): n(n_){ //n_要素数
		n = 1;
		while(n < n_) n *= 2;
		dat.resize(n * 2, INF); //(1) 初期値を最大に
	}
	void update(int k, T val){ // k番目の値(0-indexed)を val に変更
		k += n - 1; //葉の節点
		dat[k] = val;
		while(k > 0){
			k = (k - 1) / 2;
			dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]); // (2) 区間の最小値で更新
		}
	}
	T query(int a, int b, int k, int l, int r){ //[a, b)の最大値を求める
		if(r <= a || b <= l) return INF; //(3) 最小値に関係ない値で更新
		if(a <= l && r <= b) return dat[k];
		else{
			T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
			T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return min(vl, vr); //(4) 区間の最小値で更新
		}
	}
	T query(int a, int b){
		return query(a, b, 0, 0, n);
	}
};

/*
segtree
更新: 1 点
クエリ: 区間の最小値
note: (1)~(4)を変えることで対応可能

http://arc045.contest.atcoder.jp/tasks/arc045_b
(http://arc045.contest.atcoder.jp/submissions/1151282)
*/


##################################################
####### ./data_struture/segtree_monoid.cpp #######
##################################################

template <class T> //T(モノイド) : dat[]の中身の型
class segtree{
public:
	int n;
	T neutral;
	vector<T> dat;
	T func(T l, T r) { //二項演算子
		int lok, lopen, lclose, rok, ropen, rclose;
		tie(lok, lopen, lclose) = l;
		tie(rok, ropen, rclose) = r;
		int add = min(lopen, rclose);
		return make_tuple(lok + rok + 2 * add, lopen + ropen - add, lclose + rclose - add);
	}
	segtree(int n_, T val): n(n_), neutral(val) { //n_:要素数 val:単位元
		n = 1;
		while(n < n_) n *= 2;
		dat.resize(n * 2, neutral); //初期値
	}
	void update(int k, T val){ // k番目の値(0-indexed)を val に変更
		k += n - 1;
		dat[k] = val;
		while (k > 0) {
			k = (k - 1) / 2;
			dat[k] = func(dat[k * 2 + 1], dat[k * 2 + 2]);
		}
	}
	T query(int a, int b, int k, int l, int r) { //[a, b)の区間
		if(r <= a || b <= l) return neutral;
		if(a <= l && r <= b) return dat[k];
		else {
			T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
			T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return func(vl, vr);
		}
	}
	T query(int a, int b) {
		return query(a, b, 0, 0, n);
	}
};

##################################################
###### ./data_struture/segtree_template.hpp ######
##################################################

template <class T> //T : dat[]の中身の型
class segtree{
public:
	int n;
	T neutral;
	vector<T> dat;
	T func(T l, T r){ //区間をマージする関数
		return max(l, r); /* ここを変える */
	}
	segtree(int n_, T val): n(n_), neutral(val){ //n_:要素数 val:単位元
		n = 1;
		while(n < n_) n *= 2;
		dat.resize(n * 2, neutral); //初期値
	}
	void update(int k, T val){ // k番目の値(0-indexed)を val に変更
		for (dat[k += n] = val; k > 0; k >>= 1){ // kを含む区間のインデックスを下から順に列挙
			dat[k>>1] = func(dat[k], dat[k ^ 1]);
		}
	}
	T query(int l, int r){ //[l, r)の区間
		/* 可換出ない時危険 */
		T ret = neutral;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1){
			if(l & 1) ret = func(ret, dat[l++]);
			if(r & 1) ret = func(ret, dat[--r]);
		}
		return ret;
	}
};

/*
呼び出し方
例
segtree<pair<ll, int>> seg(n, make_pair(0, 0));

funcの部分を変えてマージする

http://yukicoder.me/problems/no/489
(http://yukicoder.me/submissions/156443)
*/

##################################################
###### ./data_struture/SparseTable_max.hpp #######
##################################################

/*
 呼びだし方
 int v[1000];
 segtree<int> seg(n, v); // int型の要素で nは要素の数
*/

template <class T> //T : table[][]の中身の型
class SparseTable_max{
public:
	int N, M; //table[N][M]
	// table[i][k] := [i, i + 2^k)の最大値
	vector<vector<T>> table;
	template<class S> SparseTable_max(int n, S &val): N(n){ // O(nlogn)
		M = 32 - __builtin_clz(N); // M - 1 <= logN < M
		table.resize(N, vector<T>(M));
		for (int i = 0; i < N; ++i){ // [i, i + 1)までの区間の最大値
			table[i][0] = val[i];
		}
		for (int k = 0; k < M - 1; ++k){ // [i, i + 2^(k+1))の区間を計算
			for (int i = 0; i + (1<< k) < N; ++i){
				// iから2^(k+1)の長さの区間の最小値を2^kの長さの区間の最大値を利用して求める
				table[i][k + 1] = max(table[i][k], table[i + (1 << k)][k]); // (1)最大値
			}
		}
	}
	T query(int l, int r){ // O(1) [l, r) の間の最大値
		int k = 31 - __builtin_clz(r - l); //区間の長さの半分以上の値 （k<= r - l < k + 1)
		return max(table[l][k], table[r - (1 << k)][k]); // (2) 最大値
	}
};


/*
前処理(nlogn)
最小値(1)

http://codeforces.com/contest/689/problem/D
(http://codeforces.com/contest/689/submission/25363691)
*/



##################################################
###### ./data_struture/SparseTable_min.hpp #######
##################################################

/*
 呼びだし方
 int v[1000];
 segtree<int> seg(n, v); // int型の要素で nは要素の数
*/

template <class T> //T : table[][]の中身の型
class SparseTable{
public:
	int N, M; //table[N][M]
	// table[i][k] := [i, i + 2^k)の最小値
	vector<vector<T>> table;
	template<class S> SparseTable(int n, S &val): N(n){ // O(nlogn)
		M = 32 - __builtin_clz(N); // M - 1 <= logN < M
		table.resize(N, vector<T>(M));
		for (int i = 0; i < N; ++i){ // [i, i + 1)までの区間の最小値
			table[i][0] = val[i];
		}
		for (int k = 0; k < M - 1; ++k){ // [i, i + 2^(k+1))の区間を計算
			for (int i = 0; i + (1<< k) < N; ++i){
				// iから2^(k+1)の長さの区間の最小値を2^kの長さの区間の最小値を利用して求める
				table[i][k + 1] = min(table[i][k], table[i + (1 << k)][k]); // (1)最小値
			}
		}
	}
	T query(int l, int r){ // O(1) [l, r) の間の最小値
		int k = 31 - __builtin_clz(r - l); //区間の長さの半分以上の値 （k<= r - l < k + 1)
		return min(table[l][k], table[r - (1 << k)][k]); // (2) 最小値
	}
};

/*
template <class T> //T : table[][]の中身の型
class SparseTable{
public:
	int N, M; //table[N][M]
	// table[i][k] := [i, i + 2^k)の最小値
	vector<vector<T>> table;
	template<class S> SparseTable(int n, S &val): N(n){ // O(nlogn)
		M = 32 - __builtin_clz(N); // M - 1 <= logN < M
		table = vector<vector<T>>(N, vector<T>(M, INF)); // (1)最小に関係ない値で更新
		for (int i = 0; i < N; ++i){ // [i, i + 1)までの区間の最小値
			table[i][0] = val[i];
		}
		for (int k = 1; k < M; ++k){ // [i, i + 2^k)の区間を計算
			for (int i = 0; i + (1<< k) <= N; ++i){
				// iから2^kの長さの区間の最小値を2^(k-1)の長さの区間の最小値を利用して求める
				auto first = table[i][k - 1];
				auto second = table[i + (1<< (k - 1))][k - 1];
				table[i][k] = (first < second) ? first : second; // (2) 小さい方で更新
			}
		}
	}
	T query(int l, int r){ // O(1) [l, r) の間の最小値
		int k = 31 - __builtin_clz(r - l); //区間の長さの半分以上の値 （k<= r - l < k + 1)
		return min(table[l][k], table[r - (1 << k)][k]); // (3) 最小値
	}
};
*/


/*
前処理(nlogn)
最小値(1)

http://arc045.contest.atcoder.jp/tasks/arc045_b
(http://arc045.contest.atcoder.jp/submissions/1152995)
(http://arc045.contest.atcoder.jp/submissions/1152999)
最初の初期値をどのようにするか
*/



##################################################
########## ./data_struture/union_find.h ##########
##################################################

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

##################################################
################ ./dp/imos2d.cpp #################
##################################################

/*
 * 二次元累積和(長方形内の値の合計を出す問題)
 */

// O(hw)
void sum2D(int h, int w) { // a の縦と横の長さ
	rep(y, h + 1)rep(x, w + 1) sum[y][x] = 0;
	rep(y, h)rep(x, w) sum[y + 1][x + 1] = a[y][x]; // まずは埋め込む
	rep(y, h + 1)rep(x, w) sum[y][x + 1] += sum[y][x]; // 横
	rep(y, h)rep(x, w + 1) sum[y + 1][x] += sum[y][x]; // 縦
}
// O(1)
int calcSum(int y1, int x1, int y2, int x2) { // 求めたい長方形の左上, 右下の座標
	return sum[y2 + 1][x2 + 1] - sum[y2 + 1][x1] - sum[y1][x2 + 1] + sum[y1][x1];
}

/*
"まずは埋め込む" の部分のaは書き換える
aoj 1176

*/

##################################################
########### ./dp/Traveling_Salesman.h ############
##################################################

const int MAX_N = 20;
vector<pair<int, int> > G[MAX_N]; /* G[u][v] := u->v's weight */
int dp[(1 << MAX_N)][MAX_N];
int pre[(1 << MAX_N)][MAX_N];
int Traveling_Salesman(int n){ /* n := Number of vertices */
	rep(i, (1 << n))rep(j, n)dp[i][j] = INF; /* Initialization */
	dp[0][0] = 0;
	for (int mask = 0; mask < (1 << n); ++mask){
		for (int u = 0; u < n; ++u){ /* Current vertex */
			for(auto p : G[u]){ /* Next vertex */
				int v = p.first, w = p.second;
				if((mask & (1 << v)) == 0){
					if(dp[mask | (1 << v)][v] > dp[mask][u] + w){
						dp[mask | (1 << v)][v] = dp[mask][u] + w;
						pre[mask | (1 << v)][v] = u;
					}
				}
			}
		}
	}
	return dp[(1 << n) - 1][0];
}
vector<int> Restoration(int n){
	vector<int> root;
	int mask = (1 << n) - 1, v = 0;
	root.push_back(v);
	while(mask != 0){
		int u = pre[mask][v]; /* u -> v */
		root.push_back(u);
		mask ^= (1 << v);
		v = u;
	}
	reverse(root.begin(), root.end());
	return root;	
}

/*
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_2_A
経路復元は検証していない
*/

##################################################
############ ./geometry/template.cpp #############
##################################################

class Point { // 点
public:
    double x, y;
    Point(double x = 0, double y = 0):x(x), y(y){}
    Point operator + (Point p) const { return Point(x + p.x, y + p.y); }
    Point operator - (Point p) const { return Point(x - p.x, y - p.y); }
    Point operator * (double a) const { return Point(a * x, a * y); }
    Point operator / (double a) const { return Point(x / a, y / a); }
    double abs() const { return sqrt(norm()); }
    double norm() const { return x * x + y * y; }
    // bool operator < (const Point &p) const { return x != p.x ? x < p.x : y < p.y; }
    bool operator < (const Point &p) const { // 誤差を許容して比較
        return x + EPS < p.x || (eq<double>(x, p.x) && y + EPS < p.y);
    }
    bool operator == (const Point &p) const { return (eq<double>(x, p.x) && eq<double>(y, p.y)); }
};
using Vector = Point;
using Polygon = vector<Point>; // 多角形

double dot(const Vector& a, const Vector& b) { return a.x * b.x + a.y * b.y; } // ベクトルaとbの内積
double cross(const Vector& a, const Vector& b) { return a.x * b.y - a.y * b.x; } // ベクトルaとbの外積
double length2(const Point& a) { return a.norm(); } // 通常の長さの2乗
double length(const Point& a) { return a.abs(); } // 通常の長さ
Point rotationalTransfer(Point c, double r, double deg) { // cを中心として半径rの円周上のdeg度の位置座標
    double rad = PI * deg / 180.0; return c + Point(cos(rad), sin(rad)) * r;
}
// (x, y, z) の点を光源(xy座標での角度がtheta度, xy平面からz方向への角度がphi度の時の)からてらした時の影のxy座標
Point Shadow(double x, double y, double z, double theta, double phi) {
    theta = PI * theta / 180.0, phi = PI * phi / 180.0;
    return Point(x - z / tan(phi) * cos(theta), y - z / tan(phi) * sin(theta));
}

enum ccw_t {
    COUNTER_CLOCKWISE = 1, // p0->p1 反時計回りの方向にp2
    CLOCKWISE = -1, // p0->p1 時計回りの方向にp2
    ONLINE_BACK = 2, // p2->p0->p1 の順で直線上でp2
    ONLINE_FRONT = -2, // p0->p1->p2 の順で直線上p2
    ON_SEGMENT = 0, // p0->p2->p1 の順で線分p0p1上にp2
};
ccw_t ccw(Point p0, Point p1, Point p2) {
    Vector a = p1 - p0, b = p2 - p0;
    if ( cross(a, b) > EPS  )  return COUNTER_CLOCKWISE;
    if ( cross(a, b) < -EPS )  return CLOCKWISE;
    if ( dot(a, b) < -EPS )    return ONLINE_BACK;
    if ( a.norm() < b.norm() ) return ONLINE_FRONT;
    return ON_SEGMENT;
}

class Segment { //線分
public:
    Point p1, p2;
    Segment(){}
    Segment(Point p1, Point p2):p1(p1), p2(p2){}
};
using Line = Segment;

// *** 多角形 ***
// IN := 2, ON := 1, OUT := 0
vector<Segment> getPolygonSegument(const Polygon& p) { //多角形の点から多角形の辺を求める
    vector<Segment> ret;
    rep(i, p.size() - 1) ret.push_back(Segment(p[i], p[i + 1]));
    ret.push_back(Segment(p[p.size() - 1], p[0]));
    return ret;
}
int contains(const Polygon& g, const Point& p){ // 多角形gの中に点pが含まれているか
    int n = g.size(); bool x = false;
    for (int i = 0; i < n; ++i) {
        Point a = g[i] - p, b = g[(i + 1) % n] - p;
        if ( abs(cross(a, b)) < EPS && dot(a, b) < EPS ) return 1;
        if (a.y > b.y) swap(a, b);
        if (a.y < EPS && EPS < b.y && cross(a, b) > EPS ) x = !x;
    }
    return (x ? 2 : 0);
}
Polygon andrewScan(Polygon s) { // 凸包(最も左にある頂点から)
    Polygon u, l;
    if (s.size() < 3) return s;
    sort(s.begin(), s.end()); // x, yを基準に昇順ソート
    // xが小さいものから2つ u に追加
    u.push_back(s[0]), u.push_back(s[1]);
    // x が大きいものから2つ1に追加
    l.push_back(s[s.size() - 1]), l.push_back(s[s.size() - 2]);
    // 凸包の上部を生成
    for (int i = 2; i < s.size(); i++) {
        for (int n = u.size(); n >= 2 && ccw(u[n - 2], u[n - 1], s[i]) != CLOCKWISE; n--){
            u.pop_back();
        }
        u.push_back(s[i]);
    }
    // 凸包の下部を生成
    for (int i = s.size() - 3; i >= 0; i--) {
        for (int n = l.size(); n >= 2 && ccw(l[n - 2], l[n - 1], s[i]) != CLOCKWISE; n--){
            l.pop_back();
        }
        l.push_back(s[i]);
    }
    // 時計回りになるように凸包の点の列を生成
    reverse(l.begin(), l.end());
    for (int i = u.size() - 2; i >= 1; i--) l.push_back(u[i]);
    return l;
}


// *** 線分の交差判定 ***
bool intersect(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    return ( ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 && 
             ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0 );
}
bool intersect(const Segment& s1, const Segment& s2) { // 交差していたらtrue
    return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}
//*** 線分の交点 ***
Point getCrossPoint(Segment s1, Segment s2) { // 線分の交点が存在するから調べた後つかうこと
    Vector base = s2.p2 - s2.p1;
    double d1 = abs(cross(base, s1.p1 - s2.p1)), d2 = abs(cross(base, s1.p2 - s2.p1));
    double t  = d1 / (d1 + d2);
    return s1.p1 + (s1.p2 - s1.p1) * t;
}
// *** 距離 ***
double getDistance(Point& a, Point& b) { // 点aと点bの距離
    return length(a - b);
}
double getDistanceLP(Line& l, Point& p) { // 直線sと点pの距離
    return length(cross(l.p2 - l.p1, p - l.p1) / length(l.p2 - l.p1));
}
double getDistanceSP(Segment s, Point p) { // 線分sと点pの距離
    if( dot(s.p2 - s.p1, p - s.p1) < EPS ) return length(p - s.p1);
    if( dot(s.p1 - s.p2, p - s.p2) < EPS ) return length(p - s.p2);
    return getDistanceLP(s, p);
}
double getDistanceSS(const Segment& s1, const Segment& s2) { // 線分s1と線分s2の交点
    if( intersect(s1, s2) ) return 0.0; //交わっているとき
    return min(min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)),
               min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2)));
}
double getDistancePolP(const Polygon& pol, const Point& p) { // 多角形polと点pの距離
    if(contains(pol, p) != 0) return 0.0; // 点が多角形の内部に含まれている
    double ret = 1e9;
    for(Segment& u : getPolygonSegument(pol)) ret = min(ret, getDistanceSP(u, p));
    return ret;
}
double getDistancePolPol(const Polygon& p1, const Polygon& p2) { // 多角形p1とp2の距離
    for(const Point& p : p1) if(contains(p2, p) != 0) return 0.0; // p1の点が多角形p2の中に含まれている
    for(const Point& p : p2) if(contains(p1, p) != 0) return 0.0; // p2の点が多角形p1の中に含まれている
    double ret = 1e9;
    for(const Segment& u : getPolygonSegument(p1))for(const Segment& v : getPolygonSegument(p2)) {
        ret = min(ret, getDistanceSS(u, v));
    }
    return ret;
}


class Rectangle { // 長方形
public:
    // 3 2
    // 0 1 (反時計回りに長方形の頂点をいれること)
    vector<Point> p; // 点を順番にいれること
    Rectangle(vector<Point>&p):p(p) {
        rep(i, 3) reps(j, i + 1, 4) { //適当な順番にいれても大丈夫なように?
            int cnt = 0;
            rep(k, 4) if(k != i && k != j) {
                cnt += ccw(p[i], p[j], p[k]) == COUNTER_CLOCKWISE;
            }
            if(cnt == 2) {
                swap(p[i + 1], p[j]);
                break;
            }
        }
    }
    bool intersect(const Segment& s) { // 線分sと長方形の少なくとも1辺が交差していればtrue
        bool flag = false;
        rep(i, 4) flag |= ::intersect(s, Segment(p[i], p[(i + 1) % 4]));
        return flag;
    }
    bool contain(const Point& pp) { // 点ppが長方形内に含まれれば(辺を含まない)true
        bool flag = true;
        rep(i, 4) flag &= ccw(p[i], p[(i + 1) % 4], pp) == COUNTER_CLOCKWISE;
        return flag;
    }
    bool contain(const Segment& s) { // 線分sが長方形内に含まれれば(辺を含まない)true
        return contain(s.p1) && contain(s.p2);
    }
};


class Circle {
public:
	Point c;
	double r;
	Circle(Point c = Point(), double r = 0.0):c(c), r(r) {}
}
double arg(Vector p) { return atan2(p.y, p.x); }
Vector polar(double a, double b) { return Point(cos(r) * a, sin(r) * a); }
pair<Point, Point> getCrossPoints(Circle c1, Circle c2) {
	assert(intersect(c1, c2));
	double b = abs(c1.c - c2.c);
	double a = acos(c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d);
	double t = arg(c2.c - c1.c);
	return make_pair(c1.c + polar(c1.r, t + a), c1.c + polar(c1.r, t - a));
}

/*
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2009
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1157&lang=jp
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2402
*/

##################################################
########## ./geometry/types_triangles.h ##########
##################################################

class Types_triangles{
public:
	int n;
	vector<int> y, x;//y座標　x座標
	const double EPS = 1e-10;
	long long cnt_chokaku = 0, cnt_donkaku = 0, cnt_eikaku = 0;
	Types_triangles(const vector<int> &ty, const vector<int> &tx, int size):y(ty), x(tx), n(size){//n:=座標の数
		count();
	}
private:
	void count(){
		for (int i = 0; i < n; ++i){
			//-M_PI ~ M_PI(-180 ~ 180)
			vector<double> angle;//(x[i], y[i])を原点とした偏角
			for (int j = 0; j < n; ++j){
				if(j == i) continue;
				angle.push_back(atan2(y[j] - y[i], x[j] - x[i]));
			}
			sort(angle.begin(), angle.end());
			for (int j = 0; j < n - 1; ++j){//2周目を作る
				angle.push_back(angle[j] + M_PI*2);
			}
			for (int j = 0; j < n - 1; ++j){
				cnt_chokaku += upper_bound(angle.begin(), angle.end(), angle[j] + M_PI/2.0 + EPS) - lower_bound(angle.begin(), angle.end(), angle[j] + M_PI/2.0 - EPS);
				cnt_donkaku += lower_bound(angle.begin(), angle.end(), angle[j] + M_PI) - upper_bound(angle.begin(), angle.end(), angle[j] + M_PI/2.0 + EPS);
			}
		}
		cnt_eikaku = (ll)n * (n - 1) * (n - 2) / 6 - cnt_chokaku - cnt_donkaku;
	}
};

/*
座標があたえられて、その中でできる三角形のなかで、
鋭角、鈍角、直角がそれぞれいくつずつできるかを求める。
http://abc033.contest.atcoder.jp/tasks/abc033_d
*/

##################################################
############### ./graph/dijkstra.h ###############
##################################################

const int MAX_N = 210;
using TYPE = double; // 距離の型を入れる
vector<pair<int, TYPE> > G[MAX_N];
vector<TYPE> dijkstra(int start){
	vector<TYPE> dist(MAX_N, INFF);
	dist[start] = 0;//dist[i] :=　start->iまでの最短距離
	priority_queue<pair<TYPE, int>, vector<pair<TYPE, int> >, greater<pair<TYPE, int> > >  que;
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
				que.push(make_pair(dist[v], v));
			}
		}
	}
	return dist;
}


/*
http://joi2016yo.contest.atcoder.jp/tasks/joi2016yo_e
(http://joi2016yo.contest.atcoder.jp/submissions/1201083)
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2402
*/


##################################################
####### ./graph/dijkstra_.Restoration.cpp ########
##################################################

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

##################################################
############# ./graph/dijkstra_ex.h ##############
##################################################

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

##################################################
############## ./graph/euler_tour.h ##############
##################################################

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

/*
http://codeforces.com/contest/383/problem/C
*/

##################################################
################ ./graph/flow.hpp ################
##################################################

const int MAX_V = 2010; //必要な頂点数
struct Flow{
	struct edge{
		int to, cap, rev;
	};
	vector<edge> G[MAX_V];//隣接リスト
	bool used[MAX_V];
 
	void add_edge(int from, int to, int cap){
		G[from].push_back((edge){to, cap, (int)G[to].size()});//from -> to
		G[to].push_back((edge){from, 0, (int)G[from].size() - 1});//to -> from
	}
	//増加パスを探す
	int dfs(int v, int t, int f){
		if(v == t) return f;
		used[v] = true;
		for (int i = 0; i < G[v].size(); ++i){
			edge &e = G[v][i];
			if(!used[e.to] && e.cap > 0){
				int d = dfs(e.to, t, min(f, e.cap));
				if(d > 0){
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}
	//sからtへの最大流
	int max_flow(int s, int t){
		int flow = 0;
		while(1){
			memset(used, 0, sizeof(used));
			int f = dfs(s, t, INF);
			if(f == 0) return flow;
			flow += f;
		}
	}
};


/*
最大流 2部マッチング
http://codeforces.com/contest/777/problem/B
*/

##################################################
################ ./graph/lca.cpp #################
##################################################

class Tree_lca{
public:
	static const int MAXLOG_V = 25;
	vector<vector<int> > G;
	int V, root;//頂点数 根
	// parent[k][v] := 頂点vから2^k回親側に登って到達する頂点 (通り過ぎると-1)
	vector<int> parent[MAXLOG_V];
	vector<int> depth;//根からの深さ
	
	Tree_lca(int V, int root) : V(V), root(root){
		G.resize(V);
		for (int i = 0; i < MAXLOG_V; ++i) parent[i].resize(V);
		depth.resize(V);
	}
	void unite(int u, int v){ //u-vをunite
		G[u].push_back(v);
		G[v].push_back(u);
	}
	int dist(int u, int v){ // u-v の距離
		int p = lca(u, v);
		return (depth[u] - depth[p]) + (depth[v] - depth[p]);
	}
	void init(){ //parent[0]とdepthを初期化
		dfs(root, -1, 0);
		//parentを初期化 2^kごとのテーブルを作成
		for (int k = 0; k + 1 < MAXLOG_V; ++k){
			for (int v = 0; v < V; ++v){
				if(parent[k][v] < 0) parent[k + 1][v] = -1;//root(rootより上)が親
				else parent[k + 1][v] = parent[k][parent[k][v]];//ダブリングで2倍上の親を求める
			}
		}
	}
private:
	//１つ上の親と深さを設定
	void dfs(int v, int p, int d){//ノード番号　親のノード番号　深さ
		parent[0][v] = p;
		depth[v] = d;
		for(auto u : G[v]){
			if(u != p) dfs(u, v, d + 1);
		}
	}
	//u, vのLCAを求める
	int lca(int u, int v){
		if (depth[u] > depth[v]) swap(u, v);
		for (int k = 0; k + 1 < MAXLOG_V; k++){ //uがvと同じ高さになるまで親を辿る
			if (((depth[v] - depth[u]) >> k) & 1) {
				v = parent[k][v];//bitが立っていれば、親を2^k辿っていく
			}
		}
		if (u == v) return u;
		//2分探索でLCAを求める　LCAより上の親(LA)は常に同じになる
		for (int k = MAXLOG_V - 1; k >= 0; k--) {
			if (parent[k][u] != parent[k][v]){//LCAにたどり着く限界まで、上を目指せばいい
				u = parent[k][u];
				v = parent[k][v];
			}
		}
		return parent[0][u];//1つ上がLCA
	}
};

/*
init()を忘れないように
*/

##################################################
################# ./graph/scc.h ##################
##################################################

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


##################################################
############ ./graph/scc_and_twosat.h ############
##################################################

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

int main(void){

	twosatisfiability sat(n); /* 頂点の数 */
	/* そのままをtrue, 変更するのをfalseとして
		条件を満たさないようなものの条件を反転させた辺を追加する
		ex) true trueで条件を満たさないなら
		sat.add(i, false, j, false)
	*/
	return 0;
}

/*
http://yukicoder.me/problems/no/470
http://yukicoder.me/problems/no/274
http://yukicoder.me/problems/no/483
http://codeforces.com/contest/776/problem/D
*/

##################################################
############## ./graph/scc_class.h ###############
##################################################

class strongly_connected_components{
public:
	vector<vector<int> > G, rG;
	vector<int> used, vs;
	vector<int> cmp; //cmp[v] := 頂点vが含まれる連結成分がどれなのかを示す番号
	strongly_connected_components(int n): G(n), rG(n), cmp(n), used(n){}
	void add_edge(int from, int to){
		G[from].push_back(to);
		rG[to].push_back(from);
	}
	int scc(){
		fill(used.begin(), used.end(), 0);
		vs.clear();
		for (int i = 0; i < G.size(); ++i){
			if(!used[i]) dfs(i);
		}
		fill(used.begin(), used.end(), 0);

		int k = 0;
		for (int i = vs.size() - 1; i >= 0; --i){
			if(!used[vs[i]]){
				rdfs(vs[i], k++);
			}
		}
		return k; //sccの数
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

##################################################
########## ./math/combination_samll.cpp ##########
##################################################

const int MAX_N = 60;
ll com[MAX_N][MAX_N];
void combination(void){ //com[i][j] := iCj
	com[0][0] = 1;
	for (int i = 1; i <= MAX_N - 1; ++i){
		for (int j = 0; j <= i; ++j){
			//パスカルの３角形
			if(j == 0) com[i][j] = com[i - 1][j];
			else com[i][j] = (com[i - 1][j] + com[i - 1][j - 1]);
		}
	}
}

/*
http://abc057.contest.atcoder.jp/tasks/abc057_d
(http://abc057.contest.atcoder.jp/submissions/1184866)
*/

##################################################
############# ./math/combinations.h ##############
##################################################

const int MAX_N = 2000000;
ll inv[MAX_N + 10];
ll fac[MAX_N + 10], facInv[MAX_N + 10];
class MATH{
public:
	MATH(){
		inverse();
		factroial();
	}
	ll nCk(ll n, ll k){// n! / k!*(n-k)!
		if(k < 0 || k > n) return 0;
		ll ret = fac[n];
		(ret *= facInv[k]) %= MOD;
		(ret *= facInv[n - k]) %= MOD;
		return ret;
	}
	ll nHk(ll n, ll k){// nHk = n+k-1 C k = (n+k-1)! / k! * (n-1)!
		if(n == 0 && k == 0) return 1;
		ll ret = fac[n + k - 1];
		(ret *= facInv[k]) %= MOD;
		(ret *= facInv[n - 1]) %= MOD;
		return ret;
	}
	ll nPk(ll n, ll k){//nPk = n! / (n-k)!
		if(k < 0 || k > n) return 0;
		ll ret = fac[n];
		(ret *= facInv[n - k]) %= MOD;
		return ret;
	}
private:
	void inverse(void){
		inv[1] = 1;
		for (int i = 2; i <= MAX_N; ++i){
			// inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
			inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		}
	}
	void factroial(void){
		fac[0] = facInv[0] = 1;
		for (int i = 1; i <= MAX_N; ++i){
			fac[i] = (fac[i - 1] * i) % MOD;
			facInv[i] = (facInv[i - 1] * inv[i]) % MOD;
		}
	}
};

##################################################
################ ./math/eratos.h #################
##################################################

bool isprime[20010];
//エラトステネス
void eratos(int m){
    for (int i = 0; i <= m; ++i) isprime[i] = true;
    isprime[0] = isprime[1] = false;
    //iを残してiの倍数を消していく
    for (int i = 2; i <= m; ++i){
        if(isprime[i]){
            for (int j = 2 * i; j <= m; j += i){
                isprime[j] = false;
            }
        }
    }
}

##################################################
############### ./math/invmod.hpp ################
##################################################

// x^k (mod m)
long long powmod(long long x, long long k, long long m){
	long long ret = 1;
	while(k){
		if(k & 1) ret = ret * x % m;
		x = x * x % m;
		k >>= 1;
	}
	return ret;
}
// 1/a mod(p(素数))
long long invmod(long long a, long long p){
	return powmod(a, p - 2, p);
}

/*
フェルマーの定理を用いて, modの逆元
http://tubo28.me/algorithm/modinv/


http://yukicoder.me/problems/no/492
(http://yukicoder.me/submissions/157384)
*/

##################################################
############### ./math/matrix.cpp ################
##################################################

typedef vector<long long> vec;
typedef vector<vec> mat;
mat mul(mat &A,mat &B){ // A * B の計算
	mat C(A.size(), vec(B[0].size()));
	for(int i = 0; i < A.size(); i++){
		for(int k = 0;k < B.size(); k++){
			for(int j = 0; j < B[0].size(); j++){
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % (ll)MOD; // mod
			}
		}
	}
	return C;
}
mat pow(mat A, long long n){ // A^n の計算 O(m^3*logn)
	mat B(A.size(), vec(A.size()));
	for(int i = 0; i < A.size(); i++){
		B[i][i] = 1;
	}
	while(n > 0){
		if(n & 1) B = mul(B, A);
		A = mul(A, A);
		n >>= 1;
	}
	return B;
}

int main(void){
	ll n; cin >> n;
	mat A(2, vec(2));
	A[0][0] = 100, A[0][1]  = 1;
	A[1][0] = 0,	A[1][1] = 1;
	auto ret = pow(A, n - 1);
}


/* 
行列演算 O(m^3*logn)
A^n 行列を解く
http://yukicoder.me/problems/no/492
(http://yukicoder.me/submissions/157402)

http://abc009.contest.atcoder.jp/tasks/abc009_4

 N*N行列Aを作りたい場合
 mat A(N, vec(N));
 
*/

##################################################
################ ./math/powmod.h #################
##################################################

//x^k mod
long long powmod(long long x, long long k, long long m){ // 繰り返し二乗法(logk)
	if(k == 0) return 1;
	if(k % 2 == 0) return powmod(x * x % m, k / 2, m);
	else return x * powmod(x, k - 1, m) % m;
}

/*
 http://arc044.contest.atcoder.jp/tasks/arc044_b
 (http://arc044.contest.atcoder.jp/submissions/1151541)
*/


##################################################
########## ./math/prime_factorization.h ##########
##################################################

class primelib{
public:
	vector<int> prime; //prime[i] := iが素数の場合には0, 以外のときはiを割りる最大の素数
	vector<int> memo; 
	primelib(int size):prime(size + 10, 0), memo(size + 10, 0){
		prime_factorization(size + 1);
	}
	//[left,right]までのlcmがmemo[x]:=xの次数 として表される
	void getlcm(int left, int right){
		// fill(memo.begin(), memo.end(), 0); //0で初期化
		for (int i = max(2, left); i <= right; ++i){
			map<int, int> degree; //<x, k> := x^k
			int tmp = i;
			while(prime[tmp]){
				degree[prime[tmp]]++;
				tmp /= prime[tmp]; //最大の素数で割る
			}
			degree[tmp]++; //残った素数をカウント
			//memo[x] := [left, right]までを素因数分解した最大のxの次数を更新
			for(auto u : degree){
				memo[u.first] = max(memo[u.first], u.second);
			}
		}
	}
private:
	//prime[i] := iが素数の場合には0, 以外のときはiを割りる最大の素数
	//これを使えばO(logn)で素因数分解可能
	void prime_factorization(int n){
    	for (int i = 2; i <= n; i++) {
    		if (prime[i] == 0) {
        		for (int j = 2; j * i <= n; j++) {
            		prime[i * j] = i;
        		}
    		}
    	}
    }
};

##################################################
############### ./other/is_ururu.h ###############
##################################################

bool is_ururu(int y){
	if(y % 4) return false;
	else if(y % 100) return true;
	else if(y % 400) return false;
	else return true;
}

##################################################
############# ./search/rollinghash.h #############
##################################################

typedef unsigned long long ull;
const ull B = 100000007;
//aはｂにいくつ
int contain(string a, string b){
    int ret = 0;
    int al = a.length(), bl = b.length();
    if(al > bl) return 0;

    ull t = 1;
    for (int i = 0; i < al; ++i) t *= B;

    ull ah = 0, bh = 0;
    for (int i = 0; i < al; ++i) ah = ah * B + a[i];
    for (int i = 0; i < al; ++i) bh = bh * B + b[i];

    for (int i = 0; i + al <= bl; ++i){
        if(ah == bh) ret++;
        if(i + al < bl) bh = bh * B + b[i + al] - b[i] * t;
    }
    return ret;
}

/*
http://yukicoder.me/problems/no/430
*/



##################################################
############### ./search/xor128.h ################
##################################################

unsigned int xor128(){//乱数生成
 	static unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
 	unsigned int t = (x ^(x << 11));
 	x = y; y = z; z = w;
 	return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}

/*
http://yukicoder.me/problems/no/469
*/

