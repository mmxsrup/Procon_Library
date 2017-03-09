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

