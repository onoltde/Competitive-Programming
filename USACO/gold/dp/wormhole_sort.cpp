#include<bits/stdc++.h>
using namespace std;

#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
//#define int long long

//template<typename... T>
//void s(T&... args) { ((cin >> args), ...);}
//template<typename... T>
//void p(T&&... args) { ((cout << args << " "), ...);}
//template<typename... T>
//void pl(T&&... args) { ((cout << args << " "), ...); cout<<'\n';}

typedef vector<int> vi;
typedef pair<int,int> pi;
typedef set<int> si;
typedef multiset<int> msi;

inline void mxx(int &a,int b)
{
	if(b>a) a=b;
}

inline void mnn(int &a,int b)
{
	if(b<a) a=b;
}

const int mxn=1e5+10;
vector<int> dsu[mxn];
int par[mxn];
int dp[mxn];
int p[mxn];

int get(int x)
{
	if(par[x]==x) return x;
	else return par[x]=get(par[x]);
}

int cnt;
void join(int x,int y)
{
//	cout<<x<<" "<<y<<"\n";
	x=get(x);
	y=get(y);
	if(dsu[x].size()<dsu[y].size()) swap(x,y);
	par[y]=x;
	for(int l : dsu[y])
	{
		int i=l;
		while(dp[i]==1)
		{
			int ii=get(i);
			int jj=(get(p[i]));
			if(ii==jj)
			{
				cnt--;
				dp[i]=0;
				i=p[i];
			} 
			else break;	
		}
	}
	for(int i : dsu[y]) dsu[x].pb(i);
	dsu[y].clear(); 
}

void go()
{
	int n,m;
	cin>>n>>m;
	for(int i=0; i<n; i++) cin>>p[i],p[i]--;
	vector<array<int,3>> g;
	for(int i=0; i<m; i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		a--;
		b--;
		g.pb({c,a,b});
	}
	for(int i=0; i<n; i++) dsu[i].pb(i),par[i]=i;
	sort(g.rbegin(),g.rend());
	for(int i=0; i<n; i++) if(p[i]!=i) cnt++,dp[p[i]]=1;
	int ans=-1;
	for(int i=0; i<m && cnt; i++)
	{
		if(get(g[i][1])==get(g[i][2])) continue;
		join(get(g[i][1]),get(g[i][2]));
		ans=g[i][0];
	}
	cout<<ans<<"\n";
}


signed main()
{
	fast;
	freopen("wormsort.in","r",stdin);
	freopen("wormsort.out","w",stdout);
	int t=1;
//	s(t);
	while(t--) go();
}