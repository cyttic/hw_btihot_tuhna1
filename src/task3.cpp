
/*
 * Program to demonstrate a calculating the value of IC
 * for text encoded with Vigenere cipher.
 * 
 * There is need a string to analyse as parameter to start
 * or it can use without any parametrs with example text by default
 * Example of using:
 * $./task3 cmlmtywcrmvuxugmnhkgmnabvqfmnjvwnvtxoeqwudnymltxojdivucqviymsrgbhuggmltxopdaaidmqghynbdviddfdmvubwczofvgjmacoknzybylfnohqmsbedgyhbidqrnjehokdububccjyjrmrmwxynzcsudmkqsjolswtxootqejgfhapubqnntxoczztxdfdziloprkahbwrwnwcdqwmtsqsinjvymlsqxbsperspcatuvjxwujbsspsyxrgmihmyktsypwnclycrdvcboyqtyoyskthukpspefkqsbhuzpdaeddymltxodtbuhogmbehduhvetvgjmsjbgm
 * 
 * IMPORTANT: USER TEXT AND USER KEY MUST BE WITHOUT SPACES!!
 * The program was tested with encoded texts of around 500
 * characters and works correctly with texts of this length or longer.
 * 
*/

#include <iostream>
#include <algorithm>
#include <iomanip>
#include "service.h"

using namespace std;

int main(int argc, char *argv[]){
	
	string vec = "moijbmvrfkvagmsqqyfwwhcikalxsesfhhnegkxalrldmfzevyslzxalvbcikiiyvvxjpbtfbuknwxallbsptnebujtzxulgtbwxoiphrmlhmvvxhgaalxvpwavxlemalxasivjmoifvygaebuaalvxalxvaezmgnegkxalabuhpomlwikzwxjvxawbuxhalxlekzsyalhziposwhvxasxetevvxalxkiiallvjmoigpkaaaappxzxtywphxvowbsigaprhfhcizbmwprzalxjykpsnzqbuhlalkvyzowahhhdwtuhwyittwppxasmzoxlvjavtxhrwzxhymxzygasekatpxbukihxblrmscmvfxbrvvzxyiwicmoiuyeolegkxalvxzxelwlzsnsw";
	if (argc == 2)
		vec = argv[1];
	else if (argc > 2){
		cerr << "There is a wrong number parameters to this program\n"
				"usage: ./task3 YOURCHIPREDTEXT or just ./task3 to use encoded text by default" << endl;
		return -7;
	}
	transform(vec.begin(), vec.end(), vec.begin(), [](unsigned char c) { return std::toupper(c); });
	auto result = getCommonSubVec(vec);
	auto s = trustedDistances(result);
	if (s.size() == 0){
		cerr << "There is not found pattern to decode a text" << endl;
		return -6;
	}
	getKeyLength(vec,s);
	
	return 0;
}
