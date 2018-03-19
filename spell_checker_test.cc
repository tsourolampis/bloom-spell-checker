#include "spell_checker.h"


// Author: Charalampos E. Tsourakakis

int main(int argc, char** argv)
{
    BloomFilter* bf = new BloomFilter(235886);
    bf->init();
    SpellChecker *sc = new SpellChecker(std::string(argv[1]));
    sc->mispelled_words(bf);
    return 0;
}


