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

void go(){
	int n,t;
	cin>>n>>t;
	vector<pair<int,int>> a;
	for(int i=0; i<n; i++){
		int x,y;
		cin>>x>>y;
		a.pb({x+y*t,i});
	}
	sort(all(a),[&](pair<int,int> x,pair<int,int> y){
		if(x.ff==y.ff) return x.ss>y.ss;
		return x.ff<y.ff;
	});
	set<int> s;
	for(int i=0; i<n; i++){
		int now=-a[i].ss;
		auto it=s.lower_bound(now);
		if(it==s.end()) s.in(now);
		else s.erase(it),s.in(now);
	}
	cout<<s.size()<<'\n';
}

signed main(){
	fast;
	freopen("cowjog.in","r",stdin);
	freopen("cowjog.out","w",stdout);
	int t=1;
//	cin>>t;
	while(t--) go();
}