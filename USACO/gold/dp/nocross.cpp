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
 
//#define int long long

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn=1010;

int a[mxn],b[mxn],dp[mxn][mxn];

int main(){
	freopen("nocross.in","r",stdin);
	freopen("nocross.out","w",stdout);
	fast;
	int n;
	cin>>n;
	for(int i=1; i<=n; i++) cin>>a[i];
	for(int i=1; i<=n; i++) cin>>b[i];
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
			if(abs(a[i]-b[j])<=4) mxx(dp[i][j],dp[i-1][j-1]+1); 
		}
	}
	cout<<dp[n][n]<<'\n';
}