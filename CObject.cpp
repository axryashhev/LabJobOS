//
// Created by altai on 03.03.2021.
//

#include "CObject.h"

void CObject::Show(int nCmdShow)
{
    ShowWindow(hWnd, nCmdShow);
}

CObject::CObject(HINSTANCE hInst, LPCWSTR dlgResName, HWND hWndParent)
{
    this->CreateDlg(hInst, dlgResName, hWndParent);
}

CObject::~CObject()
{
    delete actionWindow;
}

void CObject::CreateDlg(HINSTANCE hInst, LPCWSTR dlgResName, HWND parent)
{
    hWnd = CreateDialogW(hInst, dlgResName, parent, (DLGPROC)pWndProc);
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
}

LRESULT CObject::pWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CObject* cObject = (CObject*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    if (cObject) {
        return cObject->pRealWndProc(hWnd, uMsg, wParam, lParam);
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CObject::pRealWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Event event(hWnd, uMsg, wParam, lParam);
    
    switch (uMsg)
    {
        case WM_PAINT:
            actionWindow->onPaint(event);
            break;
        case WM_LBUTTONDOWN:
            actionWindow->onLeftButtonMouse(event);
            break;
        case WM_RBUTTONDOWN:
            actionWindow->onRightButtonMouse(event);
            break;
            case WM_KEYDOWN:
            actionWindow->onActionKey(event);
            break;
        case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

CObject::CObject(Window window) {
    this->init();
    this->createWindow(window);
}

void CObject::createWindow(Window window) {
    TCHAR szClassName[] = L"CWndClass";
    wc.cbSize = sizeof(wc);
    wc.style = window.classStyle;
    wc.lpfnWndProc = pWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(CObject*);
    wc.hInstance = window.hInst;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = (LPCWSTR) window.menuName;
    wc.lpszClassName = szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        WCHAR msg[100] = L"Cannot register class: ";
        wcscat_s(msg, szClassName);
        MessageBox(NULL, L"Cannot register class: ", L"Error", MB_OK);
        return;
    }
    else {

        hWnd = CreateWindowW(szClassName, window.windowName, window.windowStyle,
            window.x, window.y, window.width, window.height, window.hParent, (HMENU)NULL, window.hInst, NULL);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
    }

    //    auto fgd = reinterpret_cast<LONG_PTR>(this);

    if (!hWnd) {
        TCHAR text[100] = L"Cannot create window: ";
        wcscat_s(text, window.windowName);
        MessageBox(NULL, text, L"Error", MB_OK);
        return;
    }
}

void CObject::init() {
    actionWindow = new ActionWindow();
}
