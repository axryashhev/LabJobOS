//
// Created by altai on 03.03.2021.
//

#ifndef LABJOB2_CMAINWINDOW_H
#define LABJOB2_CMAINWINDOW_H


#include "CObject.h"
#include "Window.h"
#include <Windows.h>

class CMainWindow : public CObject
{
public:
    CMainWindow(HINSTANCE hInst, LPCWSTR dlgResName, HWND hWndParent);
    CMainWindow(Window window);
    ~CMainWindow();
    LRESULT CALLBACK pRealWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void OnCreate();
};


#endif //LABJOB2_CMAINWINDOW_H
