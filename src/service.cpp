#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>
#include "service.h"

using namespace std;

string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//this function realises Step 1 of algorithm
map<string, vector<int>> getCommonSubVec(const string &arr){
	map<string, vector<int>> result;
	for(int i = 0; i < arr.size()-4; ++i){
		string tmp(arr.begin()+i, arr.begin()+i+3);
		if ( result.count(tmp) != 0)//check if result contains alredy this substring
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
