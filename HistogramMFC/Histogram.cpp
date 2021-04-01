#include "pch.h"
#include "Histogram.h"

Triangle::Triangle()
{
    size = 60;
    center.x = size/2;
    center.y = size / 2;
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

bool Triangle::MoveTriangle(int transX, int transY)
{
    for (size_t i = 0; i < 3; i++)
    {
        vertex[2].x += transX;
        vertex[2].y += transY;
    }
    return true;
}


void Histogram::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    // TODO: 在此添加专用代码和/或调用基类

    CView::OnPrint(pDC, pInfo);
}
