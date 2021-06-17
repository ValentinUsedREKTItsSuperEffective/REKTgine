#ifndef SCREEN_H
#define SCREEN_H


class Screen
{
    public:
        Screen(unsigned int, unsigned int);
        virtual ~Screen();

        static unsigned int width;
        static unsigned int height;
};

#endif // SCREEN_H
