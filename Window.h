//
// Created by altai on 03.03.2021.
//

#ifndef LABJOB2_WINDOW_H
#define LABJOB2_WINDOW_H

#include <Windows.h>

class Window {
public:
    LPCWSTR windowName;
    HINSTANCE hInst;
    LPCSTR menuName;
    int x; int y;
    int width;
    int height;
    UINT classStyle;
    DWORD windowStyle;
    HWND hParent;

    Window(LPCWSTR windowName, HINSTANCE hInst,
        LPCSTR menuName = NULL,
        int x = CW_USEDEFAULT, int y = 0,
        int width = CW_USEDEFAULT, int height = 0,
        UINT classStyle = CS_HREDRAW | CS_VREDRAW,
        DWORD windowStyle = WS_OVERLAPPEDWINDOW,
        HWND hParent = NULL);
};


#endif //LABJOB2_WINDOW_H
