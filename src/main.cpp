#include <vector>
#include <map>
#include <iostream>
#include "service.h"

using namespace std;

int main(){
	string vec = "ksp 123456 ksp4321 ksp";
	//string vec = "lm ahh cudhr mou whlfosawcug wbl puiiaecsiws vf wbl rdhkop woolwl oinoe vute oyathl awlwl iq noe jcceq nlxw. Qptk noiv cudhr pt lm wovmpboy ao fblcn bvw pojh wbldlmarlvbtliu oi noe oyathlz iq noe wyet lm jlrml tr noe xhpfrlt dlmarlvbtliu. Tky saqabajy dhhlledwo lhnaeu xpswlpbxnpoq cz uqcmoug";
	//string vec = "akfc12345kfc";
	auto result = getCommonSubVec(vec);
	//cout<<result.size()<<endl;
	/*
	for(auto pair : result){
		std::cout << pair.first << " ";
		for(auto val: pair.second)
			std::cout << val << " ";
		cout << endl;
	}
	*/
	vector<int>v = mostLongVec(result);
	auto distances = getDistances(v);
	auto s = getDivFromVec(distances);
	for(auto i : distances)
		cout<< i << endl;
		
		
	return 0;
}
