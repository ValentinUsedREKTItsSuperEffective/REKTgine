#include "Exercices.h"

Exercices::Exercices(){}

Exercices::~Exercices(){}

bool Exercices::Palyndrome(string &word){
    for(int i = 0; i < word.size(); i++){
        if(word[i] != word[word.size() - 1 - i]){
            std::cout << "Not a palyndrome !" << std::endl;
            return false;
        }
    }

    std::cout << "Palyndrome !" << std::endl;
    return true;
}
