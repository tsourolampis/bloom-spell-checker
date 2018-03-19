#ifndef SPELL_CHECKER_H_
#define  SPELL_CHECKER_H_

#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>


// Author Charalampos Tsourakakis

unsigned long hash(std::string str){
    std::hash<std::string> hash_fn;
    return (unsigned long) hash_fn(str);
}


class BloomFilter{
private:
    std::string dict_file;
    int  words_;
    int n; // number of bits
    bool* bitmask; // bloom filter
    long p; // this is a large prime
    int  num_hashes_;
    std::vector<long> coeffs; // hash function coefficients
public:
    BloomFilter();
    BloomFilter(int words);
    BloomFilter(int words, std::string dictionary_file);
    void add_data(std::string w);
    bool spell_check(std::string x); // query string x
    void init(); //initiates the bloom filter from dict_file
};

class SpellChecker{
public:
    int counter;
    SpellChecker(std::string doc);
    SpellChecker();
    std::string document_file;
    void mispelled_words(BloomFilter *bf);
};

#endif
