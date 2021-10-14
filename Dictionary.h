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

    //void setDictionary(const std::map<std::string, int> &aDictionary);

    void put(const std::string& word);

    void fillFromFile(const std::string& fileName);

    void sortByAlphabet();

    void sortByFrequency();
};


#endif //QT_TASK_DICTIONARY_H
