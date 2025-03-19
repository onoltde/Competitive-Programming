#include<bits/stdc++.h>
using namespace std;
 
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define sz(x) (int)x.size()

typedef long long ll;
 
//#define int long long

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn=2010,mod=1e9+7;

int dp[mxn][mxn][2];

void add(int &a,int b){
	a+=b;
	if(a>=mod) a-=mod;
}

void go(){
	int n;
	cin>>n;
	string str1;
	cin>>str1;
	string a="",b="";
	for(int i=0; i<n; i++){
		if(str1[i]=='0') a.clear();
		if(str1[i]=='1') continue;
		if(str1[i]!='+') str1[i]='X';
		a.pb(str1[i]);
	}
	cin>>str1;
	for(int i=0; i<n; i++){
		if(str1[i]=='0') b.clear();
		if(str1[i]=='1') continue;
		if(str1[i]!='+') str1[i]='X';
		b.pb(str1[i]);
	}
	for(int i=0; i<=sz(a); i++){
		for(int j=0; j<=sz(b); j++){
			for(int k=0; k<2; k++){
				dp[i][j][k]=0;
			}
		}
	}
	dp[0][0][0]=1;
	int ans=0;
	for(int i=0; i<=sz(a); i++){
		for(int j=0; j<=sz(b); j++){
			if(i==sz(a) && j==sz(b)){
				add(ans,dp[i][j][0]);
				add(ans,dp[i][j][1]);
				continue;
			}
			if(j+1<=sz(b)){
				add(dp[i][j+1][1],dp[i][j][1]);
				add(dp[i][j+1][1],dp[i][j][0]);
			}
			if(i+1<=sz(a)){
				add(dp[i+1][j][0],dp[i][j][0]);
				if(j && i<sz(a) && b[j-1]!=a[i]) add(dp[i+1][j][0],dp[i][j][1]);
			}
		}
	}
	cout<<ans<<'\n';
}

signed main(){
//	fast;
	int t=1;
	cin>>t;
	while(t--) go();
}