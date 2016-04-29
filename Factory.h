#pragma once
#ifndef FACTORY_H
#define FACTORY_H

#include "Shapes.h"
#include <time.h>
#include <stdlib.h>

//���������� ��������� ����������� ����� � ��������� �� -100 �� 100
double randInterval() {
	return ((double)rand() / RAND_MAX - 0.5) * 200;
}

// 0-�����, 1 - ����, 2 - �������������, 3 - �������, 4 - ��������, 5 - �������������
Shape * CreateFigure(int type) { 
	switch (type){
		case 0: {
			Point * p = new Point(randInterval(), randInterval());
			return p;
		}
		case 1: {
			Circle * c = new Circle(randInterval(), randInterval(), randInterval() + 100);
			return c;
		}
		case 2: {
			Rect * r = new Rect(randInterval(), randInterval(), randInterval(), randInterval());
			return r;
		}
		case 3: {
			Square * s = new Square(randInterval(), randInterval(), randInterval(), randInterval());
			return s;
		}
		case 4: {
			Polyline * pol = new Polyline;
			int randCountVertex = rand() % 5 + 5;
			for (int i = 0; i < randCountVertex; ++i) {
				Point p(randInterval(), randInterval());
				pol->AddPoint(p);
			}
			return pol;
		}
		case 5: {
			Polygon * pol = new Polygon;
			int randCountVertex = rand() % 5 + 5;
			for (int i = 0; i < randCountVertex; ++i) {
				Point p(randInterval(), randInterval());
				pol->AddPoint(p);
			}
			return pol;
		}
		//���� ������ ������ ��������, �� ����� ����� �����
		default: {
			Point * p = new Point(randInterval(), randInterval());
			return p;
		}
	}
}


#endif