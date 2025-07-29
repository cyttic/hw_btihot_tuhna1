#include <cstring>
#include <vector>

using namespace std;

//this function realises Step 1 of algorithm
vector<string> getCommonSubVec(const vector<char>&arr){
	vector<int> result;
	for(int i = 0; i < arr.size()-4; ++i){
		for(int j = i+2; j < arr.size() -2; ++j)
			if (&arr[i] == &arr[j] && &arr[i+1] + &arr[j+1]){//
				result.append(i);
				break;
			}
	}
	while(1 == 1){//suppose that it's impossible to get infinity loop because the vector "arr" is finite
		int size_before = result[0].size();
		for(int i = 0; i < result.size(); ++i){
			if (result.size
		}
		if (size_before == result[0].size())
			break;
	}
	
	return result;
}
