#include<bits/stdc++.h>
using namespace std;
 
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

typedef long long ll;
 
#define int long long

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn=1010;

pair<int,int> a[mxn],b[mxn];

int dp[mxn][mxn][2];

int get(pair<int,int> a,pair<int,int> b){
	int tmp=abs(a.ff-b.ff)*abs(a.ff-b.ff)+abs(a.ss-b.ss)*abs(a.ss-b.ss);
	return tmp;
}

signed main(){
	freopen("checklist.in","r",stdin);
	freopen("checklist.out","w",stdout);
	int n,m;
	cin>>n>>m;
	for(int i=1; i<=n; i++) cin>>a[i].ff>>a[i].ss;
	for(int i=1; i<=m; i++) cin>>b[i].ff>>b[i].ss;
	for(int i=0; i<=n; i++){
		for(int j=0; j<=m; j++){
			dp[i][j][0]=dp[i][j][1]=1e18;
		}
	}
	dp[1][0][0]=0;
	for(int i=1; i<=n; i++){
		for(int j=0; j<=m; j++){
			mnn(dp[i][j][0],dp[i-1][j][1]+get(b[j],a[i]));
			if(j-1>=0){
				mnn(dp[i][j][1],dp[i][j-1][0]+get(b[j],a[i]));
			}
			if(i-1>0){
				mnn(dp[i][j][0],dp[i-1][j][0]+get(a[i-1],a[i]));
			}
			if(j-1>0){
				mnn(dp[i][j][1],dp[i][j-1][1]+get(b[j-1],b[j]));
			}
		}
	}
	cout<<dp[n][m][0]<<'\n';
	return 0;
}