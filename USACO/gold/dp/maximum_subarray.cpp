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
 
int n;
 
int a[200010];
 
struct node{
	node *ch[2];
	node(){
		ch[1]=ch[0]=NULL;
	}
};
 
int search(node* root,int k,int d){
	if(d<0) return 0; 
	int dig = (k>>d) & 1;
	dig^=1;
	if(root->ch[dig]==NULL) return search(root->ch[dig^1], k, d-1) ^ ((dig ^ 1) << d);
	else return search(root->ch[dig], k, d-1) ^ (dig << d);
}
 
void insert(node *root,int k,int d){
	if(d < 0) return; 
	int dig = (k>>d) & 1;
	if(root->ch[dig]==NULL) root->ch[dig] = new node();
	insert(root->ch[dig], k, d-1);
}
 
int main(){
	fast;
	cin>>n;
	for(int i = 0; i < n; i++){
		cin>>a[i];
	}
	node *root = new node();
	int lol=0;
	int ans=0;
	for(int i = 0; i < n; i++){
		insert(root,lol,31);
		lol ^= a[i];
		ans = max(ans, lol^search(root,lol,31));
//		cout<<i<<'\n';
	}
	cout << ans << '\n';
	return 0;
}