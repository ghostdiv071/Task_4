#include <fstream>
#include <vector>
#include "Dictionary.h"
#include <algorithm>
#include <sstream>
#include <iostream>

Dictionary::Dictionary() {
      fillFromFile(R"(C:\Users\1\CLionProjects\QT_task_4\dictionary.txt)");
}

Dictionary::~Dictionary() = default;

std::map<std::string, int> &Dictionary::getDictionary() {
    return dictionary;
}

//void Dictionary::setDictionary(const std::map<std::string, int> &aDictionary) {
//    Dictionary::dictionary = aDictionary;
//}

void Dictionary::put(const std::string& word) {
    auto it = dictionary.find(word);
    if (it == dictionary.end()) {
        dictionary.insert({word, 1});
    } else {
        it->second++;
    }
}

void Dictionary::fillFromFile(const std::string& fileName) {
    //dictionary.clear();

    std::string res;
    std::string line;

    std::ifstream in(fileName);
    if (in.is_open()) {
        while (getline(in, line)) {
            res += line + ' ';
        }
    }
    in.close();

    std::vector<char> symbols = {'.', ',', '?', '!', ':', ';', '-'};
    for (char &re: res) {
        if (std::find(symbols.begin(), symbols.end(), re) != symbols.end())
            re = ' ';
    }

    std::string t;
    std::istringstream ss(res);
    std::vector<std::string> v;
    while (ss >> t) {
        std::cout << t;
        put(t);
    }
}

void Dictionary::sortByAlphabet() {

}

void Dictionary::sortByFrequency() {

}
