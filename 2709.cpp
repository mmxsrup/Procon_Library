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

int N, M, K;
int D[20];
int v[110][110];
//dp[mask] := Aさんが集合maskにいる可能性のある時の最短経路
int dp[(1<<16)];

vector<int> G[];

int main(void){
	cin >> N >>  M >> K;
	rep(i, N) cin >> D[i], D[i]--;
	rep(i, N)rep(j, K) cin >> v[i][j], v[i][j]--;

	rep(i, (1<<16)) dp[i] = INF;
	dp[(1<<M) - 1] = 0;
	return 0;
}