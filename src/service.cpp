#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <set>
#include <iterator>
#include <limits>
#include "service.h"

using namespace std;

string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//this function realises Step 1 of algorithm
map<string, vector<int>> getCommonSubVec(const string &arr){
	map<string, vector<int>> result;
	//string arr = source;//set source string to uppercase
	//transform(arr.begin(), arr.end(), arr.begin(), [](unsigned char c) { return std::toupper(c); });
	for(int i = 0; i < arr.size()-4; ++i){
		string tmp(arr.begin()+i, arr.begin()+i+3);
		if ( result.count(tmp) != 0 ||//check if result contains alredy this substring
				std::find_if(tmp.begin(), tmp.end(),//and also all of symbols of substring is letters
                   [](char c) { return !std::isalpha(c); }) != tmp.end())
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

vector<int> mostLongVec(const map<string, vector<int>>&m){
	vector<int>result;
	for (const auto& pair : m) {
        if(pair.second.size() > result.size())
			result = pair.second;
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

set<int> getDivisors(int val){
	set<int>result;
	for(int i = 2; i <= val; ++i)
		if (val % i == 0)
			result.insert(i);
	return result;
}

set<int> getDivFromVec(const vector<int> &vec){
	set<int>result;
	set<int>first = getDivisors(vec[0]);
	for(int i = 1; i < vec.size(); ++i){
		auto divisors = getDivisors(vec[i]);
		std::set_intersection(divisors.begin(), divisors.end(), first.begin(), first.end(), std::inserter(result, result.begin()));
		first = result;
	}
	return result;
}


vector<double> testKasiski(const string &str, int n){
	//we need to divide a text on n pieces and find IC.
	int len = str.size() %n == 0? str.size()/n : 1 + str.size()/n;
	//cout << "LEN: " << len << endl;
	//int len = str.size()/n ;
	vector<double>result;
	for(int i = 0; i < n; ++i){
		int j =i;
		string str_current;
		while(str_current.size() != len && j < str.size()){
			str_current += str[j];
			j += n;
		}
		//cout << "current word: " << str_current.size() << " " << str_current << endl;
		//count the letter frequencies
			int letters[26] = {0};
			for(int j = 0 ; j < str_current.size(); ++j)
				letters[str_current[j]-65]++;	
			//calculate the cumerator
			double sum = 0;
			for(int j = 0; j < 26;++j)
				sum += letters[j]*(letters[j]-1);
			//calculate the denominator: N(N-1)
			int den = str_current.size()*(str_current.size()-1);
			result.push_back(sum/den);
	}
	return result;
}

/*
char getFrequencyLetter(const string &str){
	int ch[26] = {0};
	for(int i = 0; i < str.size(); ++i)
		ch[str[i]-65]++;
	int Max = 0;
	for(int i = 0; i < 26; ++i)
		if (ch[i] > ch[Max])
			Max = i;
	return char( Max );
}


vector<char> getFrequencyLetterVec(const string &str){
	vector<char>vec(26);
	for(int i = 0; i < str.size(); ++i)
		vec[str[i]-65]++;
	return vec;
}

string getKey(const string &str, int n){
	int len = str.size() %n == 0? str.size()/n : 1 + str.size()/n;
	string result;
	for(int i = 0; i < n; ++i){
		int j =i;
		string str_current;
		while(str_current.size() != len && j < str.size()){
			str_current += str[j];
			j += n;
		}
		//cout << "string is: " << str_current << endl;
		auto v = getFrequencyLetterVec(str_current);
		//for(int i = 0; i < 26; ++i)
		//	cout << char(i+65) << ":" << (int)v[i] << " ";
		//cout << endl;

		char shift_i = ( (65+getFrequencyLetter(str_current))-'E' + 26)%26;
		char letter = char( shift_i + 'A' );
		result += letter;
	}
	return result;
}
*/

vector<double> getAbcFreq(const string &str){
	vector<double>result(26);
	for(int i = 0; i < str.size(); ++i)
		result[str[i]-65]++;
	/*
	for(int i = 0; i < str.size(); ++i)
		try{
			result.at(str[i]-65);
		}catch(const std::runtime_error& e){
			cout << "PROBLEM AT " << i << " " << str[i] << endl;
		}
		*/
	for(int i = 0; i < result.size(); ++i)
		result[i] = result[i]/str.size();
		
	return result;
}


const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/*
// English letter frequencies (A-Z)
const std::vector<double> ENGLISH_FREQS = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074
};
*/

const std::vector<double> ENGLISH_FREQS = {
	0.0626407, 0.037871, 0.0386899, 0.0331627, 0.0839304, 0.0229273,0.0282497,
	0.0431934,0.0462641,0.0227226, 0.0200614, 0.0292733,0.0315251,0.0745138,
	0.0665302,0.0204708, 0.0202661, 0.0700102,0.0407369, 0.057523, 0.0298874,
	0.0274309, 0.024565, 0.0206755,0.0284545,0.0184237
};


double cosangle(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    double dot_product = 0.0, norm1 = 0.0, norm2 = 0.0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        dot_product += vec1[i] * vec2[i];
        norm1 += vec1[i] * vec1[i];
        norm2 += vec2[i] * vec2[i];
    }
    norm1 = std::sqrt(norm1);
    norm2 = std::sqrt(norm2);
    if (norm1 == 0.0 || norm2 == 0.0) return 0.0;
    return dot_product / (norm1 * norm2);
}

std::string getKey(const std::string& ciphertext, int n) {
    // Clean ciphertext: keep only uppercase letters
    std::string cleaned_ciphertext;
    for (char c : ciphertext) {
        if (std::isupper(c)) {
            cleaned_ciphertext += c;
        }
    }

    // Split into n slices
    std::vector<std::string> slices(n, "");
    for (size_t i = 0; i < cleaned_ciphertext.size(); ++i) {
        slices[i % n] += cleaned_ciphertext[i];
    }

    // Compute frequencies for each slice
    std::vector<std::vector<double>> frequencies(n, std::vector<double>(26, 0.0));
    std::string key(n, 'A');

    for (int i = 0; i < n; ++i) {
        // Calculate frequency counts
        for (char c : slices[i]) {
            frequencies[i][ALPHABET.find(c)] += 1.0;
        }

        // Normalize frequencies
        double group_len = slices[i].size();
        if (group_len > 0) {
            for (int j = 0; j < 26; ++j) {
                frequencies[i][j] /= group_len;
            }
        }

        // Debug: Print frequencies for each group
        std::cout << "Group " << (i + 1) << " (length " << group_len << "): " << slices[i] << "\n";
        std::cout << "  Letter frequencies:\n";
        for (int j = 0; j < 26; ++j) {
            if (frequencies[i][j] > 0) {
                std::cout << "    " << ALPHABET[j] << ": " << frequencies[i][j] << "\n";
            }
        }

        // Find best shift using cosine similarity
        double best_score = -1.0;
        int best_shift = 0;
        if (group_len > 0) {
            for (int j = 0; j < 26; ++j) {
                std::vector<double> testtable;
                testtable.insert(testtable.end(), frequencies[i].begin() + j, frequencies[i].end());
                testtable.insert(testtable.end(), frequencies[i].begin(), frequencies[i].begin() + j);
                double score = cosangle(ENGLISH_FREQS, testtable);
                if (score > best_score) {
                    best_score = score;
                    best_shift = j;
                }
            }
            key[i] = ALPHABET[best_shift];
            std::cout << "  Best shift: " << best_shift << ", Cosine similarity: " << best_score << ", Key letter: " << key[i] << "\n";
        } else {
            std::cout << "  Empty group, defaulting to key letter 'A'\n";
        }
    }

    return key;
}
