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

    //printArray(refArray);
    //printArray(selection);

    //tri a bulle
    int bulle[ARRAY_SIZE_SORT];
    std::copy(std::begin(refArray), std::end(refArray), std::begin(bulle));

    for (int j = 0; j < ARRAY_SIZE_SORT; j++){
        for(int i = 0; i < ARRAY_SIZE_SORT - j - 1; i++){
            if(bulle[i] > bulle[i + 1]){
                buffer = bulle[i + 1];
                bulle[i + 1] = bulle[i];
                bulle[i] = buffer;

                //printArray(bulle);
            }
        }
    }

    // tri rapide
    int rapide[ARRAY_SIZE_SORT];
    std::copy(std::begin(refArray), std::end(refArray), std::begin(rapide));
    printArray(rapide);
    triRapide(rapide, 0, ARRAY_SIZE_SORT-1);

    printArray(rapide);
}

void Exercices::printArray(int a[ARRAY_SIZE_SORT]){
    for(int i = 0; i < ARRAY_SIZE_SORT; i++){
       std::cout << a[i] << " ";
    }

    std::cout << std::endl << std::endl;
}

void Exercices::triRapide(int a[ARRAY_SIZE_SORT], int debut, int fin){
    if(fin - debut > 0){
        int pivot = partition(a, debut, fin);
        triRapide(a, debut, pivot - 1);
        triRapide(a, pivot + 1, fin);
    }
}

int Exercices::partition(int a[ARRAY_SIZE_SORT], int debut, int fin){
    // pivot = fin;
    int upperSize = 0;
    int buffer;
    for(int i = debut; i <= fin; i++){
        if(a[i] > a[fin]){
            upperSize++;
            //std::cout << "i: " << i << " ! UpperSize++ = " << upperSize << std::endl;
        } else {
            if(upperSize > 0){
                //std::cout << "i: " << i << " ! Swap " << a[i] << " at " << i << " with " << a[i - upperSize] << " at " << (i - upperSize) << std::endl;
                buffer = a[i];
                a[i] = a[i - upperSize];
                a[i - upperSize] = buffer;

                //printArray(a);
            }
        }
    }

    return fin - upperSize;
}
