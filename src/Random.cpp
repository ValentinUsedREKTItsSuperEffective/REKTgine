#include "Random.hpp"

Random::Random() : seed(time(NULL)){
    srand(seed);
}

Random::~Random(){}

void Random::SetSeed(unsigned int seed){
    this->seed = seed;
    srand(seed);
}

int Random::Range(int max){
    return rand() % max;
}
