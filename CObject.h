//
// Created by altai on 03.03.2021.
//

#ifndef LABJOB2_COBJECT_H
#define LABJOB2_COBJECT_H

#include "Window.h"
#include <functional>
#include "ActionWindow.h"

class CObject
{
public:
//    typedef
//        std::function<LRESULT(HWND h, UINT m, WPARAM w, LPARAM l)>
//        WindowProcFunction;

    CObject(HINSTANCE hInst, LPCWSTR dlgResName, HWND hWndParent);
    CObject(Window window);
    virtual ~CObject();
    void Show(int nCmdShow = SW_SHOW);
    HWND getHWnd() {
        return hWnd;
    }
    ActionWindow* getActionHandle() {
        return actionWindow;
    }
private:
    void init();
    virtual void OnCreate() = 0;
    void CreateDlg(HINSTANCE hInst, LPCWSTR dlgResName, HWND parent);
    static LRESULT CALLBACK pWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void createWindow(Window window);
//    WindowProcFunction procFunction;
protected:
    ActionWindow *actionWindow;
    virtual LRESULT CALLBACK pRealWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    WNDCLASSEX wc;
    HWND hWnd;
};


#endif //LABJOB2_COBJECT_H
