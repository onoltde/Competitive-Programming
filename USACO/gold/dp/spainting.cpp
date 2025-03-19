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

const int mxn=1e6+10;
const int mod=1e9+7;

int dp[mxn][2];

signed main(){
	fast;
	freopen("spainting.in","r",stdin);
	freopen("spainting.out","w",stdout);
	int n,m,k;
	cin>>n>>m>>k;
	dp[0][0]=1;
	int sum=1;
	int tot=0;
	for(int i=1; i<=n; i++){
		if(i-k>=0) sum-=dp[i-k][0];
		if(sum<0) sum+=mod;
		if(i>1 && i<k) dp[i][0]=((sum-1)*(m-1)+1)%mod;
		else if(i>1) dp[i][0]=(sum*(m-1))%mod;
		else dp[i][0]=1;
		sum+=dp[i][0];
		if(sum>=mod) sum-=mod;
		
		if(i-k>=0) tot-=dp[i-k][1];
		if(tot<0) tot+=mod;
		dp[i][1]=(tot*(m-1))%mod;
		if(i-k>0) dp[i][1]+=m*(dp[i-k][0]+dp[i-k][1])%mod;
		else if(i-k==0) dp[i][1]++;
		if(dp[i][1]>=mod) dp[i][1]-=mod;
		tot+=dp[i][1];
		if(tot>=mod) tot-=mod;
//		cout<<sum<<' '<<tot<<'\n';
	}
//	for(int i=1; i<=n; i++) cout<<dp[i][0]<<' '<<dp[i][1]<<'\n';
	cout<<(dp[n][1]*m)%mod<<'\n';
	return 0;
}