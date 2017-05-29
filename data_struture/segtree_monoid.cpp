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