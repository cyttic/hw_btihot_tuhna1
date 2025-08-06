/*
 * Program to demonstrate a work of encode-decode functions
 * from task 1 of homework of course "bthihot tuhna"
 * 
 * Usage: call executable without parameters will encoded text 
 * "CRYPTO GRAPHY" by key "KEY" by default.
 * Call with 2 string params will decode and encode user's text with
 * user key.
 * 
 * * Example of using:
 * $./task1 encodeitplease example_key
 * 
 * IMPORTANT: USER TEXT AND USER KEY MUST BE WITHOUT SPACES!!
 * 
*/

#include <iostream>
#include "service.h"

using namespace std;

int main(int argc, char *argv[]){
	string text = "CRYPTO GRAPHY";
	string key = "KEY";
	if (argc == 3){//looks like there are params for text and key
		text = argv[1];
		key = argv[2];
	}
	string encodedStr = encVigenere(text,key);
	cout << "-------ENCODED TEXT-------------" << endl;
	cout << encodedStr << endl;
	cout << "-------DECODED TEXT-------------" << endl;
	cout << decVigenere(encodedStr, key) << endl;
	return 0;
}

