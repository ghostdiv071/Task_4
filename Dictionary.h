#ifndef QT_TASK_DICTIONARY_H
#define QT_TASK_DICTIONARY_H


#include <map>

class Dictionary {
private:
    std::map<std::string, int> dictionary;

public:
    Dictionary();

    ~Dictionary();

    std::map<std::string, int> &getDictionary();

    void put(const std::string& word);

    void fillFromFile(const std::string& fileName);

    std::vector<std::pair<std::string, int>> sortByAlphabet();

    std::vector<std::pair<std::string, int>> sortByFrequency();
};


#endif //QT_TASK_DICTIONARY_H
