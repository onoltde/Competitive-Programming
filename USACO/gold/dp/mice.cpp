#include<bits/stdc++.h>
using namespace std;
 
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
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

template<typename T>
T fpow(T a,int z){
	T ret=1;
	for(; z; z>>=1){
		if(z&1) ret=(ret*a);
		a=(a*a);
	}
	return ret;
}

const int mxn=16;

int n;
int x[mxn],y[mxn];
double t[mxn];
double gg;

double dis(int x1,int y1,int x2,int y2){
	double xx=(double)(x1-x2);
	double yy=(double)(y1-y2);
	return sqrt(xx*xx+yy*yy);
}

bool ch(double v){
	vector<bool> vis((1<<n),0);
	vector<vector<double>> dp((1<<n),vector<double>(n,1e9));
	for(int i=0; i<n; i++) dp[0][i]=0;
	for(int i=1; i<(1<<n); i++){
		double vv=fpow(gg,__builtin_popcount(i)-1)*v;
//		cout<<vv<<' '<<__builtin_popcount(i)<<' '<<v<<" \n";
		for(int j=0; j<n; j++){
			if((i&(1<<j))==0) continue;
			int nw=i^(1<<j);
			for(int k=0; k<n; k++){
				if((nw&(1<<k))==0) continue;
				mnn(dp[i][j],dp[nw][k]+dis(x[k],y[k],x[j],y[j])/vv);
			}
			if(nw==0) dp[i][j]=dis(0,0,x[j],y[j])/vv;
			if(dp[i][j]>t[j]) dp[i][j]=1e9;
		}
//		cout<<vv<<" loooool\n";
	}
//	cout<<dp[(1<<n)-1][0]<<' '<<v<<'\n';
//	cout<<"dis = "<<dis(0,0,x[0],y[0])<<' '<<x[0]<<' '<<y[0]<<'\n';
	for(int i=0; i<n; i++) if(dp[(1<<n)-1][i]<=t[i]) return 1;
	return false;
}

signed main(){
	fast;
	cin>>n;
	for(int i=0; i<n; i++){
		cin>>x[i]>>y[i]>>t[i];
	} 
	string str;
	cin>>str;
	for(int i=1; i<str.size(); i++){
		gg=gg*10.0+(double)(str[i]-'0');
	}
	gg/=fpow(10.0,(int)str.size()-1);
	double r=1000000001.0;
	double l=0;
	while(r-l>0.000000001){
		double m=(l+r)/2.0;
		if(ch(m)) r=m;
		else l=m;
//		cout<<l<<' '<<r<<'\n';
	}
//	cout<<ch(r)<<'\n';
	cout<<fixed<<setprecision(5);
	cout<<r<<'\n';
}