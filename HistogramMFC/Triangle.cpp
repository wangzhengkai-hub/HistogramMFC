#include "pch.h"
#include "Triangle.h"

Triangle::Triangle()
{
    size = 15;

    center.x = size/2;
    center.y = size / 2;

    vertex[0].x = center.x;
    vertex[0].y = center.y - size / 2;

    vertex[1].x = center.x - size / 2;
    vertex[1].y = center.y;

    vertex[2].x = center.x + size / 2;
    vertex[2].y = center.y;
}

Triangle::Triangle(int _size, CPoint _center)
{
    size = _size;
    center = _center;

    vertex[0].x = center.x;
    vertex[0].y = center.y - size / 2;

    vertex[1].x = center.x - size / 2;
    vertex[1].y = center.y;

    vertex[2].x = center.x + size / 2;
    vertex[2].y = center.y;
}

Triangle::~Triangle()
{
}

bool Triangle::SetTrianglePos(CPoint point)
{
    center = point;

    vertex[0].x = center.x;
    vertex[0].y = center.y - size / 2;

    vertex[1].x = center.x - size / 2;
    vertex[1].y = center.y;

    vertex[2].x = center.x + size / 2;
    vertex[2].y = center.y;
    return true;
}

bool Triangle::MoveTriangle(int transX, int transY)
{
    for (size_t i = 0; i < 3; i++)
    {
        vertex[i].x += transX;
        vertex[i].y += transY;
    }
    center.x += transX;
    center.y += transY;
    return true;
}

bool Triangle::IsInTriangle(CPoint point)
{
    int signOfTrig = (vertex[2].x - vertex[1].x) * (vertex[0].y - vertex[1].y) - (vertex[2].y - vertex[1].y) * (vertex[0].x - vertex[1].x);
    int signOfAB = (vertex[1].x - vertex[0].x) * (point.y - vertex[0].y) - (vertex[1].y - vertex[0].y) * (point.x - vertex[0].x);
    int signOfBC = (vertex[2].x - vertex[1].x) * (point.y - vertex[1].y) - (vertex[2].y - vertex[1].y) * (point.x - vertex[1].x);
    int signOfCA = (vertex[0].x - vertex[2].x) * (point.y - vertex[2].y) - (vertex[0].y - vertex[2].y) * (point.x - vertex[2].x);

    boolean d1 = (signOfAB * signOfTrig > 0);
    boolean d2 = (signOfBC * signOfTrig > 0);
    boolean d3 = (signOfCA * signOfTrig > 0);

    return (d1 && d2 && d3);
}
