#include <windows.h>
// #include "CWnd.h"
// #include "Models/Triangle.h"
// #include "Controller/DelegateController.h"
#include "Window.h"
#include "CMainWindow.h"
#include "Point.h"
#include "Figure.h"
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
// #include <vector>
// #include <memory>
#define n 8 // макcимальное количество фигур
#define pi 3.14

// namespace SignsOfVisible {
//    boolean V = true, V_1 = false, V_2 = false;
//    boolean m = true;
// }

namespace figure {
	int x[n], y[n], R[n], h[n], g[n];
	int N = 0, m, y_0;
}

using namespace figure;

template<typename T>
using List = std::vector<T>;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

List<Point> getRotateFigure(List<Point> pointList, double angle, Point center, boolean axis, ModeRotation mode);
Mode mirroring(Mode mode, boolean axis);
Point getNewCenter(Point point, Point figure, boolean axis);
ModeRotation getUpdateModeRotation(Mode mode);
void debugList(List<Point> listPoint);


//====================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int
    nCmdShow)
{
    MSG msg;
    auto at = pi/6;
	boolean axis = false;

    auto createTriangle = [&](Point point, Mode mode, float angle)->List<Point> {
        List<Point> listPoint;
//        listPoint.clear();
		switch (mode)
		{
			case NORMAL:
				listPoint.push_back(Point(point.getX() - point.getR()*cos(angle), point.getY() + point.getR()*sin(angle)));
				listPoint.push_back(Point(point.getX() + point.getR()*cos(angle), point.getY() + point.getR()*sin(angle)));
				listPoint.push_back(Point(point.getX(), point.getY() - point.getR()));
				break;
			case HORIZONTAL:
				listPoint.push_back(Point(point.getX() - point.getR()*cos(angle), point.getY() - point.getR()*sin(angle)));
				listPoint.push_back(Point(point.getX() + point.getR()*cos(angle), point.getY() - point.getR()*sin(angle)));
				listPoint.push_back(Point(point.getX(), point.getY() + point.getR()));
				break;
			case VERTICAL:
				listPoint.push_back(Point(point.getX() + point.getR()*cos(angle), point.getY() + point.getR()*sin(angle)));
				listPoint.push_back(Point(point.getX() - point.getR()*cos(angle), point.getY() + point.getR()*sin(angle)));
				listPoint.push_back(Point(point.getX(), point.getY() - point.getR()));
				break;
			case BOTH:
				listPoint.push_back(Point(point.getX() + (point.getR() * -1)*cos(angle), point.getY() + (point.getR() * -1)*sin(angle)));
				listPoint.push_back(Point(point.getX() - (point.getR() * -1)*cos(angle), point.getY() + (point.getR() * -1)*sin(angle)));
				listPoint.push_back(Point(point.getX(), point.getY() - (point.getR() * -1)));
				break;
		}
        
        return listPoint;
    };

    auto createRhombus = [&](Point point, Mode mode, float angle)->List<Point> {
        List<Point> listPoint;
//        listPoint.clear();
        listPoint.push_back(Point(point.getX(), point.getY()-point.getR()));
        listPoint.push_back(Point(point.getX()-point.getR(), point.getY()));
        listPoint.push_back(Point(point.getX(), point.getY()+point.getR()));
        listPoint.push_back(Point(point.getX()+point.getR(), point.getY()));
        return listPoint;
    };

    auto createSquare = [&](Point point, Mode mode, float angle)->List<Point> {
        List<Point> listPoint;
//        listPoint.clear();
        listPoint.push_back(Point(point.getX()-point.getR(), point.getY()-point.getR()));
        listPoint.push_back(Point(point.getX()-point.getR(), point.getY()+point.getR()));
        listPoint.push_back(Point(point.getX()+point.getR(), point.getY()+point.getR()));
        listPoint.push_back(Point(point.getX()+point.getR(), point.getY()-point.getR()));
        return listPoint;
    };

    List<Figure> listFigure(n);

    // PASSIVE
    HPEN p1 = CreatePen(PS_SOLID, 3, RGB(255, 128, 255));
    HPEN p2 = CreatePen(PS_SOLID, 1, RGB(255, 0, 128));
    HPEN p3 = CreatePen(PS_SOLID, 2, RGB(162, 255, 121));

    // ACTIVE
    HPEN p1_1 = CreatePen(PS_SOLID, 6, RGB(113, 227, 255));
    HPEN p2_1 = CreatePen(PS_SOLID, 6, RGB(250, 122, 113));
    HPEN p3_1 = CreatePen(PS_SOLID, 6, RGB(126, 255, 112));

    HDC hDc;
    PAINTSTRUCT ps;
    RECT rect;

    Window window(L"Laboratory work", hInstance);
    window.height = 500;
    window.width = 400;

    CMainWindow* mainWnd = new CMainWindow(window);

    mainWnd->getActionHandle()->setOnPaintListener([&](Event event) {
        hDc = BeginPaint(event.gethWnd(), &ps);

        //рисуем до n фигур
        for (int i=0; i<n; i++) {
            List<Point> listPoints = listFigure[i].getPointList();
            //треугольник
            if (g[i]==0) { //если нажали F1
                //проверка фигуры на активность
            if (h[i]==1) {
                SelectObject(hDc, p1);
            }
            else
                SelectObject(hDc, p1_1);

//                MoveToEx(hDc,x[i],y[i]-R[i],NULL);
//                LineTo(hDc,x[i]-R[i]*cos(at),y[i]);
//
//                MoveToEx(hDc,x[i]-R[i]*cos(at),y[i],NULL);
//                LineTo(hDc,x[i]+R[i]*cos(at),y[i]);
//
//                MoveToEx(hDc,x[i]+R[i]*cos(at),y[i],NULL);
//                LineTo(hDc,x[i],y[i]-R[i]);

                MoveToEx(hDc,listPoints[2].getX(),listPoints[2].getY(),NULL);
                LineTo(hDc,listPoints[0].getX(),listPoints[0].getY());

                MoveToEx(hDc,listPoints[0].getX(),listPoints[0].getY(),NULL);
                LineTo(hDc,listPoints[1].getX(),listPoints[1].getY());

                MoveToEx(hDc,listPoints[1].getX(),listPoints[1].getY(),NULL);
                LineTo(hDc,listPoints[2].getX(),listPoints[2].getY());
            }

            //ромб
             if (g[i]==1) {//если нажали F2
                //проверка фигуры на активность
            if (h[i]==1) {
                SelectObject(hDc, p2);
            }
            else
                SelectObject(hDc, p2_1);

                MoveToEx(hDc,listPoints[0].getX(),listPoints[0].getY(),NULL);
                LineTo(hDc,listPoints[1].getX(),listPoints[1].getY());

                MoveToEx(hDc,listPoints[1].getX(),listPoints[1].getY(),NULL);
                LineTo(hDc,listPoints[2].getX(),listPoints[2].getY());

                MoveToEx(hDc,listPoints[2].getX(),listPoints[2].getY(),NULL);
                LineTo(hDc,listPoints[3].getX(),listPoints[3].getY());

                MoveToEx(hDc,listPoints[3].getX(),listPoints[3].getY(),NULL);
                LineTo(hDc,listPoints[0].getX(),listPoints[0].getY());
            }

            //квадрат
            if (g[i]==2) {  //если нажали F3
                //проверка фигуры на активность
                if (h[i]==1) {
                    SelectObject(hDc, p3);
                }
                else
                    SelectObject(hDc, p3_1);

                MoveToEx(hDc,listPoints[0].getX(),listPoints[0].getY(),NULL);
                LineTo(hDc,listPoints[1].getX(),listPoints[1].getY());

                MoveToEx(hDc,listPoints[1].getX(),listPoints[1].getY(),NULL);
                LineTo(hDc,listPoints[2].getX(),listPoints[2].getY());

                MoveToEx(hDc,listPoints[2].getX(),listPoints[2].getY(),NULL);
                LineTo(hDc,listPoints[3].getX(),listPoints[3].getY());

                MoveToEx(hDc,listPoints[3].getX(),listPoints[3].getY(),NULL);
                LineTo(hDc,listPoints[0].getX(),listPoints[0].getY());
            }
        }

        EndPaint(event.gethWnd(),&ps);
    });

    mainWnd->getActionHandle()->setOnLeftButtonMouseListener([&](Event event) {
        //перемещение фигуры
        x[m] = LOWORD(event.getlParam()); //смещение по координате x 
        y[m] = HIWORD(event.getlParam()); //смещение по координате y

        // List<Point> pointList = listFigure[m].getPointList();
		listFigure[m].setModeRotation(listFigure[m].getModeRotation());
		listFigure[m].setPointCenter(Point(x[m], y[m], R[m]));
		listFigure[m].restore();
        listFigure[m].setPointList(getRotateFigure(listFigure[m].getPointList(),
        listFigure[m].getSaveAngle(), listFigure[m].getPointCenter(), axis, listFigure[m].getModeRotation()));
        GetClientRect(event.gethWnd(), &rect);
        InvalidateRect(event.gethWnd(), &rect, -1);
        UpdateWindow(event.gethWnd());
    });

	mainWnd->getActionHandle()->setOnRightButtonMouseListener([&](Event event) {
		//отображение фигуры относительно горизонтальной оси
		x[m] = LOWORD(event.getlParam()); //смещение по координате x 
		y[m] = HIWORD(event.getlParam()); //смещение по координате y

		//y[m] = 2 * y_0 - y[m]; //изменение координаты y для отображения относительно горизонтальной оси
		//R[m] = -R[m]; //изменение радиуса на отрицательный

		// List<Point> pointList = listFigure[m].getPointList();
		// Point point(x[m], y[m]);
		// point.setR(R[m]);
		// listFigure[m].create(point);
		auto localRotation = [](ModeRotation modeRotation) -> ModeRotation {
			if (modeRotation == STRIHT) {
				return REVERSE;
			}
			else {
				return STRIHT;
			}
		};
		listFigure[m].setModeRotation(localRotation(listFigure[m].getModeRotation()));
		listFigure[m].setPointCenter(getNewCenter(Point(x[m], y[m]), listFigure[m].getPointCenter(), axis));
		listFigure[m].setMode(mirroring(listFigure[m].getMode(), axis));
		listFigure[m].restore();
		// debugList(listFigure[m].getPointList());
        listFigure[m].setPointList(getRotateFigure(listFigure[m].getPointList(),
                                                   listFigure[m].getSaveAngle(), listFigure[m].getPointCenter(), axis, listFigure[m].getModeRotation()));
        // MessageBox(event.gethWnd(), std::to_wstring(listFigure[m].getSaveAngle()).c_str(), L"", MB_OK);
        GetClientRect(event.gethWnd(), &rect);
        InvalidateRect(event.gethWnd(), &rect, -1);
        UpdateWindow(event.gethWnd());
    });

    mainWnd->getActionHandle()->setOnActionKeyListener([&](Event event) {
		if (N < n) { //условие того, что фигур будет не больше заданного
		//при нажатии клавиши F1
			if (event.getwParam() == VK_F1) { //создрание треугольника
				h[m] = 1; //фигура активна
				m = N; //номер фигуры в массиве становится N
				N++; //количество фигур увеличено на 1
				x[m] = 100; //координаты x0
				y[m] = 100; //координаты y0
				R[m] = 50; //радиус
				g[m] = 0; //тип фигуры треугольник
				h[m] = 2; //фигура не активна

				Point point(x[m], y[m]);
				point.setR(50);
				Figure triangle(createTriangle);
				triangle.create(point);
				listFigure[m] = triangle;

				GetClientRect(event.gethWnd(), &rect);
				InvalidateRect(event.gethWnd(), &rect, -1);
				UpdateWindow(event.gethWnd());
			}

			//при нажатии клавиши F2
			if (event.getwParam() == VK_F2) {
				h[m] = 1; //фигура активна
				m = N; //номер фигуры в массиве становится N
				N++; //количество фигур увеличено на 1
				x[m] = 100; //координаты x0
				y[m] = 100; //координаты y0
				R[m] = 50; //радиус
				g[m] = 1; //тип фигуры ромб
				h[m] = 2; //фигура не активна

                Point point(x[m], y[m]);
                point.setR(50);
                Figure rhombus(createRhombus);
                rhombus.create(point);
                listFigure[m] = rhombus;

                GetClientRect(event.gethWnd(), &rect);
				InvalidateRect(event.gethWnd(), &rect, -1);
				UpdateWindow(event.gethWnd());
			}

			//при нажатии клавиши F3
			if (event.getwParam() == VK_F3) {
				h[m] = 1; //фигура активна
				m = N; //номер фигуры в массиве становится N
				N++; //количество фигур увеличено на 1
				x[m] = 100; //координаты x0
				y[m] = 100; //координаты y0
				R[m] = 50; //радиус
				g[m] = 2; //тип фигуры квадрат
				h[m] = 2; //фигура не активна

                Point point(x[m], y[m]);
                point.setR(50);
                Figure square(createSquare);
                square.create(point);
                listFigure[m] = square;

				GetClientRect(event.gethWnd(), &rect);
				InvalidateRect(event.gethWnd(), &rect, -1);
				UpdateWindow(event.gethWnd());
			}

			if(event.getwParam() == VK_F4) {
                y_0 = HIWORD(event.getlParam()); //смещение для y_0

                // at += pi / 12;
//                y[m] = y[m] * sin(at);
                listFigure[m].setPointList(getRotateFigure(listFigure[m].getPointList(),
                pi/12, listFigure[m].getPointCenter(), axis, listFigure[m].getModeRotation()));
                listFigure[m].setSaveAngle(pi / 12);
//
//                y[m] = 2 * y_0 - y[m]; //изменение координаты y для отображения относительно горизонтальной оси
//                R[m] = -R[m]; //изменение радиуса на отрицательный
                GetClientRect(event.gethWnd(), &rect);
                InvalidateRect(event.gethWnd(), &rect, -1);
                UpdateWindow(event.gethWnd());
			}

			if (event.getwParam() == VK_F5) {
				y_0 = HIWORD(event.getlParam()); //смещение для y_0
				// at += pi / 12;
				// y[m] = y[m] * sin(at);
				listFigure[m].setPointList(getRotateFigure(listFigure[m].getPointList(),
					-(pi / 12), listFigure[m].getPointCenter(), axis, listFigure[m].getModeRotation()));
				listFigure[m].setSaveAngle(-(pi / 12));
				//
				//                y[m] = 2 * y_0 - y[m]; //изменение координаты y для отображения относительно горизонтальной оси
				//                R[m] = -R[m]; //изменение радиуса на отрицательный
				GetClientRect(event.gethWnd(), &rect);
				InvalidateRect(event.gethWnd(), &rect, -1);
				UpdateWindow(event.gethWnd());
			}

			//при нажатии клавиши вверх
			if (event.getwParam() == VK_UP) {
				R[m] += 5; //увеличиваем радиус на 5
				GetClientRect(event.gethWnd(), &rect);
				InvalidateRect(event.gethWnd(), &rect, -1);
				UpdateWindow(event.gethWnd());
			}

			//при нажатии клавиши вниз
			if (event.getwParam() == VK_DOWN) {
				R[m] -= 5; //уменьшаем радиус на 5
				GetClientRect(event.gethWnd(), &rect);
				InvalidateRect(event.gethWnd(), &rect, -1);
				UpdateWindow(event.gethWnd());
			}

			if (event.getwParam() == VK_SPACE) {
				axis = !axis;

			}

		}


		if ((N - 1 < n) && (N > 0)) { //если количество фигур от 1 до 10
		//при нажатии клавиши влево
			if (event.getwParam() == VK_LEFT) {
				h[m] = 1; //фигура активна
				if (m > 0) //если номер фигуры больше 0
					m--; //фигура переклюается на предыдущую
				else
					m = N - 1; //если фигура была первая, то она переключается на последнюю
				h[m] = 2; //фигура не активна
				GetClientRect(event.gethWnd(), &rect);
				InvalidateRect(event.gethWnd(), &rect, -1);
				UpdateWindow(event.gethWnd());
			}

			//при нажатии клавиши вправо
			if (event.getwParam() == VK_RIGHT) {
				h[m] = 1; //фигура активна
				if (m < N - 1) //если номер фигуры меньше количества созданных фигур
					m++; //фигура переклюается на следующую
				else
					m = 0; //если фигура последняя, то переключится на первую
				h[m] = 2; //фигура не активна
				GetClientRect(event.gethWnd(), &rect);
				InvalidateRect(event.gethWnd(), &rect, -1);
				UpdateWindow(event.gethWnd());
			}

			//при нажатии клавиши DEL
			if (event.getwParam() == VK_DELETE) {
				for (int i = m; i <= N - 1; i++) { //цикл удаляет значения выбранной фигуры из памяти и смещает остальные 
					x[i] = x[i + 1];
					y[i] = y[i + 1];
					g[i] = g[i + 1];
					R[i] = R[i + 1];
					h[i] = h[i + 1];
					listFigure[i]  = listFigure[i + 1];
				}
				N--; //количество фигур уменьшается на 1
				if (m > 0) //выбранной фигурой становится предыдущая
					m--;
				else
					m = 0; //если удаленная фигура была первой, то новой выбранной фигурой становится новая фигура, стоящая на 1 месте
					listFigure[m].restore();
				h[m] = 2; //фигура не активна
				GetClientRect(event.gethWnd(), &rect);
				InvalidateRect(event.gethWnd(), &rect, -1);
				UpdateWindow(event.gethWnd());
			}
		}
    });

    mainWnd->Show();

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    delete mainWnd;
    return msg.wParam;
}

