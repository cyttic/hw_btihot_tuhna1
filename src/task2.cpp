
#include <iostream>
/*
 * Program to demonstrate a calculating the frequency of 
 * appearance of each letter in any ciphertext
 * 
 * There is need a string to analyse as parameter to start
 * Example of using:
 * $./task2 THISISMYTEXTTOANALYSE
 * 
 * IMPORTANT: USER TEXT AND USER KEY MUST BE WITHOUT SPACES!!
 * 
*/

#include <algorithm>
#include <iomanip>
#include "service.h"

using namespace std;

int main(int argc, char *argv[]){
	if (argc != 2){
		cerr << "Wrong number of arguments: needs text to frequency analyse" << endl;
		return -3;
	}
	string str = argv[1];
	//using function transform to make string a uppercase.
	transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::toupper(c); });
	auto result = getAbcFreq(str);
	for(int i = 0; i < result.size(); ++i){
		cout << char(65+i) << ": " << std::fixed << std::setprecision(4) << result[i];
		if (i > 0 && ((i+1) %5 == 0))//set up new lines
			cout << endl;
		else
			cout << ", ";
	}
	cout << endl;
}
