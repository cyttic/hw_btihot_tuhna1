#include <vector>
#include <map>
#include <string>
#include "service.h"

using namespace std;

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
