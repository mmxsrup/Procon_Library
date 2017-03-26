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