#include "Screen.hpp"

unsigned int Screen::width = 0;
unsigned int Screen::height = 0;

Screen::Screen(unsigned int width, unsigned int height){
    Screen::width = width;
    Screen::height = height;
}

Screen::~Screen(){}
