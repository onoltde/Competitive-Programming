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

signed main(){
	int n;
	cin>>n;
	vector<array<int,4>> lol;
	for(int i=0,x,y; i<n; i++){
		cin>>x>>y;
		lol.pb({x+y,x-y,x,y});
	}
	sort(all(lol),[&](array<int,4> a,array<int,4> b){
		if(a[0]==b[0]) return a[1]>b[1];
		return a[0]<b[0];
	});
	vector<int> ss;
	vector<array<int,3>> ans;
	for(int i=0; i<n; i++){
		int gg=lower_bound(all(ss),lol[i][1])-ss.begin();
		if(gg==ss.size()) ss.pb(lol[i][1]);
		else ss[gg]=lol[i][1];
		ans.pb({lol[i][2],lol[i][3],gg+1});
	}
	cout<<ss.size()<<'\n';
	for(auto [x,y,z] : ans) cout<<x<<' '<<y<<' '<<z<<'\n';
	return 0;
}