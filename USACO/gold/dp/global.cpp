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

const int mxn=2e5+10;
const int inf=1e18+10;

int pre[mxn];

int a[mxn];

signed main(){
	int n,x;
	cin>>n>>x;
	for(int i=1; i<=n; i++){
		cin>>a[i];
	}
	vector<int> g;
	int ans=0;
	for(int i=1; i<=n; i++){
		int gg=lower_bound(all(g),a[i])-g.begin();
		if(gg==g.size()) g.pb(a[i]);
		else g[gg]=a[i];
		pre[i]=gg+1;
	}
	g.clear();
	for(int i=n; i>=1; i--){
		int gg=lower_bound(all(g),-(a[i]-x))-g.begin();
		mxx(ans,pre[i]+gg);
		gg=lower_bound(all(g),-a[i])-g.begin();
		if(gg==g.size()) g.pb(-a[i]);
		else g[gg]=-a[i];
	}
	cout<<ans<<'\n';
}