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
