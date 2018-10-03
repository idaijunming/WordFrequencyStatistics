#include<iostream>
#include<iomanip>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

using namespace std;

struct cmp_str
{
    bool operator()(char *a, char *b)const
    {
        return std::strcmp(a, b) < 0;
    }
};

inline void StringCopy(map<char*, long, cmp_str>& wordMap, pair< map<char*, long>::iterator, bool>& ret, char*& target, char*& val, int& start, int& finish)
{
    if (finish - start > 0)
    {
        if (target != nullptr)
            delete target;
        target = new char[finish - start + 1];
        strcpy(target, val + start);
        ret = wordMap.insert(make_pair(target, 1));
        if (!ret.second)
        {
            wordMap[target] += 1;
        }
        else
        {
            target = nullptr;
        }

    }
    start = finish + 1;
}

inline void handleWords(map<char*, long, cmp_str>& wordMap, pair< map<char*, long>::iterator, bool>& ret, char*& trueWord, char*& word)
{
    int index = 0;
    for (int i = 0; i < 50; i++)
    {
        if (word[i] == '\0')
        {
            StringCopy(wordMap, ret, trueWord, word, index, i);
            break;
        }
        else
        {
            if (word[i] < 65 || (word[i] > 90 && word[i] < 97) || word[i] >122)
            {
                word[i] = '\0';
                StringCopy(wordMap, ret, trueWord, word, index, i);
            }
            else if (word[i] > 64 && word[i] < 91)
            {
                word[i] += 32;
            }
        }
    }
}

bool cmp_by_value(const pair<char*, long>& v1, const pair<char*, long>& v2)
{
    if (v1.second == v2.second)
        return v1.first < v2.first;
    else
        return v1.second > v2.second;
}

int main()
{
    //_CrtSetBreakAlloc(259);
    map<char*, long, cmp_str> wordMap;
    pair< map<char*, long>::iterator, bool> ret;
    std::ifstream file;
    file.open("Gone_with_the_wind.txt");
    char* word = new char[50];
    char* trueWord = nullptr;
    while (!file.eof())
    {
        if (file.getline(word, 50, ' ').good())
            handleWords(wordMap, ret, trueWord, word);
        else
        {
            handleWords(wordMap, ret, trueWord, word);
            break;
        }
    }
    if (trueWord != nullptr)
        delete trueWord;
    if (word != nullptr)
        delete word;
    file.close();

    vector<pair<char*, long> >wordArray(wordMap.begin(), wordMap.end());
    sort(wordArray.begin(), wordArray.end(), cmp_by_value);
    int len = std::min(int(wordArray.size()), 10);
    int size = wordArray.size();
    for (int i = 0; i < size; i++)
    {
        cout.width(15);
        cout.fill(' ');
        cout.setf(ios::left);
        if (i < len)
        {
            cout << wordArray[i].first << wordArray[i].second << endl;
        }
        delete wordArray[i].first;
        wordArray[i].first = nullptr;
    }
    wordArray.clear();
    wordMap.clear();
    return 0;
    //_CrtDumpMemoryLeaks();
}