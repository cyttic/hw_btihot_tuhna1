#include <vector>
#include <map>
#include <iostream>
#include "service.h"

using namespace std;

int main(){
	string vec = "sdf111sdf121sf";
	auto result = getCommonSubVec(vec);
	//cout<<result.size()<<endl;
	for(auto pair : result){
		std::cout << pair.first << " ";
		for(auto val: pair.second)
			std::cout << val << " ";
		cout << endl;
	}
	return 0;
}
