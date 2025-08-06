#include <map>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

//task1
std::string encVigenere(const std::string &, const std::string &);
std::string decVigenere(const std::string &, const std::string &);

std::set<int> getDivisors(int val);
std::set<int> getDivFromVec(const std::vector<int> &);
std::vector<int> getDistances(const std::vector<int> &vec);
std::vector<double> testKasiski(const std::string &str, int n);

std::string getKey(const std::string &str, int len);
char getFrequencyLetter(const std::string &str);
std::vector<char> getFrequencyLetterVec(const std::string &str);
std::vector<double> getAbcFreq(const std::string &str);

std::vector<int> mostLongVec(const std::unordered_map<std::string, std::vector<int>>&m);

//std::map<std::string, std::vector<int>> getCommonSubVec(const std::string &arr);
std::vector<std::pair<std::string, std::vector<int>>> getCommonSubVec(const std::string& text, int minLen = 3, int maxLen = 20);
std::set<int> trustedDistances(const std::vector<std::pair<std::string, std::vector<int>>> &vec);

