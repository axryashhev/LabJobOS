//
// Created by altai on 06.03.2021.
//

#ifndef LABJOB2_ACTIONWINDOW_H
#define LABJOB2_ACTIONWINDOW_H

#include "Event.h";
#include <functional>

class ActionWindow {
    private: std::function<void(Event)> paintListener = [](Event event){};
    private: std::function<void(Event)> leftButtonListener = [](Event event){};
    private: std::function<void(Event)> rightButtonListener = [](Event event){};
    private: std::function<void(Event)> actionKey = [](Event event){};

    public: void setOnPaintListener(std::function<void(Event)> paintListener) {
        this->paintListener = paintListener;
    }

    public: auto onPaint(Event event) {
        return paintListener(event);
    }

    public: void setOnLeftButtonMouseListener(std::function<void(Event)> leftButtonListener) {
        this->leftButtonListener = leftButtonListener;
    }

    public: auto onLeftButtonMouse(Event event) {
        return leftButtonListener(event);
    }

    public: void setOnRightButtonMouseListener(std::function<void(Event)> rightButtonListener) {
        this->rightButtonListener = rightButtonListener;
    }

    public: auto onRightButtonMouse(Event event) {
        return rightButtonListener(event);
    }

    public: void setOnActionKeyListener(std::function<void(Event)> actionKey) {
        this->actionKey = actionKey;
    }

    public: auto onActionKey(Event event) {
        return actionKey(event);
    }
};

#endif //LABJOB2_ACTIONWINDOW_H
