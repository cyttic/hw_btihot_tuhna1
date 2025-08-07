#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <set>
#include <iterator>
#include <limits>
#include <numeric>
#include <unordered_map>
#include "service.h"

using namespace std;

string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const std::vector<double> ENGLISH_FREQS = {
	0.06264, 0.03787, 0.03868, 0.03316, 0.08393, 0.02292, 0.02824,
	0.04319, 0.04626, 0.02272, 0.02006, 0.02927, 0.03152, 0.07451,
	0.06653, 0.02047, 0.02026, 0.07001, 0.04073, 0.05752, 0.02989,
	0.02743, 0.02457, 0.02068, 0.02845, 0.01842
};


//this function realises Step 1 of algorithm
vector<pair<string, vector<int>>> getCommonSubVec(const string &arr){
		//The common idea: two inner loop to find matches at least 3 same letters
        map<string, vector<int>> result;
        for(int i = 0; i < arr.size()-4; ++i){
                string tmp(arr.begin()+i, arr.begin()+i+3);
                if ( result.count(tmp) != 0 ||//check if result contains alredy this substring
                                std::find_if(tmp.begin(), tmp.end(),//and also all of symbols of substring is letters
                   [](char c) { return !std::isalpha(c); }) != tmp.end())
                                continue;
                for(int j = i+1; j < arr.size()-2; ++j){
                        if (arr[i] == arr[j] && (arr[i+1] == arr[j+1]) && (arr[i+2] == arr[j+2]) ){
                                if( result.count(tmp) == 0)//we need to add substring to result if it was found in first time
                                        result[ tmp ].push_back(i+1);
                                result[ tmp ].push_back(j+1);
                        }
                }
        }
        //using std::vector to sort result and return
		vector<pair<string, vector<int>>> vec;
		for(auto &i : result)
			vec.push_back(make_pair(i.first,i.second));
		sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
			return a.second.size() > b.second.size(); // descending
		});
		return vec;
}

set<int> trustedDistances(const vector<pair<string, vector<int>>> &vec){
	set<int>result;
	for(auto &item : vec){
		auto vv = getDivFromVec( getDistances(item.second) );
		if (vv.size() > 1)
			result = vv;
	}
	return result;
}


//founding key length by instruction from task 3
int getKeyLength(const string &vec,const set<int>&s){
	vector<int>vec_len;
	pair<double, int>lenBlock;
	for(auto i : s){		
		cout<< "---------Checking a length of key = " << i << "---------" << endl;
		vec_len.push_back(i);
		auto res = testKasiski(vec,i);
		for(int j =0; j < res.size(); ++j)
			cout << "block " << j+1 << ": " << res[j] << endl;
		double average = accumulate(res.begin(),res.end(), 0.0)/res.size();
		if (abs(lenBlock.first-0.066) > abs(average - 0.066))
			lenBlock = make_pair(average, i);
		cout << "Average IC for key length of "<< i << " is " << average << endl;
	}
	cout <<"******** The most probably length of key is " << lenBlock.second << " with IC=" <<lenBlock.first << " ********" <<endl;
	return lenBlock.second;
}

//step 2
vector<int> getDistances(const vector<int> &vec){
	vector<int>result;
	for(int i = 1; i < vec.size(); ++i)
		result.push_back(vec[i] - vec[i-1]);
	return result;
}

//task1 - encoder Vigenere
string encVigenere(const string &text, const string &key){
	if (key.size() < 1){
		cerr << "Wrong length of key size" << endl;
		return "";
	}
	//prepare key to fit size of text
	string t = text;
	transform(t.begin(), t.end(), t.begin(), [](unsigned char c) { return std::toupper(c); });
	string k_tmp = key;
	transform(k_tmp.begin(), k_tmp.end(), k_tmp.begin(), [](unsigned char c) { return std::toupper(c); });
	string k;
	while( text.size() > k.size())
		k += k_tmp;
	k.resize(text.size());
	//encoding
	string result;
	for(int i =0; i < t.size(); ++i){
		if (ALPHABET.find(t[i]) != string::npos)//we're encoding only letters from ABC
			result += ALPHABET[((t[i]-65) + (k[i]-65))%26];
		else
			result += t[i];
	}
	return result;
}

