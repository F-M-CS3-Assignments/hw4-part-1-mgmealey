
#include "bdc.h"

#include <vector>
#include <cassert>
#include <iostream>
#include <set>
#include <string>

#define NPOS UINT32_MAX

using namespace std;

//turns vector into string to be outputted
string vec_to_string(const vector<int>& v){
	string output;
	output = output + "[";
	for (int i =  0; i < v.size() - 1; ++i){
		output = output + to_string(v[i]) + ", ";
	}
	output = output + to_string(v[v.size() - 1]) + "]";

	return output;
}

vector<int> sort(vector<int> input){

	vector<int> sorted_vec;
	int start = 0;

	while (!input.empty()){
		//first find smallest number in sequence
		int min_idx = 0;
		int min = input[0];

		for(time_t i = 0; i < input.size(); ++i){
			if (input[i] < min){
				min = input[i];
				min_idx = i;
			}
		}
		
		//add min number to new sorted vector and then remove it from the original vector
		sorted_vec.push_back(min);
		input.erase(input.begin() + min_idx);

	}
	return sorted_vec;
}

//From the position i+1, find the position of next number in the input vector which
//is divisible by input[i]
int find_next_dividend(const vector<int>& input, int start){
	for (int i = start; i < input.size(); ++i){
		//cout << input[i] << " % " << input[start] << " = " << input[i] % input[start] << endl;
		if (input[i] % input[start - 1] == 0){
			return i;
		}
	}
	return -1;
}

vector<int> sub_vec(vector<int> input, int start){
	vector<int> answer;
	if (start > 0){
		for (int i = start; i < input.size(); i++){
			answer.push_back(input[i]);
		}
	}
	return answer;
}

vector<int> longest_vector(const vector<vector<int>>& candidates){
	
	int max_length = candidates[0].size();
	int idx_longest = 0;

	for (int i = 0; i < candidates.size(); ++i){
		if(candidates[i].size() > max_length){
			max_length = candidates[i].size();
			idx_longest = i;
		}
	}
	return candidates[idx_longest];
}

vector<int> combine(vector<int>& l, vector<int>& r){

	if(r.size() > 0 && r.at(0) % l.at(0) != 0){
		return l;
	}
	
	vector<int> output;

	for(size_t i = 0; i < l.size(); i++){
		output.push_back(l.at(i));
	}

	for(size_t i = 0; i < r.size(); i++){
		output.push_back(r.at(i));
	}

	return output;
}

vector<int> bdc_helper(vector<int>& input){
	if (input.size() == 1 || input.size() == 0){
		return input;
	}

	vector<vector<int>> candidates;

	for (size_t i = 0; i < input.size(); i++){
		vector<int> l;
		l.push_back(input[i]);
		int next_div = find_next_dividend(input, (i + 1));

		if (next_div == -1){
			candidates.push_back(l);
			continue;
		}

		vector<int> rin = sub_vec(input, next_div);

		vector<int> r = bdc_helper(rin);

		vector<int> cand_v = combine(l, r);

		candidates.push_back(cand_v);
	}

	return longest_vector(candidates);
}

vector<int> biggest_divisible_conglomerate(vector<int>& input){
	vector<int> sorted = sort(input);
	return bdc_helper(sorted);
}

// void tests(){
// 	// //test sort
// 	// cout << "Testing sort" << endl;
// 	vector<int> values = {28, 22, 7, 2, 8, 14, 24, 56};
// 	sort(values.begin(), values.end(), greater<int>());

// 	assert(vec_to_string(values) == "[56, 28, 24, 22, 14, 8, 7, 2]");
	

// 	cout << "testing find dividend" << endl;
// 	int next_divident = find_next_dividend(values, 0);
// 	cout << next_divident << endl;
// 	assert(next_divident == 1);
// }


int main() {

	// tests();

	// Test 1 (example from assignment description)
	vector<int> values = {28, 22, 7, 2, 8, 14, 24, 56};
	vector<int> ans = biggest_divisible_conglomerate(values);
	cout << "input: " << vec_to_string(values) << endl;
	cout << "output: " << vec_to_string(ans) << endl << endl;
	set<int> answerSet(ans.begin(), ans.end());
	set<int> soln = {56, 14, 7, 28};
	bool first = (answerSet == soln);
	soln = {56, 28, 14, 2};
	bool second = (answerSet == soln);
	assert(first || second);


	// Test 2
	values = {10, 5, 3, 15, 20};
	ans = biggest_divisible_conglomerate(values);
	cout << "input: " << vec_to_string(values) << endl;
	cout << "output: " << vec_to_string(ans) << endl << endl;
	soln = {20, 5, 10};
	set<int> answerSet2(ans.begin(), ans.end());
	assert(answerSet2 == soln);

	// write your own tests here!

	return 0;
}