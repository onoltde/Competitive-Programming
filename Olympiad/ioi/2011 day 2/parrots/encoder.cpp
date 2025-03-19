#include "encoder.h"
#include "encoderlib.h"
#include<bits/stdc++.h>
using namespace std;

#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

//#define int long long
 
typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
typedef multiset<int> msi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

const int B = 10000, A = 40;
struct bigNum {
	array<int, A> dig;
	bigNum(int x = 0) {
		for(int i = 0; i < A; i++) {
			dig[i] = x % B;
			x /= B;
		}
	}
	bigNum& operator+=(const bigNum &b) {
		int carry = 0;
		for(int i = 0; i < A; i++) {
			dig[i] += b.dig[i] + carry;
			carry = dig[i] / B;
			dig[i] %= B;
		}
		return *this;
	};
	bigNum& operator-=(const bigNum &b) {
		for(int i = 0; i < A; i++) {
			dig[i] -= b.dig[i];
			while(dig[i] < 0) {
				assert(i + 1 < A);
				dig[i] += B;
				dig[i + 1]--;
			}
		}
		return *this;
	}
	bigNum& operator*=(const int &b) {
		int carry = 0;
		for(int i = 0; i < A; i++) {
			dig[i] *= b;
			dig[i] += carry;
			carry = dig[i] / B;
			dig[i] %= B;
		}
		return *this;
	}
	friend bigNum operator+(const bigNum &a, const bigNum &b) {
		return bigNum(a) += b;
	}
	friend bigNum operator-(const bigNum &a, const bigNum &b) {
		return bigNum(a) -= b;
	}
	friend bigNum operator*(const bigNum &a, const int &b) {
		return bigNum(a) *= b;
	}
	int compare(const bigNum &a) {
		for(int i = A - 1; i >= 0; i--) {
			if(a.dig[i] > dig[i]) return -1;
			else if(a.dig[i] < dig[i]) return 1;
		}
		return 0;
	}
	bool operator<(const bigNum &b) {
		return this->compare(b) == -1;
	}
	bool operator>(const bigNum &b) {
		return this->compare(b) == 1;
	}
	bool operator==(const bigNum &b) {
		return this->compare(b) == 0;
	}
	bool operator!=(const bigNum &b) {
		return this->compare(b) != 0;
	}
	bool operator<=(const bigNum &b) {
		return this->compare(b) != 1;
	}
	bool operator>=(const bigNum &b) {
		return this->compare(b) != -1;
	}
	friend ostream& operator<<(ostream& out, const bigNum &a) {
		for(int i = 0; i < 10; i++) {
			out << a.dig[i];
			if(i + 1 < A) out << ", ";
		}
		out << ';';
	}
};


void encode(int n, int a[]) {
	bigNum val(0);
	vector<bigNum> pw(1, 1);
	for(int i = 1; i < n; i++) {
		pw.pb(pw.back() * 256);
	}
	for(int i = 0; i < n; i++) {
		val += pw[i] * a[i];
	}
	int len = n * 5;
	vector<vector<bigNum>> dp(len + 1, vector<bigNum>(256, 0));
	// dp[0] = vector<bigNum>(256, 1);
	dp[0][0] = 1;
	for(int i = 1; i <= len; i++) {
		for(int j = 0; j < 256; j++) {
			dp[i][j] = dp[i - 1][j];
			if(j - 1 >= 0) dp[i][j] += dp[i][j - 1];
		}
	}
	for(int i = len; i >= 1; i--) {
		int ans = 0;
		for(int j = 0; j < 256; j++) {
			if(dp[i][j] > val) {
				ans = j;
				break;
			}
			val -= dp[i][j];
		}
		send(ans);
	}
}
