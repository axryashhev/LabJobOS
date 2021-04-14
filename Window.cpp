//
// Created by altai on 03.03.2021.
//

#include "Window.h"

Window::Window(LPCWSTR windowName, HINSTANCE hInst, LPCSTR menuName, int x, int y, int width, int height, UINT classStyle, DWORD windowStyle, HWND hParent)
{
    this->windowName = windowName;
    this->hInst = hInst;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->classStyle = classStyle;
    this->windowStyle = windowStyle;
    this->hParent = hParent;
}
