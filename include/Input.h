#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

class Input{
    public:
        int mouseX, mouseY;
        int mouseRX, mouseRY;
        bool isEnd;

        Input();
        ~Input();
        void updateEvent();
        bool getKey(const SDL_Scancode key) const;
        bool getMouseButton(const Uint8 button) const;
        bool inMovement() const;
        void showCursor(bool answer) const;
        void captureCursor(bool answer) const;

    private:
        SDL_Event event;
        bool keys[SDL_NUM_SCANCODES];
        bool mouseButton[8];
};

#endif // INPUT_H