List<Point> getRotateFigure(List<Point> pointList, double angle, Point center, boolean axis, ModeRotation mode) {
    int length = pointList.size();
	int cofficient = 1;
    if (length <= 1) return pointList;
	if (mode == REVERSE) {
		angle = -angle;
	}
    double cs = cos(angle);
    double sn = sin(angle);
    /* Point center = Point(0,0);
    for (int i = 0; i < length; i++) {
        center.setX(pointList[i].getX());
        center.setY(pointList[i].getY());
    }
    center.setX(center.getX() / length);
    center.setY(center.getY() / length);
	*/

    double dx;
    double dy;
    while(length--) {
        dx = pointList[length].getX() - center.getX();
        dy = pointList[length].getY() - center.getY();
        pointList[length].setX(dx * cs - sn * dy + center.getX());
        pointList[length].setY(dx * sn + cs * dy + center.getY());
    }

    return pointList;
}

Point getNewCenter(Point point, Point figure, boolean axis) {
	if (axis) 
		figure.setX(point.getX() * 2 - figure.getX());
	else 
		figure.setY(point.getY() * 2 - figure.getY());
	return figure;
}

ModeRotation getUpdateModeRotation(Mode mode) {
	if (mode == NORMAL || mode == BOTH) {
		return STRIHT;
	}
	else {
		return REVERSE;
	}
}

