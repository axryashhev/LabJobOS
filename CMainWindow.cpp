//
// Created by altai on 03.03.2021.
//

#include "CMainWindow.h"

CMainWindow::CMainWindow(HINSTANCE hInst, LPCWSTR dlgResName, HWND hWndParent) : CObject(hInst, dlgResName, hWndParent)
{
    //    OnCreate();
}

CMainWindow::CMainWindow(Window window) : CObject(window) {
    //    OnCreate();
}

CMainWindow::~CMainWindow()
{
}

LRESULT CMainWindow::pRealWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
        switch (wParam)
        {
        case IDOK:
            MessageBoxW(hWnd, L"Button is pushed!", L"OK", MB_OK);
            break;
        case IDCANCEL:
            MessageBoxW(hWnd, L"Button is pushed!", L"Cancel", MB_OK);
            break;
        }
        break;
    }
    return CObject::pRealWndProc(hWnd, uMsg, wParam, lParam);
}

void CMainWindow::OnCreate()
{
    //    MessageBoxW(nullptr, L"OnCreate called!", L"Message", MB_OK);
}
