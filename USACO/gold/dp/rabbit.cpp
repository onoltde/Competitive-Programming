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

const int mod=1e9+7;

void add(int &a,int b){
	a+=b;
	if(a>=mod) a-=mod;
}

signed main(){
	int n,m;
	cin>>n>>m;
	vector<int> a(n); 
	vector<int> b;
	for(int i=0; i<n; i++){
		cin>>a[i];
		if((i+1)*m>=a[i]) b.pb(m*(i+1)-a[i]); 
	}
	multiset<int> s;
	for(int i=0; i<b.size(); i++){
		auto it=s.upper_bound(b[i]);
		if(it==s.end()) s.in(b[i]);
		else s.erase(it),s.in(b[i]);
	}
	cout<<n-(int)s.size()<<'\n';
}