Mode mirroring(Mode mode, boolean axis) {
	if (axis) {
		switch (mode)
		{
		case NORMAL:
			return VERTICAL;
		case VERTICAL:
			return NORMAL;
		case HORIZONTAL:
			return BOTH;
		case BOTH:
			return HORIZONTAL;
		}
	}
	else {
		switch (mode)
		{
		case NORMAL:
			return HORIZONTAL;
		case VERTICAL:
			return BOTH;
		case HORIZONTAL:
			return NORMAL;
		case BOTH:
			return VERTICAL;
		}
	}
}

void debugList(List<Point> listPoint) {
	std::wstringstream ss;
	for (auto point : listPoint) {
		ss << "X: " << point.getX() << "Y: " << point.getY() << '\n';
	}
	std::wstring str = ss.str();
	MessageBox(NULL, str.c_str(), L"", MB_OK);
}

//    auto controller = std::make_unique<DelegateController>(hWnd, uMsg, wParam, lParam);
//    auto triangle = std::make_unique<Triangle>(100, 100, 50);
//    HPEN hP1, hP2;
//    PAINTSTRUCT ps;
//    RECT rect;
//    int userReply;
//    controller->setOnPaintListener([&](ObjectWinProc data) {
//        hDC = BeginPaint(hWnd, &ps);
//        hP1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
//        hP2 = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
//
//            if (SignsOfVisible::V == true) {
//
//                if (SignsOfVisible::m == true)
//                    SelectObject(hDC, hP2);
//                else
//                    SelectObject(hDC, hP1);
//                MoveToEx(hDC, triangle->getX(), triangle->getY() - triangle->getR(), NULL);
//                LineTo(hDC, triangle->getX() - triangle->getR() * cos(pi / 6), triangle->getY() + triangle->getR() * sin(pi / 6));
//                LineTo(hDC, triangle->getX() + triangle->getR() * cos(pi / 12), triangle->getY() + triangle->getR() * sin(pi / 12));
//                LineTo(hDC, triangle->getX() , triangle->getY() - triangle->getR() );
//            }
//
//            EndPaint(hWnd, &ps);
//    });
//    controller->execute();

//    auto controller = std::make_unique<DelegateController>(hWnd, uMsg, wParam, lParam);
//        controller->setOnPaintListener([&](ObjectWinProc data) {
//        hDC = BeginPaint(hWnd, &ps);
//        hP1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
//        hP2 = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
//
//            if (SignsOfVisible::V == true) {
//
//                if (SignsOfVisible::m == true)
//                    SelectObject(hDC, hP2);
//                else
//                    SelectObject(hDC, hP1);
//                MoveToEx(hDC, triangle->getX(), triangle->getY() - triangle->getR(), NULL);
//                LineTo(hDC, triangle->getX() - triangle->getR() * cos(pi / 6), triangle->getY() + triangle->getR() * sin(pi / 6));
//                LineTo(hDC, triangle->getX() + triangle->getR() * cos(pi / 12), triangle->getY() + triangle->getR() * sin(pi / 12));
//                LineTo(hDC, triangle->getX() , triangle->getY() - triangle->getR() );
//            }
//
//            EndPaint(hWnd, &ps);
//    });