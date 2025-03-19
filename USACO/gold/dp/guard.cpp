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

int s[mxn],w[mxn],h[mxn];

int dp[1<<mxn],tot[1<<mxn];

signed main(){
	fast;
	freopen("guard.in","r",stdin);
	freopen("guard.out","w",stdout);
	int n,H;
	cin>>n>>H;
	for(int i=0; i<n; i++) cin>>h[i]>>w[i]>>s[i];
	memset(dp,-1,sizeof(dp));
	for(int i=0; i<n; i++){
		int l=(1<<i);
		dp[l]=s[i];
		tot[l]=h[i];
	}
	int ans=-1;
	for(int i=0; i<(1<<n); i++){
		for(int j=0; j<n; j++){
			int l=(1<<j);
			if((l&i)==0) continue;
			int t=i^l;
			if(dp[t]==-1) continue;
			int nw=min(dp[t]-w[j],s[j]);
			if(nw<0) continue;
			if(nw>dp[i]){
				dp[i]=nw;
				tot[i]=tot[t]+h[j];
			}
		}
		if(tot[i]>=H){
			mxx(ans,dp[i]);
		}
	}
	if(ans==-1) cout<<"Mark is too tall\n";
	else cout<<ans<<'\n';
}