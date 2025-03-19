#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define int long long

void mxx(int &a,int b) {if(b>a) a=b;}
void mnn(int &a,int b) {if(b<a) a=b;}

int mod;

int dp[10100][2000];

signed main(){
	fast;
	freopen("exercise.in","r",stdin);
	freopen("exercise.out","w",stdout);
	int n,mod;
	cin>>n>>mod;
	vector<int> gg,vis(n+1,0);
	for(int i=2; i<=n; i++){
		if(vis[i]) continue;
		gg.pb(i);
		for(int j=i*i; j<=n; j+=i) vis[j]=1;
	}
	if(gg.empty()){
		cout<<1<<'\n';
		return 0;
	}
	for(int i=0; i<=gg.size(); i++) dp[0][i]=1;
	for(int j=1; j<=gg.size(); j++){
		for(int i=1; i<=n; i++){
			int tmp=gg[j-1];
			dp[i][j]=dp[i][j-1];
			while(tmp<=i){
				dp[i][j]+=(dp[i-tmp][j-1]*tmp);
				dp[i][j]%=mod;
				tmp*=gg[j-1];
			}
		}
	}
	int ans=0;
	for(int i=0; i<=n; i++) ans+=dp[i][gg.size()];
	ans%=mod;
	cout<<ans<<'\n';
	return 0;
}