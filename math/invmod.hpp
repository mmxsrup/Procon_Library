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