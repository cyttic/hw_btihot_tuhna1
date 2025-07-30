#include <vector>
#include <map>
#include <iostream>
#include "service.h"

using namespace std;

int main(){
	//string vec = "KCCPBGUFDHQTYAVINRRTMVGKDNBVFDETDGITLXRGUDDKOTFMBPVGELTGCKVQAOCWDNAMCRXIZAKFTLEWRPTYCQKYVXCHKTFPONCQRHJVQAJWETMCMSPKDYHJVDAHCTRLSVSKCGCZQDZXGSFRLSWCWSJTBHAFSIASPRJAHKJRJUMVGKMIZHFPDISFZVLVNGTFPLKEBDPGCBSHCTJRWKBAFSFEZQNRWXCVCGAONWDKACKAWBBIKFTIOVKCGGHVVLNHICWHJVLNHIQIBTKHJVNPIST";
	string vec = "KCCPKBGUFDPHQTYAVINRRMTWGRKDNBVFDETDGILTXRGUD"
	//string vec = "akfc12345kfc";
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
