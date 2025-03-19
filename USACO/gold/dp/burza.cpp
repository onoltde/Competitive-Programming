#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

// #define int long long

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn=21;
const int mxm=410;

vector<int> g[mxm];
vector<int> dd[mxn];

pair<int,int> cc[mxm];
int n,k;
int tt=0;

void dfs(int to,int fr,int dth){
	dd[dth].pb(to);
	if(dth==k){
		cc[to].ff=cc[to].ss=++tt;
		return;
	}
	for(int x : g[to]){
		if(x==fr) continue;
		dfs(x,to,dth+1);
		mxx(cc[to].ss,cc[x].ss);
		mnn(cc[to].ff,cc[x].ff);
	}
}

void go(){
	cin>>n>>k;
	for(int i=0; i<n; i++){
		int x,y;
		cin>>x>>y;
		g[x].pb(y);
		g[y].pb(x);
	}
	if(k*k>=n){
		cout<<"DA\n";
		return;
	}
	for(int i=1; i<=n; i++) cc[i].ff=1e9,cc[i].ss=-1;
	dfs(1,0,0);
	// cout<<tt<<'\n';
	vector<int>	dp((1<<k),-1);
	dp[0]=0;
	for(int i=1; i<(1<<k); i++){
		for(int j=0; j<k; j++){
			int l=(1<<j);
			if((i&l)==0) continue;
			int pp=i^l;
			for(int x : dd[j+1]){
				if(cc[x].ff-1<=dp[pp]) mxx(dp[i],cc[x].ss);
			}
		}
		if(dp[i]>=tt){
			cout<<"DA\n";
			return;
		}
	}
	cout<<"NE\n";
}

signed main(){
	int t=1;
	// cin>>t;
	while(t--) go();
	return 0;
}