#ifndef EXERCICES_H
#define EXERCICES_H

#include <string>
#include <iostream>
#include <vector>
#include <map>

#define ARRAY_SIZE_SORT 20

using namespace std;

class Exercices{

    public:
        Exercices();
        ~Exercices();

        bool Palyndrome(string &word);
        void Tri();
        bool Bananagram(vector<char> bag, string word);

    private:
        void printArray(int a[ARRAY_SIZE_SORT]);
        void triRapide(int a[ARRAY_SIZE_SORT], int debut, int fin);
        int partition(int a[ARRAY_SIZE_SORT], int debut, int fin);
};

#endif // EXERCICES_H
