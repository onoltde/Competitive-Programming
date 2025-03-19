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

pair<int,int> a[mxn],b[mxn];

int get(int i,int j){
	return (a[i].ff-b[j].ff)*(a[i].ff-b[j].ff)+(a[i].ss-b[j].ss)*(a[i].ss-b[j].ss);
}
	
int dp[mxn][mxn];

signed main(){
	freopen("radio.in","r",stdin);
	freopen("radio.out","w",stdout);
	int n,m;
	string str1,str2;
	cin>>n>>m;
	cin>>a[0].ff>>a[0].ss;
	cin>>b[0].ff>>b[0].ss;
	cin>>str1;
	cin>>str2;
	for(int i=0; i<n; i++){
		a[i+1]=a[i];
		if(str1[i]=='N') a[i+1].ss++;
		else if(str1[i]=='E') a[i+1].ff++;
		else if(str1[i]=='S') a[i+1].ss--;
		else a[i+1].ff--;
	}
	for(int i=0; i<m; i++){
		b[i+1]=b[i];
		if(str2[i]=='N') b[i+1].ss++;
		else if(str2[i]=='E') b[i+1].ff++;
		else if(str2[i]=='S') b[i+1].ss--;
		else b[i+1].ff--;
	}
	for(int i=0; i<=n; i++){
		for(int j=0; j<=m; j++){
			dp[i][j]=2e9;
		}
	}
	dp[0][0]=0;
	for(int i=0; i<=n; i++){
		for(int j=0; j<=m; j++){
			if(i) mnn(dp[i][j],dp[i-1][j]+get(i,j));
			if(j) mnn(dp[i][j],dp[i][j-1]+get(i,j));
			if(i && j) mnn(dp[i][j],dp[i-1][j-1]+get(i,j));
		}
	}
	cout<<dp[n][m]<<'\n';
	return 0;
}