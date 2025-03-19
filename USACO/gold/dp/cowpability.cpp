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

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mod=1e9+7;
const int lmt=5;

map<array<int,5>,int> mp;
int a[lmt+10];
vector<int> g[1<<lmt];

void go(){
	int n;
	cin>>n;
	int ans=0;
	for(int i=0; i<(1<<lmt); i++){
		for(int j=0; j<lmt; j++){
			int l=(1<<j);
			if(l&i){
				g[i].pb(j);
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<lmt; j++){
			cin>>a[j];
		}
		sort(a,a+lmt);
		for(int j=0; j<(1<<lmt); j++){
			array<int,5> tmp={0, 0, 0, 0, 0};
			int cnt=0;
			for(int k : g[j]){
				tmp[cnt]=a[k];
				cnt++;
			}
			int &ret=mp[tmp];
			if(cnt%2) ans-=ret;
			else ans+=ret;
			ret++;
		}
	}
	cout<<ans<<'\n';
}

signed main(){
	fast;
	freopen("cowpatibility.in","r",stdin);
	freopen("cowpatibility.out","w",stdout);
	int t=1;
	// cin>>t;
	while(t--) go();
	return 0;
}