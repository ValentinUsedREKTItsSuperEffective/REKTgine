#include "Input.h"

Input::Input() : _mouseX(0), _mouseY(0), _mouseRX(0), _mouseRY(0), _end(false)
{
    for(int i = 0; i < SDL_NUM_SCANCODES; i++)
        _keys[i] = false;

    for(int i = 0; i < 8; i++)
        _mouseButton[i] = false;
}

Input::~Input()
{
    //dtor
}

void Input::updateEvent(){

    _mouseRX = 0;
    _mouseRY = 0;

    while(SDL_PollEvent(&_event)){

        switch(_event.type){
            case SDL_KEYDOWN:
                _keys[_event.key.keysym.scancode] = true;
            break;

            case SDL_KEYUP:
                _keys[_event.key.keysym.scancode] = false;
            break;

            case SDL_MOUSEBUTTONDOWN:
                _mouseButton[_event.button.button] = true;
            break;

            case SDL_MOUSEBUTTONUP:
                _mouseButton[_event.button.button] = false;
            break;

            case SDL_MOUSEMOTION:
                _mouseX = _event.motion.x;
                _mouseY = _event.motion.y;

                _mouseRX = _event.motion.xrel;
                _mouseRY = _event.motion.yrel;
            break;

            case SDL_WINDOWEVENT_CLOSE:
                _end = true;
            break;
        }
    }
}

bool Input::isEnd(){
    return _end;
}

bool Input::getKey(const SDL_Scancode key) const{
    return _keys[key];
}

bool Input::getMouseButton(const Uint8 button) const{
    return _mouseButton[button];
}

bool Input::inMovement() const{
    return (_mouseRX != 0 || _mouseRY !=0);
}

int Input::getX() const{
    return _mouseX;
}

int Input::getY() const{
    return _mouseY;
}

int Input::getRX() const{
    return _mouseRX;
}

int Input::getRY() const{
    return _mouseRY;
}

void Input::showCursor(bool answer) const{
    answer ? SDL_ShowCursor(SDL_ENABLE) : SDL_ShowCursor(SDL_DISABLE);
}

void Input::captureCursor(bool answer) const{
    answer ? SDL_SetRelativeMouseMode(SDL_TRUE) : SDL_SetRelativeMouseMode(SDL_FALSE);
}
