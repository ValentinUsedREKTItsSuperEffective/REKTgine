#include "Exercices.h"

#include "Random.hpp"

#include <algorithm>

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

void Exercices::Tri(){
    Random random;
    int refArray[ARRAY_SIZE_SORT];
    for(int i = 0 ; i < ARRAY_SIZE_SORT; i++){
        refArray[i] = random.Range(50);
    }

    int buffer;
    int indexBuffer;

    // tri par selection
    int selection[ARRAY_SIZE_SORT];
    std::copy(std::begin(refArray), std::end(refArray), std::begin(selection));

    for (int j = 0; j < ARRAY_SIZE_SORT; j++){
        int max = -1;
        for(int i = 0; i < ARRAY_SIZE_SORT - j; i++){
            if (max < selection[i]){
                max = selection[i];
                indexBuffer = i;
            }
        }

        buffer = selection[ARRAY_SIZE_SORT - 1 - j];
        selection[ARRAY_SIZE_SORT- 1 - j] = selection[indexBuffer];
        selection[indexBuffer] = buffer;
    }

    printArray(refArray);
    printArray(selection);
}

void Exercices::printArray(int a[ARRAY_SIZE_SORT]){
    for(int i = 0; i < ARRAY_SIZE_SORT; i++){
       std::cout << a[i] << " ";
    }

    std::cout << std::endl << std::endl;
}