//task1 - decoder Vigenere
string decVigenere(const string &text, const string &key){
	if (text.size() < key.size() || key.size() < 1){
		cerr << "Wrong length of key size" << endl;
		return "";
	}
	//prepare key to fit size of text
	string t = text;
	transform(t.begin(), t.end(), t.begin(), [](unsigned char c) { return std::toupper(c); });
	string k_tmp = key;
	transform(k_tmp.begin(), k_tmp.end(), k_tmp.begin(), [](unsigned char c) { return std::toupper(c); });
	string k;
	while( text.size() > k.size())
		k += k_tmp;
	k.resize(text.size());
	//decoding
	string result;
	for(int i =0; i < t.size(); ++i){
		if (ALPHABET.find(t[i]) != string::npos){//we're decoding only letters from ABC
			int pos = (t[i]-65) - (k[i]-65);
			if (pos < 0)
				pos = 26 + pos;
			result += ALPHABET[pos];
		}else
			result += t[i];
	}
	return result;
}

//Function to find all of divisiors of number
set<int> getDivisors(int val){
	set<int>result;
	for(int i = 2; i <= val; ++i)
		if (val % i == 0)
			result.insert(i);
	return result;
}

//Function to find all of divisiors of vector of integers
set<int> getDivFromVec(const vector<int> &vec){
	set<int>result;
	set<int>first = getDivisors(vec[0]);
	for(int i = 1; i < vec.size(); ++i){
		auto divisors = getDivisors(vec[i]);
		std::set_intersection(divisors.begin(), divisors.end(), first.begin(), first.end(), std::inserter(result, result.begin()));
		first = result;
	}
	return result;
}

//function to find IC according the instruction from Task
vector<double> testKasiski(const string &str, int n){
	//we need to divide a text on n pieces and find IC.
	int len = str.size() %n == 0? str.size()/n : 1 + str.size()/n;
	vector<double>result;
	for(int i = 0; i < n; ++i){
		int j =i;
		string str_current;
		while(str_current.size() != len && j < str.size()){
			str_current += str[j];
			j += n;
		}
			int letters[26] = {0};
			for(int j = 0 ; j < str_current.size(); ++j)
				letters[str_current[j]-65]++;	
			//calculate the cumerator
			double sum = 0;
			for(int j = 0; j < 26;++j)
				sum += letters[j]*(letters[j]-1);
			//calculate the denominator: N(N-1)
			int den = str_current.size()*(str_current.size()-1);
			result.push_back(sum/den);
	}
	return result;
}

//task 2 solution
vector<double> getAbcFreq(const string &str){
	vector<double>result(26);
	for(int i = 0; i < str.size(); ++i)
		result[str[i]-65]++;
	for(int i = 0; i < result.size(); ++i)
		result[i] = result[i]/str.size();
		
	return result;
}

//Function to find how much closer values of two std::vectors
double cosangle(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    double dot_product = 0.0, norm1 = 0.0, norm2 = 0.0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        dot_product += vec1[i] * vec2[i];
        norm1 += vec1[i] * vec1[i];
        norm2 += vec2[i] * vec2[i];
    }
    norm1 = std::sqrt(norm1);
    norm2 = std::sqrt(norm2);
    if (norm1 == 0.0 || norm2 == 0.0) return 0.0;
    return dot_product / (norm1 * norm2);
}

//solution of task4
std::string getKey(const std::string& ciphertext, int n) {
    // Split into n slices
    std::vector<std::string> slices(n, "");
    for (size_t i = 0; i < ciphertext.size(); ++i) {
        slices[i % n] += ciphertext[i];
    }
    // Compute frequencies for each slice
    std::vector<std::vector<double>> frequencies(n, std::vector<double>(26, 0.0));
    std::string key(n, 'A');
    for (int i = 0; i < n; ++i) {
        // Calculate frequency counts
        double group_len = slices[i].size();
        frequencies[i] = getAbcFreq(slices[i]);
        // Find best shift using cosine similarity
        double best_score = -1.0;
        int best_shift = 0;
        if (group_len > 0) {
            for (int j = 0; j < 26; ++j) {
                std::vector<double> testtable;
                testtable.insert(testtable.end(), frequencies[i].begin() + j, frequencies[i].end());
                testtable.insert(testtable.end(), frequencies[i].begin(), frequencies[i].begin() + j);
                double score = cosangle(ENGLISH_FREQS, testtable);
                if (score > best_score) {
                    best_score = score;
                    best_shift = j;
                }
            }
            key[i] = ALPHABET[best_shift];
        }
    }
    return key;
}
