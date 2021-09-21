#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <time.h>

class Random
{
    public:
        Random();
        virtual ~Random();

        void SetSeed(unsigned int seed);
        int Range(int max);

    private:
        unsigned int seed;
};

#endif // RANDOM_H
