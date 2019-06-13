#include "Input.h"

Input::Input() : mouseX(0), mouseY(0), mouseRX(0), mouseRY(0), isEnd(false){
    for(int i = 0; i < SDL_NUM_SCANCODES; i++)
        keys[i] = false;

    for(int i = 0; i < 8; i++)
        mouseButton[i] = false;
}

Input::~Input(){}

void Input::updateEvent(){
    mouseRX = 0;
    mouseRY = 0;

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
                keys[event.key.keysym.scancode] = true;
                break;

            case SDL_KEYUP:
                keys[event.key.keysym.scancode] = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mouseButton[event.button.button] = true;
                break;

            case SDL_MOUSEBUTTONUP:
                mouseButton[event.button.button] = false;
                break;

            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;

                mouseRX = event.motion.xrel;
                mouseRY = event.motion.yrel;
                break;

            case SDL_WINDOWEVENT_CLOSE:
                isEnd = true;
                break;
        }
    }
}

bool Input::getKey(const SDL_Scancode key) const{
    return keys[key];
}

bool Input::getMouseButton(const Uint8 button) const{
    return mouseButton[button];
}

bool Input::inMovement() const{
    return (mouseRX != 0 || mouseRY !=0);
}

void Input::showCursor(bool answer) const{
    answer ? SDL_ShowCursor(SDL_ENABLE) : SDL_ShowCursor(SDL_DISABLE);
}

void Input::captureCursor(bool answer) const{
    answer ? SDL_SetRelativeMouseMode(SDL_TRUE) : SDL_SetRelativeMouseMode(SDL_FALSE);
}
