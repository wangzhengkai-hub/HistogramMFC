// Histogram.cpp: 实现文件
//

#include "pch.h"
#include "HistogramMFC.h"
#include "Histogram.h"
#include "afxdialogex.h"


// Histogram 对话框

IMPLEMENT_DYNAMIC(Histogram, CDialogEx)

Histogram::Histogram(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FORMVIEW, pParent)
{

}

Histogram::~Histogram()
{
}

void Histogram::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Histogram, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// Histogram 消息处理程序


void Histogram::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (leftTriangel.IsInTriangle(point))
	{
		isMoveTriangle = true;
		posStart = point;
		triangleFlag = 0;
	}

	if (rightTriangel.IsInTriangle(point))
	{
		isMoveTriangle = true;
		posStart = point;
		triangleFlag = 1;
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void Histogram::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isMoveTriangle == true)
	{
		posStart = leftTriangel.center;
		isMoveTriangle = false;
		triangleFlag = -1;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void Histogram::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isMoveTriangle)
	{
		int transX = point.x - posStart.x;
		int transY = point.y - posStart.y;
		posStart = point;
		switch (triangleFlag)
		{
		case 0:
			leftTriangel.MoveTriangle(transX, 0);
			break;

		case 1:
			rightTriangel.MoveTriangle(transX, 0);
			break;

		default:
			break;
		}

		Invalidate(true);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL Histogram::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	leftTriangel.SetTrianglePos(CPoint(60, 200));
	rightTriangel.SetTrianglePos(CPoint(300, 200));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Histogram::OnPaint()
{
	CPaintDC dc(this);

	CRect rc;
	GetClientRect(&rc);
	CDC cacheDc;
	cacheDc.CreateCompatibleDC(&dc);

	CBitmap m_cacheCBitmap;
	m_cacheCBitmap.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	CBitmap* pOldBit = cacheDc.SelectObject(&m_cacheCBitmap);
	cacheDc.FillSolidRect(rc, GetSysColor(COLOR_WINDOW));

	CRgn rgn;
	CBrush brush;
	cacheDc.Polygon(leftTriangel.data, 3);
	rgn.CreatePolygonRgn(leftTriangel.data, 3, ALTERNATE/*WINDING*/);
	brush.CreateSolidBrush(RGB(0, 0, 0));
	cacheDc.FillRgn(&rgn, &brush);

	rgn.DeleteObject();
	cacheDc.Polygon(rightTriangel.data, 3);
	rgn.CreatePolygonRgn(rightTriangel.data, 3, ALTERNATE/*WINDING*/);
	cacheDc.FillRgn(&rgn, &brush);

	dc.BitBlt(0, 0, rc.right, rc.bottom, &cacheDc, 0, 0, SRCCOPY);

	brush.DeleteObject();
	rgn.DeleteObject();
	m_cacheCBitmap.DeleteObject();
	cacheDc.DeleteDC();
	CDialogEx::OnPaint();
}


BOOL Histogram::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return true;
}
