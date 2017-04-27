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