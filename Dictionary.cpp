#include <fstream>
#include <vector>
#include "Dictionary.h"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cctype>

Dictionary::Dictionary() {
    fillFromFile(R"(C:\Users\1\CLionProjects\QT_task_4\dictionary.txt)");
}

Dictionary::~Dictionary() = default;

std::map<std::string, int> &Dictionary::getDictionary() {
    return dictionary;
}

void Dictionary::put(const std::string &word) {
    auto it = dictionary.find(word);
    if (it == dictionary.end()) {
        dictionary.insert({word, 1});
    } else {
        it->second++;
    }
}

void Dictionary::fillFromFile(const std::string &fileName) {
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

        std::transform(t.begin(), t.end(), t.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        put(t);
    }
}

std::vector<std::pair<std::string, int>> Dictionary::sortByAlphabet() {
    auto cmp = [](std::pair<std::string, int> const &a, std::pair<std::string, int> const &b) {
        return a.first < b.first;
    };
    std::vector<std::pair<std::string, int>> pairs;
    pairs.reserve(dictionary.size());
    for (const auto &pair: dictionary) {
        pairs.emplace_back(pair);
    }
    std::sort(pairs.begin(), pairs.end(), cmp);
    return pairs;
}

std::vector<std::pair<std::string, int>> Dictionary::sortByFrequency() {
    auto cmp = [](std::pair<std::string, int> const &a, std::pair<std::string, int> const &b) {
        return a.second > b.second;
    };
    std::vector<std::pair<std::string, int>> pairs;
    pairs.reserve(dictionary.size());
    for (const auto &pair: dictionary) {
        pairs.emplace_back(pair);
    }
    std::sort(pairs.begin(), pairs.end(), cmp);
    return pairs;
}
