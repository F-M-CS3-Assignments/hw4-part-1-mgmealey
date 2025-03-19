
#include "bdc.h"

#include <vector>
#include <cassert>
#include <iostream>
#include <set>
#include <string>

using namespace std;

//turns vector into string to be outputted
string vec_to_string(vector<int> v){
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

vector<int> biggest_divisible_conglomerate(vector<int> input){
	vector<int> sorted_vector = sort(input);
	return sorted_vector;
}


void tests(){
	//test sort
	cout << "Testing sort" << endl;
	vector<int> values = {28, 22, 7, 2, 8, 14, 24, 56};
	vector<int> sorted_vec = sort(values);
	assert(vec_to_string(sorted_vec) == "[2, 7, 8, 14, 22, 24, 28, 56]");
	cout << "tests passed!" << endl;
	
}


int main() {

	tests();

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
