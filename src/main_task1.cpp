#include <iostream>
#include "service.h"

using namespace std;

int main(){
	string text = "CRYPTO GRAPHY";
	string key = "DUH";
	string encodedStr = encVigenere(text,key);
	cout << encodedStr << endl;
	cout << "--------------------" << endl;
	cout << decVigenere(encodedStr, key) << endl;
	
	return 0;
}

