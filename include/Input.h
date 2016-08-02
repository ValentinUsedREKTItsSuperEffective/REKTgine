#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

class Input
{
    public:
        Input();
        ~Input();
        void updateEvent();
        bool isEnd();
        bool getKey(const SDL_Scancode key) const;
        bool getMouseButton(const Uint8 button) const;
        bool inMovement() const;
        int getX() const;
        int getY() const;
        int getRX() const;
        int getRY() const;
        void showCursor(bool answer) const;
        void captureCursor(bool answer) const;

    private:
        SDL_Event _event;
        bool _keys[SDL_NUM_SCANCODES];
        bool _mouseButton[8];
        int _mouseX, _mouseY;
        int _mouseRX, _mouseRY;
        bool _end;
};

#endif // INPUT_H
