#include<bits/stdc++.h>
using namespace std;
 
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

typedef long long ll;
 
//#define int long long

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn=22;

int h[mxn],dp[1<<mxn];

signed main(){
	fast;
	freopen("movie.in","r",stdin);
	freopen("movie.out","w",stdout);
	int n,L;
	cin>>n>>L;
	vector<vector<int>> g(n);
	for(int i=0; i<n; i++){
		cin>>h[i];
		int m;
		cin>>m;
		g[i].resize(m);
		for(int j=0; j<m; j++) cin>>g[i][j];
	}
	memset(dp,-1,sizeof(dp));
	dp[0]=0;
	int ans=100;
	for(int i=0; i<(1<<n); i++){
		for(int j=0; j<n; j++){
			int l=(1<<j);
			if(!(l&i)) continue;
			int gg=i^l;
			if(dp[gg]==-1) continue;
			int pos=upper_bound(all(g[j]),dp[gg])-g[j].begin();
			if(pos==0) continue;
			pos--;
			mxx(dp[i],g[j][pos]+h[j]);
			if(dp[i]>=L){
//				if(i==2){
//					cout<<dp[i]<<' '<<dp[gg]<<' '<<pos<<' '<<l<<'\n';
//				}
				mnn(ans,__builtin_popcount(i));
			}
		}
	}
	cout<<(ans==100 ? -1 : ans)<<'\n';
}