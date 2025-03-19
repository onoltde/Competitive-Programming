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

const int mxm=22;
const int mxn=1e5+10;

int a[mxn];
int is[30];
int dp[1<<mxm];
int cnt[mxm][mxm];

signed main(){
	fast;
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	string str;
	cin>>str;
	int cn=0;
	int n=(int)str.size();
	memset(is,-1,sizeof(is));
	for(int i=0; i<n; i++){
		if(is[str[i]-'a']==-1){
			is[str[i]-'a']=cn;
			cn++;
		}
		a[i]=is[str[i]-'a'];
	}
	for(int i=1; i<n; i++) cnt[a[i-1]][a[i]]++;
	dp[0]=1;
	for(int i=1; i<(1<<cn); i++){
		dp[i]=1e9;
		for(int j=0; j<cn; j++){
			if((i&(1<<j))==0) continue;
			int tmp=dp[i^(1<<j)];
			for(int k=0; k<cn; k++){
				if((i&(1<<k))==0) continue;
				tmp+=cnt[j][k];
			}
			mnn(dp[i],tmp);
		}
	}
//	cout<<cn<<'\n';
	cout<<dp[(1<<cn)-1]<<'\n';
}