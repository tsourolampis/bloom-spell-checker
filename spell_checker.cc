#include "spell_checker.h"


// Author: Charalampos E. Tsourakakis
// Space efficient spell checker using Bloom filters

BloomFilter::BloomFilter(int words){
    dict_file = "/usr/share/dict/words";
    words_= (words);
    p = 413158511;
    n = 8*words_;
    bitmask = new bool[n];
    num_hashes_ = ceil( log(2)*8 );
    // generate k universal hash functions
    for(int i = 0; i < num_hashes_; i++){
        coeffs.push_back( 1+ rand() % (p-1));   // uar from 1..p-1
        coeffs.push_back(  rand() % (p));      // uar from 0 to p-1
    }
}

BloomFilter::BloomFilter(int words, std::string dictionary_file){
    words_ = (words);
    p= 413158511;
    dict_file =  dictionary_file;
    n = 8*words;
    bitmask = new bool[n];
    num_hashes_ = ceil( log(2)*8 );
    for(int i = 0; i < num_hashes_; i++){
        coeffs.push_back( 1+ rand() % (p-1)); // uar from 1..p-1
        coeffs.push_back(  rand() % (p));     // uar from 0 to p-1
    }
}


// update the bloom filter
void BloomFilter::add_data(std::string str){
    unsigned long   h = hash(str);
    for(int i = 0; i < num_hashes_; i++){
        long a = coeffs[2*i];
        long b = coeffs[2*i+1];
        bitmask[ ((a*h+b)%p)%n ]= true;
    }
}


// if res is false, then x is mispelled
// if res is true, then probably is spelled right
bool BloomFilter::spell_check(std::string x){
    bool res = true;
    unsigned long  h = hash(x);
    for(int i = 0; i < num_hashes_; i++){
        long a = coeffs[2*i];
        long b = coeffs[2*i+1];
        if( bitmask[ ((a*h+b)%p)%n ] == false){
            res = false;
            break;
        }
    }
    return res;
}

//initiates the bloom filter from dict_file
void BloomFilter::init(){
    std::string word;
    std::ifstream filestream;
    filestream.open(dict_file);
    for(int i = 0;i<n;i++){
        bitmask[i] = false;
    }
    long stats = 0;
    while(filestream>>word){
        
        stats++;
        /*
         if(stats%10000 == 0){
         std::cout<<"Word "<<stats<<" was just read"<<std::endl;
         }*/
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        add_data(word);
    }
    std::cout<<"Bloom filter created, read "<<stats<< " words in total\n";
    filestream.close();
}


SpellChecker::SpellChecker(std::string doc){
			 document_file = doc;
}


SpellChecker::SpellChecker(){
			 document_file = "test.txt";
}



void SpellChecker::mispelled_words(BloomFilter* bf){
    std::vector<std::string> mispelled;
    std::string word;
    std::ifstream filestream;
    filestream.open(document_file);
    long counter = 0;
    while(filestream>>word){
        // lower case
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        word.erase(std::remove_if (word.begin (), word.end (), ispunct), word.end ());
        //std::cout<<"read word "<<word<<std::endl;
        if(!bf->spell_check(word)){
            mispelled.push_back(word);
            //std::cout<<"Word "<< word <<" is mispelled\n";
            counter++;
        }
    }
    
    int i=0;
    if( counter  > 0 ){
        std::cout<<"Mispelled words:\n";
        for (std::vector<std::string>::iterator it = mispelled.begin() ; it != mispelled.end(); ++it)
            std::cout <<(++i)<<". "<< *it<<std::endl; 
    }
    else
        std::cout<<"Excellent spelling!\n";
    
    
    
    filestream.close(); 
}


/* } */
