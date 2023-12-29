// Dictionary.cpp

#include "Dictionary.h"
#include <algorithm>
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
#include <vector>
using namespace std;

void removeNonLetters(string& s);

// This class does the real work of the implementation.

//Beginning: Hash node class template
class HashNode {
public:
    HashNode(const int& k, const string& v):key(k), value(v), next(nullptr) {}
    int getKey() const{ return key; }
    string getValue() const{ return value; }
    void setValue(string value) {
        HashNode::value = value;
    }
    HashNode* getNext() const { return next; }
    void setNext(HashNode* next) {
        HashNode::next = next;
    }
private:
    int key;
    string value;
    HashNode* next;
};
//End: Hash node class template



//Begin: Hash map class template
class HashMap {
public:
    //Default constructor: 50000
    HashMap():maxBuckets(50000) {
        table = new HashNode* [50000]();
    }

    //Constructor
    HashMap(int maxBuckets):maxBuckets(maxBuckets) {
        table = new HashNode * [maxBuckets]();
    }

    //Destructor
    ~HashMap() {
        //destroy all buckets one by one
        for (int i = 0; i < maxBuckets; i++) {
            HashNode* entry = table[i];
            while (entry != nullptr) {
                HashNode* prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = nullptr;
        }
        //Destroy Array of pointers
        delete[] table;
    }
    
    //Return vector of approximate permutations
    void return_p(const string& value, vector<string>& p) {
        string sort_value = value;
        
        unsigned long hashValue = HashFunction(sort_value);
        HashNode* entry = table[hashValue];
        while (entry != nullptr) {
            p.push_back(entry->getValue());
            entry = entry->getNext();
        }
    }

    

    void put(const string& value) {
        string sort_value = value;
        removeNonLetters(sort_value);
        unsigned long hashValue = HashFunction(sort_value);
        HashNode* prev = nullptr;
        HashNode* entry = table[hashValue];

        while (entry != nullptr) {
            prev = entry;
            entry = entry->getNext();
        }
        entry = new HashNode(hashValue, value);
        if (prev == nullptr) {
            table[hashValue] = entry;
        }
        else {
            prev->setNext(entry);
        }
        
    }
    
private:
    int maxBuckets;
    unsigned int HashFunction(string s) const;
    //hash table
    HashNode** table;
    

};
//End: Hash map class template


//FNV-1 Variant
//Beginning: Hash Map Function
unsigned int HashMap::HashFunction(string s) const{
    string sorted_string = s;
    sort(sorted_string.begin(), sorted_string.end());
    unsigned int h = 2166136261U;
    for (size_t i = 0; i < sorted_string.size(); i++) {
        h += sorted_string[i];
        h *= 16777619;
    }
    h = h % maxBuckets;
    return h;
}
//End: Hash Map Function

//Beginning: DictionaryImpl
class DictionaryImpl
{
public:
    DictionaryImpl(int maxBuckets = 50000): m_words(maxBuckets), maxBuckets(maxBuckets) {}
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string));
private:
    int maxBuckets;
    HashMap m_words;
    vector<string> permutations;
};


void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    m_words.put(word);
}

void DictionaryImpl::lookup(string letters, void callback(string))
{
   if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;

    string permutation = letters;
    sort(permutation.begin(), permutation.end());
    vector<string> p_vector;
    m_words.return_p(permutation, p_vector);
    for (int i = 0; i < p_vector.size(); i++) {
        string temp = p_vector[i];
        sort(temp.begin(), temp.end());
        if (temp == permutation) {
            callback(p_vector[i]);
        }
    }
    
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}
