//
// Created by altai on 06.03.2021.
//

#ifndef LABJOB2_EVENT_H
#define LABJOB2_EVENT_H

class Event {
private: HWND hWnd;
private: UINT uMsg;
private: WPARAM wParam;
private: LPARAM lParam;

public: Event(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        this->hWnd = hWnd;
        this->uMsg = uMsg;
        this->wParam = wParam;
        this->lParam = lParam;
    }

public: HWND gethWnd() {
        return hWnd;
    }

public: void sethWnd(HWND hWnd) {
        this->hWnd = hWnd;
    }

public: UINT getuMsg() {
        return uMsg;
    }

public: void setuMsg(UINT uMsg) {
        this->uMsg = uMsg;
    }

public: WPARAM getwParam() {
        return wParam;
    }

public: void setwParam(WPARAM wParam) {
        this->wParam = wParam;
    }

public: LPARAM getlParam() {
        return lParam;
    }

public: void setlParam(LPARAM lParam) {
        this->lParam = lParam;
    }
};

#endif //LABJOB2_EVENT_H
