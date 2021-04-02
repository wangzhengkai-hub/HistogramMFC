// Histogram.cpp: 实现文件
//

#include "pch.h"
//#include <iostream>
//#include <array>
#include "HistogramMFC.h"
#include "Histogram.h"
#include "afxdialogex.h"


Histo::Histo(CRect _rect)
{
	positionRt = _rect;
	double stepX = this->positionRt.Width() / 255.0 * 5.0;
	histoValue.fill(10);
	for (size_t i = 0; i < 256; i = i+5)
		scaleValueX[i] = scaleValueX[i] * stepX;
}

Histo::~Histo()
{
}


// Histogram 对话框

IMPLEMENT_DYNAMIC(Histogram, CDialogEx)

Histogram::Histogram(CWnd* pParent /*=nullptr*/)
	:CDialogEx(IDD_FORMVIEW, pParent)
{
	triangleFlag = -1;
}

Histogram::Histogram(CRect _rect, CWnd* pParent)
	: CDialogEx(IDD_FORMVIEW, pParent)
{
	triangleFlag = -1;
	rect = _rect;

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
	if (lowRect.PtInRect(point))
	{
		isMoveTriangle = true;
		posStart = point;
		triangleFlag = 0;
	}

	if (upRect.PtInRect(point))
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
		//posStart = leftTriangel.center;
		isMoveTriangle = false;
		triangleFlag = -1;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void Histogram::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (lowRect.PtInRect(point)|| upRect.PtInRect(point))
	{
		HCURSOR cursor = LoadCursor(NULL, IDC_SIZEWE);
		SetCursor(cursor);
		//SetCursor(cursor);//将光标设置成十字
		SetClassLongA(this->GetSafeHwnd(),
			-12,
			(LONG)LoadCursor(NULL, IDC_CROSS));//使光标在该区域不再闪烁
	}
	else
	{
		SetClassLongA(this->GetSafeHwnd(),
			-12,
			(LONG)LoadCursor(NULL, IDC_ARROW));//光标离开该区域恢复默认箭头形状
	}




	if (isMoveTriangle)
	{
		int transX = point.x - posStart.x;
		int transY = point.y - posStart.y;
		posStart = point;
		switch (triangleFlag)
		{
		case 0:
			lowRect.OffsetRect(transX, 0);
			break;

		case 1:
			upRect.OffsetRect(transX, 0);
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
	this->MoveWindow(rect);
	// TODO:  在此添加额外的初始化
	//leftTriangel.SetTrianglePos(CPoint(60, 200));
	//rightTriangel.SetTrianglePos(CPoint(300, 200));

	CRect _rect;
	this->GetClientRect(_rect);
	_rect.top += 50;
	_rect.bottom -= 50;
	_rect.left += 50;
	_rect.right -= 50;
	histo.histoValue.fill(50);
	histo.positionRt = _rect;

	lowRect.left = _rect.left - 7;
	lowRect.right = _rect.left + 8;
	lowRect.top = _rect.top;
	lowRect.bottom = _rect.bottom;

	upRect.left = _rect.right - 8;
	upRect.right = _rect.right + 7;
	upRect.top = _rect.top;
	upRect.bottom = _rect.bottom;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Histogram::OnPaint()
{

	CPaintDC dc(this);
	CDC      cacheDc;
	CBitmap  cacheCBitmap;

	CRect rc;
	GetClientRect(&rc);
	cacheDc.CreateCompatibleDC(&dc);
	cacheCBitmap.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	CBitmap* pOldBit = cacheDc.SelectObject(&cacheCBitmap);
	cacheDc.FillSolidRect(rc, GetSysColor(COLOR_WINDOW));

	//PaintTriangle(&cacheDc,leftTriangel,RGB(0,0,0));
	//PaintTriangle(&cacheDc, rightTriangel, RGB(0, 0, 0));
	PaintHisto(&cacheDc, histo);

	dc.BitBlt(0, 0, rc.right, rc.bottom, &cacheDc, 0, 0, SRCCOPY);

	cacheCBitmap.DeleteObject();
	cacheDc.DeleteDC();
	CDialogEx::OnPaint();
}


BOOL Histogram::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return true;
}


bool Histogram::PaintHisto(CDC* pDC, Histo _histo)
{
	CPen solidPen(PS_SOLID, 1, RGB(192, 192, 192));
	CPen dothPen(PS_DOT, 1, RGB(192, 192, 192));
	pDC->SelectObject(solidPen);
	pDC->Rectangle(_histo.positionRt);
	_histo.SetPara();
	PaintGrid(pDC,_histo);
	PaintHistoValue(pDC, _histo);
	PaintTRect(pDC);
	return false;
}

//bool Histogram::PaintTriangle(CDC* pDC, const Triangle& _triangle, COLORREF color)
//{
//	CRgn rgn;
//	CBrush brush;
//	pDC->Polygon(_triangle.data, 3);
//	rgn.CreatePolygonRgn(_triangle.data, 3, ALTERNATE/*WINDING*/);
//	brush.CreateSolidBrush(color);
//	pDC->FillRgn(&rgn, &brush);
//	brush.DeleteObject();
//	rgn.DeleteObject();
//	return true;
//}

bool Histo::SetPara()
{

	stepX = positionRt.Width() / 256.0;
	for (size_t i = 0; i < 256; i = i + 5)
		scaleValueX.push_back(int(i * stepX));

	int maxHeight = (int)std::ceil((showRange * 100) / 10);
	stepY = positionRt.Height() / (maxHeight * 10);

	int scaleStep = 2;
	if (maxHeight > 3)
		scaleStep = std::pow(2, (maxHeight / 3));

	for (size_t i = 0; i <= maxHeight * 10; i = i + scaleStep)
		scaleValueY.push_back(int(i * stepY));

	return true;
}


int Histogram::PaintGrid(CDC* pDC,Histo _histo)
{
	CPen graySolidPen(PS_SOLID, 1, RGB(192, 192, 192));
	CPen grayDothPen(PS_DOT, 1, RGB(192, 192, 192));

	CPen blackThickPen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen blackThinPen(PS_SOLID, 1, RGB(0, 0, 0));

	CFont font;
	font.CreateFontA(13, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("宋体"));

	for (size_t i = 0; i < _histo.scaleValueX.size(); i++)
	{
		if (i % 5 == 0)
			pDC->SelectObject(graySolidPen);
		else
			pDC->SelectObject(grayDothPen);

		pDC->MoveTo(_histo.scaleValueX[i] + _histo.positionRt.left, _histo.positionRt.bottom - 1);
		pDC->LineTo(_histo.scaleValueX[i] + _histo.positionRt.left, _histo.positionRt.top);

		if (i % 5 == 0)
		{
			pDC->SelectObject(blackThickPen);
			pDC->MoveTo(_histo.scaleValueX[i] + _histo.positionRt.left, _histo.positionRt.bottom + 10);
			pDC->LineTo(_histo.scaleValueX[i] + _histo.positionRt.left, _histo.positionRt.bottom + 5);

			CString str;
			str.Format("%d", (int)std::round(_histo.scaleValueX[i] / _histo.stepX));
			pDC->SelectObject(font);
			pDC->TextOutA(_histo.scaleValueX[i]-13 + _histo.positionRt.left, _histo.positionRt.bottom + 15, str);
		}
	}


	for (size_t i = 0; i < _histo.scaleValueY.size(); i++)
	{
		if (i % 5 == 0)
			pDC->SelectObject(graySolidPen);
		else
			pDC->SelectObject(grayDothPen);

		pDC->MoveTo(_histo.positionRt.left, _histo.positionRt.bottom - _histo.scaleValueY[i]);
		pDC->LineTo(_histo.positionRt.right, _histo.positionRt.bottom - _histo.scaleValueY[i]);

		if (i % 5 == 0)
			pDC->SelectObject(blackThickPen);
		else
			pDC->SelectObject(graySolidPen);
		pDC->MoveTo(_histo.positionRt.left-10, _histo.positionRt.bottom - _histo.scaleValueY[i]);
		pDC->LineTo(_histo.positionRt.left-5, _histo.positionRt.bottom - _histo.scaleValueY[i]);

		if (i % 5 == 0)
		{
			pDC->SelectObject(font);
			CString str;
			str.Format("%d", (int)std::round(_histo.scaleValueY[i]/ _histo.stepY));
			pDC->TextOutA(_histo.positionRt.left - 30, _histo.positionRt.bottom - _histo.scaleValueY[i]-7, str);
		}

	}
	return 0;
}


bool Histogram::PaintHistoValue(CDC* pDC, Histo _histo)
{
	CPen blueSolidPen(PS_SOLID, 1, RGB(0, 0, 255));
	pDC->SelectObject(blueSolidPen);
	for (size_t i = 0; i < _histo.histoValue.size(); i++)
	{
		if (_histo.histoValue[i]>0)
		{
			pDC->MoveTo(i * _histo.stepX + _histo.positionRt.left, _histo.positionRt.bottom);
			pDC->LineTo(i * _histo.stepX + _histo.positionRt.left, _histo.positionRt.bottom - _histo.histoValue[i] * _histo.stepY);
		}

	}
	return false;
}


bool Histogram::PaintTRect(CDC* pDC)
{
	CPen greenPen(PS_SOLID, 2, RGB(0, 255, 0));
	CPen redPen(PS_SOLID, 2, RGB(255, 0, 0));

	pDC->SelectObject(greenPen);
	pDC->MoveTo((lowRect.left + lowRect.right) / 2, lowRect.bottom);
	pDC->LineTo((lowRect.left + lowRect.right) / 2, lowRect.top);

	pDC->SelectObject(redPen);
	pDC->MoveTo((upRect.left + upRect.right) / 2, upRect.bottom);
	pDC->LineTo((upRect.left + upRect.right) / 2, upRect.top);

	// TODO: 在此处添加实现代码.
	return false;
}
