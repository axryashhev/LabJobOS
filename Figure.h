#pragma once

#include <vector>
#include <functional>
#include "Point.h"
typedef enum { NORMAL, VERTICAL, HORIZONTAL, BOTH } Mode;
typedef enum { STRIHT, REVERSE } ModeRotation;

class Figure
{
	typedef std::function<std::vector<Point>(Point, Mode, float)> CreateFunction;

	private: Mode mode = NORMAL;
	private: ModeRotation modeRotation = STRIHT;
    private: std::vector<Point> pointList { Point(0,0), Point(0, 0), Point(0,0), Point(0,0)};
    private: CreateFunction createListPoint = [&](Point point, Mode mode, float angle) ->std::vector<Point> { return pointList; };
    private: Point point;
    private: float saveAngle  = 0;
	private: float angle = 3.14/6;


    public: std::vector<Point> getPointList() {
        return pointList;
    }

    Figure(CreateFunction createListPoint) {
        this->createListPoint = createListPoint;
    }

    Figure() {
        this->createListPoint = [&](Point point, Mode mode, float angle) ->std::vector<Point> { return pointList; };
    }

    public: void setPointList(std::vector<Point> pointList) {
        this->pointList = pointList;
    }

    public: void create(Point point) {
        this->point = point;
        this->setPointList(createListPoint(point, mode, angle));
    }

	public: void setActionListPoint(CreateFunction createListPoint) {
		this->createListPoint = createListPoint;
	}

    public: void restore() {
        this->setPointList(createListPoint(this->point, this->mode, this->angle));
    }

	public: void setPointCenter(Point point) {
		this->point = point;
	}

	public: Point getPointCenter() {
		return point;
	}

	public: void setMode(Mode mode) {
		this->mode = mode;
	}

	public: Mode getMode() {
		return this->mode;
	}

	public: void setModeRotation(ModeRotation modeRotation) {
		this->modeRotation = modeRotation;
	}

	public: ModeRotation getModeRotation() {
		return this->modeRotation;
	}

	public: void setSaveAngle(float angle) {
		this->saveAngle += angle;
	}

public: float getSaveAngle() {
        return this->saveAngle;
	}

	public: float getAngle() {
		return this->angle;
	}
};

