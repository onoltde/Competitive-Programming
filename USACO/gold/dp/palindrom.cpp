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

const int mxn=510,mod=1e9+7;
int n;

int dp[2][mxn][mxn];
string str[mxn];

void add(int &a,int b){
	a+=b;
	if(a>=mod) a-=mod;
}

signed main(){
	freopen("palpath.in","r",stdin);
	freopen("palpath.out","w",stdout);
	cin>>n;
	for(int i=0; i<n; i++) cin>>str[i];
	for(int i=0; i<n; i++) dp[0][i][i]=1;
	int tp=0;
	for(int l=1; l<n; l++){
		tp^=1;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				dp[tp][i][j]=0;
			}
		}
		for(int i=n-l-1,j=0; i>=0; i--,j++){
			for(int ii=n-1,jj=l; jj<n; jj++,ii--){
				if(str[i][j]==str[ii][jj] && j<=jj && i<=ii){
					add(dp[tp][i][ii],dp[tp^1][i][ii]);
					add(dp[tp][i][ii],dp[tp^1][i+1][ii]);
					add(dp[tp][i][ii],dp[tp^1][i][ii-1]);
					add(dp[tp][i][ii],dp[tp^1][i+1][ii-1]);
				}
			}
		}
	}
	cout<<dp[tp][0][n-1]<<'\n';
}