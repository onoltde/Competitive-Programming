#include<bits/stdc++.h>
#include<sys/time.h>
using namespace std;
 
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define mp make_pair

#define int long long
 
typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
typedef multiset<int> msi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn = 5e4 + 10;

int ppa[mxn], ppb[mxn];
vector<bool> vis;
vector<int> g[mxn];

bool dfs(int now) {
    if(vis[now]) {
        return false;
    }
    vis[now] = true;
    for(int x : g[now]) {
        if(ppb[x] == 0) {
            ppa[now] = x;
            ppb[x] = now;
            vis[x] = false;
            return true;
        }
    }
    for(int x : g[now]) {
        if(dfs(ppb[x])) {
            ppa[now] = x;
            ppb[x] = now;
            vis[x] = false;
            return true;
        }
    }
    return false;
}

signed main() {
    fast;
    int n, m, p;
    cin >> n >> m >> p;
    for(int i = 0; i < p; i++) {
        int x, y;
        cin >> x >> y;
        g[x].pb(y);
    }
    int ans = 0;
    bool fl = 0;
    while(!fl) {
        fl = true;
        vis = vector<bool>(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            if(ppa[i] == 0 && dfs(i)) {
                ans++;
                fl = false;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}