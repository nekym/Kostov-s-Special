#pragma once
#ifndef SHAPES_H
#define SHAPES_H

#define _USE_MATH_DEFINES
#include "Base.h"
#include "Container.h"
#include <iostream>
#include <exception>

class DegenerateFigureException : public std::exception {
public:
	virtual const char* what() const {
		return "Error: degenerate figure";
	}
};

class Shape : virtual public Printable {
public:
	virtual ~Shape() {}
	static int CountShapes;
	static int GetCount() {
		return CountShapes;
	}
	virtual void PrintInfo() = 0;
	virtual std::string GetString() const { return "Any shape"; }
	
};

int Shape::CountShapes = 0;

class Point : public Shape, public Named {
public:
	Point(double x = 0, double y = 0) 
		: Named("Point")
		, m_x(x)
		, m_y(y) 
	{
		++CountShapes;
	}

	~Point() {
		--CountShapes;
	}

	std::string GetString() const { return m_name; }

	double GetX() const {
		return m_x;
	}

	double GetY() const {
		return m_y;
	}

	void SetX(double x) {
		m_x = x;
	}

	void SetY(double y) {
		m_y = y;
	}

	void PrintInfo() {
		std::cout << (*this);
	}

	friend std::ostream & operator << (std::ostream & ioStream, const Point & shape);
private:
	double m_x;
	double m_y;
};

std::ostream & operator << (std::ostream & ioStream, const Point & shape) {
	ioStream << "(" << shape.m_x << "; " << shape.m_y << ")";
	return ioStream;
}

class Circle : public Shape, public Named {
public:
	Circle(double x = 0, double y = 0, double R = 1) 
		: Named("Circle")
		, m_radius(R)
		,  m_center(x, y) 
	{
		if (R <= 0) 
			throw DegenerateFigureException();
	}

	std::string GetString() const { return m_name; }

	double Area() const {
		return M_PI * m_radius * m_radius;
	}

	void PrintInfo() {
		std::cout << (*this);
	}

	friend std::ostream & operator << (std::ostream & ioStream, const Circle & shape);
private:
	Point m_center;
	double m_radius;
};

std::ostream & operator << (std::ostream & ioStream, const Circle & shape) {
	ioStream << "Center in " << shape.m_center;
	ioStream << ", R = " << shape.m_radius << ", area = " << shape.Area();
	return ioStream;
}


//Rect - прямоугольник со сторонами, параллельными OX и OY(с помощью двух точек),
class Rect : public Shape, public Named {
public:
	Rect(double x1 = 0, double y1 = 0, double x2 = 1, double y2 = 1) 
		: Named("Rectangle")
		, p1(x1, y1) 
		, p2(x2, y2)
	{
		if (x1 == x2 || y1 == y2) 
			throw DegenerateFigureException();
		
		--CountShapes;
	}

	~Rect() {
		++CountShapes;
	}

	std::string GetString() const { return m_name; }

	virtual double Area() const {
		return abs(p1.GetX() - p2.GetX()) * abs(p1.GetY() - p2.GetY());
	}

	virtual void PrintInfo() {
		std::cout << (*this);
	}

	friend std::ostream & operator << (std::ostream & ioStream, const Rect & shape);

protected:
	Point p1, p2;
};

std::ostream & operator << (std::ostream & ioStream, const Rect & shape) {
	ioStream << shape.p1 << ", (" << shape.p2.GetX() << ", " << shape.p1.GetY() << "), ";
	ioStream << shape.p2 << ", (" << shape.p1.GetX() << ", " << shape.p2.GetY() << "), ";
	ioStream << "area = " << shape.Area();
	return ioStream;
}

//Square - прямоугольник с одинаковыми сторонами, задающийся по двум диагональным точкам.
class Square : public Rect {
public:
	Square(double x1 = 0, double y1 = 0, double x2 = 1, double y2 = 1) { 
		if (x1 == x2 && y1 == y2) {
			throw DegenerateFigureException();
		}
		m_name = "Square";
		p1.SetX(x1);
		p1.SetY(y1);
		p2.SetX(x2);
		p2.SetY(y2);
	}

	//пововина квадрата диагонали
	double Area() const {
		double diag = sqrt((p1.GetX() - p2.GetX())*(p1.GetX() - p2.GetX()) 
			+ (p1.GetY() - p2.GetY())*(p1.GetY() - p2.GetY()));
		return diag*diag / 2;
	}
	//выведем только две точки диагонали. Оставшиеся две точки можно однозначно вычислить,
	//но не будем, дабы не захламлять код.
	void PrintInfo() {
		std::cout << (*this);
	}

	friend std::ostream & operator << (std::ostream & ioStream, const Square & shape);
};

std::ostream & operator << (std::ostream & ioStream, const Square & shape) {
	ioStream << shape.p1 << ", " << shape.p2 << ", area = " << shape.Area();
	return ioStream;
}

//Polyline - ломаная; должна быть реализована с помощью Container< Point >,
//наполняться с помощью метода AddPoint(Point const & point),
class Polyline : public Shape, public Named {
protected:
	Container <Point> points;
public:
	Polyline() : Named("Polyline") {
		++CountShapes;
	}

	~Polyline() {
		--CountShapes;// += points.Size() - 1;
	}

	std::string GetString() const { return m_name; }

	void AddPoint(Point const & point) {
		points.AddEnd(point);
		//--CountShapes;
	}

	virtual double Length()  {
		double res = 0;
		int size = points.Size();
		for (int i = 0; i < size - 1; ++i) {
			res += sqrt((points[i].GetX() - points[i+1].GetX())*(points[i].GetX() - points[i + 1].GetX()) + 
				(points[i].GetY() - points[i + 1].GetY())*(points[i].GetY() - points[i + 1].GetY()));
		}
		return res;
	}

	virtual void PrintInfo() {
		std::cout << (*this);
	}

	friend std::ostream & operator << (std::ostream & ioStream, Polyline & shape);

};

std::ostream & operator << (std::ostream & ioStream, Polyline & shape) {
	int size = shape.points.Size();
	for (int i = 0; i < size; ++i) {
		ioStream << shape.points[i] << ", ";
	}
	ioStream << "length = " << shape.Length();
	return ioStream;
}

//Polygon - произвольный многоугольник - это же просто замкнутая ломанная. 
class Polygon : public Polyline {
public:
	Polygon() {
		m_name = "Polygon";
	}

	 double Length() {
		double res = 0;
		int size = points.Size();
		for (int i = 0; i < size; ++i) {
			res += sqrt((points[i].GetX() - points[(i + 1) % size].GetX())*(points[i].GetX() - points[(i + 1) % size].GetX()) +
				(points[i].GetY() - points[(i + 1) % size].GetY())*(points[i].GetY() - points[(i + 1) % size].GetY()));
		}
		return res;
	}

	 void PrintInfo() {
		 std::cout << (*this);
	 }

	 friend std::ostream & operator << (std::ostream & ioStream, Polygon & shape);
	 //можно посчитать и площадь (при условии, что многоугольник выпуклый,
	 //это не сложно), но не будем, дабы опять же не писать лишнего
};

std::ostream & operator << (std::ostream & ioStream, Polygon & shape) {
	int size = shape.points.Size();
	for (int i = 0; i < size; ++i) {
		ioStream << shape.points[i] << ", ";
	}
	ioStream << "perimetr = " << shape.Length();
	return ioStream;
}




#endif