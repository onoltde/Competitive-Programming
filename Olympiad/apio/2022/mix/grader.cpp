#include<bits/stdc++.h>
#include"mix.h"
using namespace std;

int X, K, M, T, seed;

void wrong(string str){cout << str << endl; exit(1);}
void propose_check(vector<vector<bool>> &A){
	bool right = A.size() == M; for(auto &t : A) right &= t.size() == X;
	if(!right) wrong("Invalid Proposal");
}
void repeating_number_check(vector<int> &R, int id){
	if(R.size() != set < int >(R.begin(), R.end()).size())
		wrong("Detection " + to_string(id) + " Repeating Numbers");
}
void out_of_bound_check(vector<int> &R, int id){
	bool right = 1; for(auto &t : R) right &= t >= 0 && t <= X - 1;
	if(!right) wrong("Detection " + to_string(id) + " Out of Bound");
}
void same_check(vector<int> &R, vector<int> &P, int id){
	bool right = 1; if(R.size() != P.size()) right = 0;
	set < int > positive(P.begin(), P.end());
	for(auto &t : R) right &= positive.find(t) != positive.end();
	if(!right){
		stringstream output;
		output << "Failed Detection " << id << endl;
		output << "Your Answer:";
		for(auto t : R) output << " " << t;
		output << endl;
		output << "Correct Answer:";
		for(auto t : P) output << " " << t;
		output << endl;
		wrong(output.str());
	}
}

int main(){
	cin >> X >> K >> M >> T >> seed; mt19937 rnd(seed);
	vector<vector<bool>> A = propose(X, K, M);
	propose_check(A);
	
	for(int i = 1 ; i <= T ; ++i){
		int C = rnd() % K + 1; vector < int > positive;
		if(K <= 4){
			set < int > P; while(P.size() < C) P.insert(rnd() % X);
			positive = vector<int>(P.begin(), P.end());
		}else{
			vector < int > P;
			for(int i = 0 ; i < X ; ++i) P.push_back(i);
			shuffle(P.begin(), P.end(), rnd);
			positive = vector<int>(P.begin(), P.begin() + C);
		}
		vector<bool>R(M, 0);
		for(int i = 0 ; i < M ; ++i) for(auto t: positive) R[i] = R[i] | A[i][t];
		vector < int > result = detect(X, K, M, A, R);
		repeating_number_check(result, i);
		out_of_bound_check(result, i);
		same_check(result, positive, i);
	}
	cout << "Accepted." << endl;
	return 0;
}