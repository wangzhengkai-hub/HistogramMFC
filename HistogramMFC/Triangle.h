#pragma once


class Triangle
{
public:
	Triangle();
	Triangle(int _size, CPoint _center);
	~Triangle();

//private:
	int size;
	CPoint vertex[3];
	CPoint center;

public:
	CPoint* data = vertex;

public:
	bool MoveTriangle(int transX, int transY);
	bool IsInTriangle(CPoint point);
	bool SetTrianglePos(CPoint point);
};

