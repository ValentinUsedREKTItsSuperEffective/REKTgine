#ifndef EXERCICES_H
#define EXERCICES_H

#include <string>
#include <iostream>

#define ARRAY_SIZE_SORT 20

using namespace std;

class Exercices{

    public:
        Exercices();
        ~Exercices();

        bool Palyndrome(string &word);
        void Tri();

    private:
        void printArray(int a[ARRAY_SIZE_SORT]);
};

#endif // EXERCICES_H
