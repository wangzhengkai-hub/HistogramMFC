#pragma once


class Triangle
{
public:
	Triangle();
	~Triangle();

private:
	int size;
	CPoint vertex[3];
	CPoint center;

public:
	CPoint* data = vertex;

public:
	bool MoveTriangle(int transX, int transY);
};

class Histogram :public CView
{
	Histogram() {};

private:
	Triangle triangle;

	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
};

