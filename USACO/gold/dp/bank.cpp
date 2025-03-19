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

int a[mxn],b[mxn];

int dp[1<<mxn],cn[1<<mxn];

signed main(){
	fast;
	int n,m;
	cin>>n>>m;
	for(int i=1; i<=n; i++) cin>>a[i];
	for(int i=1; i<=m; i++) cin>>b[i];
	memset(dp,-1,sizeof(dp));
	int lim=(1<<m);
	dp[0]=0;
	for(int i=0; i<lim; i++){
		for(int j=0; j<m; j++){
			int l=(1<<j);
			if((i&l)==0) continue;
			int t=i^l;
			if(dp[t]==-1) continue;
			if(dp[t]+b[j+1]<a[cn[t]+1]){
				dp[i]=dp[t]+b[j+1];
				cn[i]=cn[t];
			}
			else if(dp[t]+b[j+1]==a[cn[t]+1]){
				dp[i]=0;
				cn[i]=cn[t]+1;
			}
		}
		if(cn[i]==n){
			cout<<"YES\n";
			return 0;
		}
	}
	cout<<"NO\n";
	return 0;
}