#pragma once

class Point {
private: double x, y, R = 0;

    public: Point(double x, double y) {
        this->x = x;
        this->y = y;
    }

	public: Point(double x, double y, double R) {
		this->x = x;
		this->y = y;
		this->R = R;
	}

    public: Point() {
        this->x = 0;
        this->y = 0;
    }

    public: double getX() {
        return x;
    }

    public: void setX(double x) {
        this->x = x;
    }

    public: double getY() {
        return y;
    }

    public: void setY(double y) {
        this->y = y;
    }

    public: double getR() {
        return R;
    }

    public: void setR(double R) {
        this->R = R;
    }
};