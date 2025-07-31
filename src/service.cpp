#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <set>
#include <iterator>
#include "service.h"

using namespace std;

string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//this function realises Step 1 of algorithm
map<string, vector<int>> getCommonSubVec(const string &arr){
	map<string, vector<int>> result;
	//string arr = source;//set source string to uppercase
	//transform(arr.begin(), arr.end(), arr.begin(), [](unsigned char c) { return std::toupper(c); });
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
	return result;
}

vector<int> mostLongVec(const map<string, vector<int>>&m){
	vector<int>result;
	for (const auto& pair : m) {
        if(pair.second.size() > result.size())
			result = pair.second;
    }
    return result;
}

//step 2
vector<int> getDistances(const vector<int> &vec){
	vector<int>result;
	for(int i = 1; i < vec.size(); ++i)
		result.push_back(vec[i] - vec[i-1]);
	return result;
}

//task1
string encVigenere(const string &text, const string &key){
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
	//encoding
	string result;
	for(int i =0; i < t.size(); ++i){
		if (ABC.find(t[i]) != string::npos)//we're encoding only letters from ABC
			result += ABC[((t[i]-65) + (k[i]-65))%26];
		else
			result += t[i];
	}
	return result;
}

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
		if (ABC.find(t[i]) != string::npos){//we're decoding only letters from ABC
			int pos = (t[i]-65) - (k[i]-65);
			if (pos < 0)
				pos = 26 + pos;
			result += ABC[pos];
		}else
			result += t[i];
	}
	return result;
}

set<int> getDivisors(int val){
	set<int>result;
	for(int i = 2; i <= val; ++i)
		if (val % i == 0)
			result.insert(i);
	return result;
}

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


vector<double> testKasiski(const string &str, int n){
	//we need to divide a text on n pieces and find IC.
	int len = str.size() %n == 0? str.size()/n : 1 + str.size()/n;
	//cout << "LEN: " << len << endl;
	//int len = str.size()/n ;
	vector<double>result;
	for(int i = 0; i < n; ++i){
		int j =i;
		string str_current;
		while(str_current.size() != len && j < str.size()){
			str_current += str[j];
			j += n;
		}
		//cout << "current word: " << str_current.size() << " " << str_current << endl;
		//count the letter frequencies
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

char getFrequencyLetter(const string &str){
	vector<char>ch(26);
	for(int i = 0; i < ch.size(); ++i)
		ch[str[i]-65]++;
	int Max = 0;
	for(int i = 0; i < ch.size(); ++i)
		if (ch[i] > ch[Max])
			Max = i;
	return char( Max + 65 );
}

string getKey(const string &str, int len){
	int len = str.size() %n == 0? str.size()/n : 1 + str.size()/n;
	string result;
	for(int i = 0; i < n; ++i){
		int j =i;
		string str_current;
		while(str_current.size() != len && j < str.size()){
			str_current += str[j];
			j += n;
		}
		result += getFrequencyLetter(str_current);
	}
	return result;
}


